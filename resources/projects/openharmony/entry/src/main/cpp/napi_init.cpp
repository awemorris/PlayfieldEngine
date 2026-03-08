#include "napi/native_api.h"
#include <ace/xcomponent/native_interface_xcomponent.h>
#include <rawfile/raw_file_manager.h>
#include <native_window/external_window.h>
#include <EGL/egl.h>
#include <GLES2/gl2.h>
#include <string>

extern "C" {
static napi_value Init(napi_env env, napi_value exports);
static napi_value InitResourceManager(napi_env env, napi_callback_info info);
static napi_value InitFileDir(napi_env env, napi_callback_info info);
static void OnSurfaceCreatedCB(OH_NativeXComponent* component, void* window);
static void OnSurfaceChangedCB(OH_NativeXComponent* component, void* window);
static void OnSurfaceDestroyedCB(OH_NativeXComponent* component, void* window);
static void DispatchTouchEventCB(OH_NativeXComponent* component, void* window);
};

NativeResourceManager* nativeResMgr;
char *sandboxDir;

static EGLDisplay display = EGL_NO_DISPLAY;
static EGLConfig config = nullptr;
static EGLContext context = EGL_NO_CONTEXT;
static EGLSurface surface = EGL_NO_SURFACE;

__attribute__((constructor))
void
RegisterEntryModule(void)
{
    napi_module suika3Module = {
        .nm_version = 1,
        .nm_flags = 0,
        .nm_filename = nullptr,
        .nm_register_func = Init,
        .nm_modname = "entry",
        .nm_priv = ((void*)0),
        .reserved = { 0 },
    };

    napi_module_register(&suika3Module);
}

static napi_value
Init(
     napi_env env,
     napi_value exports)
{
    // Register JS functions.
    napi_property_descriptor desc[] = {
        { "initResourceManager", nullptr, InitResourceManager, nullptr, nullptr, nullptr, napi_default, nullptr },
        { "initFileDir", nullptr, InitFileDir, nullptr, nullptr, nullptr, napi_default, nullptr },
    };
    napi_define_properties(env, exports, sizeof(desc) / sizeof(desc[0]), desc);

    // Register native callback functions.
    OH_NativeXComponent_Callback callback = {
        .OnSurfaceCreated = OnSurfaceCreatedCB,
        .OnSurfaceChanged = OnSurfaceChangedCB,
        .OnSurfaceDestroyed = OnSurfaceDestroyedCB,
        .DispatchTouchEvent = DispatchTouchEventCB,
    };
    napi_value exportInstance;
    if (napi_get_named_property(env, exports, OH_NATIVE_XCOMPONENT_OBJ, &exportInstance) != napi_ok) {
        return exports;
    }
    OH_NativeXComponent *nativeXComponent = nullptr;
    if (napi_unwrap(env, exportInstance, reinterpret_cast<void**>(&nativeXComponent)) != napi_ok) {
        return exports;
    }
    OH_NativeXComponent_RegisterCallback(nativeXComponent, &callback);

    return exports;
}

static napi_value
InitResourceManager(
    napi_env env,
    napi_callback_info info)
{
    size_t argc = 1;
    napi_value argv[1] = {nullptr};

    napi_get_cb_info(env, info, &argc, argv, nullptr, nullptr);

    // Save the pointer.
    nativeResMgr = OH_ResourceManager_InitNativeResourceManager(env, argv[0]);

    return nullptr;
}

static napi_value
InitFileDir(
    napi_env env,
    napi_callback_info info)
{
    size_t argc = 1;
    napi_value argv[1] = {nullptr};
    
    napi_get_cb_info(env, info, &argc, argv, nullptr, nullptr);

    size_t length = 0;
    napi_get_value_string_utf8(env, argv[0], nullptr, 0, &length);

    std::string path(length, '\0');
    napi_get_value_string_utf8(env, argv[0], &path[0], length + 1, &length);

    sandboxDir = strdup(path.c_str());

    return nullptr;
}

static void
OnSurfaceCreatedCB(
    OH_NativeXComponent* component,
    void* window)
{
    OHNativeWindow* nativeWindow = static_cast<OHNativeWindow*>(window);

    display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    eglInitialize(display, nullptr, nullptr);

    const EGLint configAttribs[] = {
        EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
        EGL_BLUE_SIZE, 8, EGL_GREEN_SIZE, 8, EGL_RED_SIZE, 8,
        EGL_NONE
    };
    EGLint numConfigs;
    eglChooseConfig(display, configAttribs, &config, 1, &numConfigs);

    const EGLint contextAttribs[] = { EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE };
    context = eglCreateContext(display, config, EGL_NO_CONTEXT, contextAttribs);

    surface = eglCreateWindowSurface(display, config, reinterpret_cast<EGLNativeWindowType>(nativeWindow), nullptr);

    eglMakeCurrent(display, surface, surface, context);

    glClearColor(1.0f, 0.4f, 0.7f, 1.0f); 
    glClear(GL_COLOR_BUFFER_BIT);
    eglSwapBuffers(display, surface);
}

static void
OnSurfaceChangedCB(
    OH_NativeXComponent* component,
    void* window)
{
}

static void
OnSurfaceDestroyedCB(
    OH_NativeXComponent* component,
    void* window)
{
}

static void
DispatchTouchEventCB(
    OH_NativeXComponent* component,
    void* window)
{
}
