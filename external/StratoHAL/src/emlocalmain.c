/* -*- tab-width: 8; indent-tabs-mode: t; -*- */

/*
 * Copyright (c) 2025, Awe Morris. All rights reserved.
 */

/*
 * Emscripten (local file)
 */

#include <stratohal/platform.h>

/* OpenGL */
#include "glrender.h"

/* OpenAL */
#include "alsound.h"

/* Emscripten Core */
#include <emscripten/emscripten.h>
#include <emscripten/html5.h>

/* Standard C */
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

/* Emscripten POSIX Emulation */
#include <sys/types.h>
#include <sys/stat.h>	/* stat(), mkdir() */
#include <sys/time.h>	/* gettimeofday() */

/*
 * Constants
 */

/* Frame Milli Seconds */
#define FRAME_MILLI	16

/*
 * Variables
 */

/* Screen */
static char *window_title;
static int screen_width;
static int screen_height;

/* Touch Position */
static int touch_start_x;
static int touch_start_y;
static int touch_last_y;
static bool is_continuous_swipe_enabled;

/* Locale */
static const char *lang_code;

/*
 * Forward Declarations
 */
static void loop_iter(void *userData);
static EM_BOOL cb_mousemove(int eventType, const EmscriptenMouseEvent *mouseEvent, void *userData);
static EM_BOOL cb_mousedown(int eventType, const EmscriptenMouseEvent *mouseEvent, void *userData);
static EM_BOOL cb_mouseup(int eventType, const EmscriptenMouseEvent *mouseEvent, void *userData);
static EM_BOOL cb_wheel(int eventType, const EmscriptenWheelEvent *wheelEvent, void *userData);
static EM_BOOL cb_keydown(int eventType, const EmscriptenKeyboardEvent *keyEvent, void *userData);
static EM_BOOL cb_keyup(int eventType, const EmscriptenKeyboardEvent *keyEvent, void *userData);
static int get_keycode(const char *key);
static EM_BOOL cb_touchstart(int eventType, const EmscriptenTouchEvent *touchEvent, void *userData);
static EM_BOOL cb_touchmove(int eventType, const EmscriptenTouchEvent *touchEvent,void *userData);
static EM_BOOL cb_touchend(int eventType, const EmscriptenTouchEvent *touchEvent, void *userData);
static EM_BOOL cb_touchcancel(int eventType, const EmscriptenTouchEvent *touchEvent, void *userData);
static void update_script_model_from_text(void);
static void update_script_model_from_current_line_text(void);
static void update_text_from_script_model(void);
static void init_lang_code(void);

/*
 * Main
 */
int main(void)
{
	/* Keep the thread alive and will receive events. */
	emscripten_exit_with_live_runtime();
	return 0;
}

/*
 * Startup
 */
EMSCRIPTEN_KEEPALIVE
void start_engine(void)
{
	/* Initialize the locale. */
	init_lang_code();

	/* Do a boot callback. */
	if (!on_event_boot(&window_title, &screen_width, &screen_height))
		return;

	/* Set the rendering canvas size. */
	emscripten_set_canvas_element_size("canvas", screen_width, screen_height);
	EM_ASM_({ onResizeWindow(); });

	/* Initialize the OpenGL rendering subsystem. */
	EmscriptenWebGLContextAttributes attr;
	EMSCRIPTEN_WEBGL_CONTEXT_HANDLE context;
	emscripten_webgl_init_context_attributes(&attr);
	attr.majorVersion = 2;
	attr.minorVersion = 0;
	context = emscripten_webgl_create_context("canvas", &attr);
	emscripten_webgl_make_context_current(context);
	if (!init_opengl(screen_width, screen_height))
		return;

	/* Initialize the OpenAL sound subsystem. */
	if (!init_openal())
		return;

	/* Do a start callback. */
	if (!on_event_start())
		return;

	/* Register input events. */
	emscripten_set_mousedown_callback("canvas", 0, true, cb_mousedown);
	emscripten_set_mouseup_callback("canvas", 0, true, cb_mouseup);
	emscripten_set_mousemove_callback("canvas", 0, true, cb_mousemove);
	emscripten_set_wheel_callback("canvas", 0, true, cb_wheel);
	emscripten_set_keydown_callback("canvas", 0, true, cb_keydown);
	emscripten_set_keyup_callback("canvas", 0, true, cb_keyup);
	emscripten_set_touchstart_callback("canvas", 0, true, cb_touchstart);
	emscripten_set_touchmove_callback("canvas", 0, true, cb_touchmove);
	emscripten_set_touchend_callback("canvas", 0, true, cb_touchend);
	emscripten_set_touchcancel_callback("canvas", 0, true, cb_touchcancel);

	/* Register other events. */
	EM_ASM_({
		window.addEventListener('resize', onResizeWindow);
		document.addEventListener('visibilitychange', function () {
			if(document.visibilityState === 'visible') {
				Module.ccall('setVisible');
				document.getElementById('canvas').focus();
			} else if(document.visibilityState === 'hidden') {
				Module.ccall('setHidden');
			}
		});
		document.getElementById('canvas').addEventListener('mouseleave', function () {
			Module.ccall('mouseLeave');
		});
	});

	/* Reserve the first frame callback. */
	emscripten_async_call(loop_iter, NULL, FRAME_MILLI);
}

EM_JS(void, onResizeWindow, (void),
{
	var canvas = document.getElementById('canvas');
	var cw = canvas.width;
	var ch = canvas.height;
	var aspect = cw / ch;
	var winw = window.innerWidth;
	var winh = window.innerHeight;
	var w = winw;
	var h = winw / aspect;
	if(h > winh) {
		h = winh;
		w = winh * aspect;
	}
	canvas.style.width = w + 'px';
	canvas.style.height = h + 'px';
	canvas.focus();
});

/* Run a frame. */
static void loop_iter(void *userData)
{
	static bool is_flip_pending = false;

	/* Do sound buffer filling. */
	fill_sound_buffer();

	/*
	 * Start a rendering.
	 *  - On Chrome, glFlush() seems to be called on "await" for a file I/O
	 *  - This causes flickering
	 *  - We avoid calling glClear() through opengl_start_rendering() here
	 *  - See also finish_frame_io()
	 */
	/* opengl_start_rendering(); */

	/* Do a frame event. */
	on_event_frame();

	/* Finish a rendering. */
	opengl_end_rendering();

	/* Reserve the next frame callback. */
	emscripten_async_call(loop_iter, NULL, FRAME_MILLI);
}

/* mousemove callback */
static EM_BOOL cb_mousemove(int eventType,
			    const EmscriptenMouseEvent *mouseEvent,
			    void *userData)
{
	double w, h, scale;
	int x, y;

	/*
	 * Get the "CSS" size of the rendering canvas
	 *  - It's not a visible size of the canvas
	 */
	emscripten_get_element_css_size("canvas", &w, &h);

	/* Scale a mouse position. */
	scale = w / (double)screen_width;
	x = (int)((double)mouseEvent->targetX / scale);
	y = (int)((double)mouseEvent->targetY / scale);

	/* Call the event handler. */
	on_event_mouse_move(x, y);

	return EM_TRUE;
}

/* mousedown callback */
static EM_BOOL cb_mousedown(int eventType,
			    const EmscriptenMouseEvent *mouseEvent,
			    void *userData)
{
	double w, h, scale;
	int x, y, button;

	/* Scale a mouse position. */
	emscripten_get_element_css_size("canvas", &w, &h);
	scale = w / (double)screen_width;
	x = (int)((double)mouseEvent->targetX / scale);
	y = (int)((double)mouseEvent->targetY / scale);

	if (mouseEvent->button == 0)
		button = MOUSE_LEFT;
	else
		button = MOUSE_RIGHT;

	/* Call the event handler. */
	on_event_mouse_press(button, x, y);

	return EM_TRUE;
}

/* mouseup callback */
static EM_BOOL cb_mouseup(int eventType,
			    const EmscriptenMouseEvent *mouseEvent,
			    void *userData)
{
	double w, h, scale;
	int x, y, button;

	/* Scale a mouse position. */
	emscripten_get_element_css_size("canvas", &w, &h);
	scale = w / (double)screen_width;
	x = (int)((double)mouseEvent->targetX / scale);
	y = (int)((double)mouseEvent->targetY / scale);

	if (mouseEvent->button == 0)
		button = MOUSE_LEFT;
	else
		button = MOUSE_RIGHT;

	/* Call the event handler. */
	on_event_mouse_release(button, x, y);

	return EM_TRUE;
}

/* wheel callback */
static EM_BOOL cb_wheel(int eventType,
			const EmscriptenWheelEvent *wheelEvent,
			void *userData)
{
	if (wheelEvent->deltaY > 0) {
		on_event_key_press(KEY_DOWN);
		on_event_key_release(KEY_DOWN);
	} else {
		on_event_key_press(KEY_UP);
		on_event_key_release(KEY_UP);
	}
	return EM_TRUE;
}

/* keydown callback */
static EM_BOOL cb_keydown(int eventType,
			  const EmscriptenKeyboardEvent *keyEvent,
			  void *userData)
{
	int keycode;

	keycode = get_keycode(keyEvent->key);
	if (keycode == -1)
		return EM_TRUE;

	on_event_key_press(keycode);
	return EM_TRUE;
}

/* keyup callback */
static EM_BOOL cb_keyup(int eventType,
			const EmscriptenKeyboardEvent *keyEvent,
			void *userData)
{
	int keycode;

	keycode = get_keycode(keyEvent->key);
	if (keycode == -1)
		return EM_TRUE;

	on_event_key_release(keycode);
	return EM_TRUE;
}

/* Get a keycode from a keysym. */
static int get_keycode(const char *key)
{
	if (strcmp(key, "Enter") == 0) {
		return KEY_RETURN;
	} else if (strcmp(key, " ") == 0) {
		return KEY_SPACE;
	} else if (strcmp(key, "Control") == 0) {
		return KEY_CONTROL;
	} else if (strcmp(key, "ArrowUp") == 0) {
		return KEY_UP;
	} else if (strcmp(key, "ArrowDown") == 0) {
		return KEY_DOWN;
	}
	return -1;
}

/* touchstart callback */
static EM_BOOL cb_touchstart(
	int eventType,
	const EmscriptenTouchEvent *touchEvent,
	void *userData)
{
	double w, h, scale;
	int x, y;

	touch_start_x = touchEvent->touches[0].targetX;
	touch_start_y = touchEvent->touches[0].targetY;
	touch_last_y = touchEvent->touches[0].targetY;

	/* Scale a mouse position. */
	emscripten_get_element_css_size("canvas", &w, &h);
	scale = w / (double)screen_width;
	x = (int)((double)touchEvent->touches[0].targetX / scale);
	y = (int)((double)touchEvent->touches[0].targetY / scale);

	/* Call the event handler. */
	on_event_mouse_press(MOUSE_LEFT, x, y);

	return EM_TRUE;
}

/* touchmove callback */
static EM_BOOL cb_touchmove(
	int eventType,
	const EmscriptenTouchEvent *touchEvent,
	void *userData)
{
	const int LINE_HEIGHT = 10;
	double w, h, scale;
	int delta, x, y;

	delta = touchEvent->touches[0].targetY - touch_last_y;
	touch_last_y = touchEvent->touches[0].targetY;

	if (delta > LINE_HEIGHT) {
		on_event_key_press(KEY_DOWN);
		on_event_key_release(KEY_DOWN);
	} else if (delta < -LINE_HEIGHT) {
		on_event_key_press(KEY_UP);
		on_event_key_release(KEY_UP);
	}

	/* Scale a mouse position. */
	emscripten_get_element_css_size("canvas", &w, &h);
	scale = w / (double)screen_width;
	x = (int)((double)touchEvent->touches[0].targetX / scale);
	y = (int)((double)touchEvent->touches[0].targetY / scale);

	/* Call the event handler. */
	on_event_mouse_move(x, y);

	return EM_TRUE;
}

/* touchend callback */
static EM_BOOL cb_touchend(
	int eventType,
	const EmscriptenTouchEvent *touchEvent,
	void *userData)
{
	const int OFS = 10;
	double w, h, scale;
	int x, y;

	/* Scale a mouse position. */
	emscripten_get_element_css_size("canvas", &w, &h);
	scale = w / (double)screen_width;
	x = (int)((double)touchEvent->touches[0].targetX / scale);
	y = (int)((double)touchEvent->touches[0].targetY / scale);

	/* Call the event handler. */
	on_event_mouse_move(x, y);

	/* Consider a two-finger tap as a right-click. */
	if (touchEvent->numTouches == 2) {
		on_event_mouse_press(MOUSE_RIGHT, x, y);
		on_event_mouse_release(MOUSE_RIGHT, x, y);
		return EM_TRUE;
	}

	/* Consider a one-finger tap as a left-click. */
	if (abs(touchEvent->touches[0].targetX - touch_start_x) < OFS &&
	    abs(touchEvent->touches[0].targetY - touch_start_y) < OFS) {
		on_event_mouse_release(MOUSE_LEFT, x, y);
		return EM_TRUE;
	}
	
	return EM_TRUE;
}

/* touchcancel callback */
static EM_BOOL cb_touchcancel(int eventType,
			      const EmscriptenTouchEvent *touchEvent,
			      void *userData)
{
	on_event_mouse_move(-1, -1);

	return EM_TRUE;
}

/*
 * Callback from JavaScript
 */

/* Resize the canvas. */
EM_JS(void, resizeWindow, (void), {
	canvas = document.getElementById('canvas');
	cw = canvas.width;
	ch = canvas.height;
	aspect = cw / ch;
	winw = window.innerWidth;
	winh = window.innerHeight;
	w = winw;
	h = winw / aspect;
	if(h > winh) {
		h = winh;
		w = winh * aspect;
	}
	canvas.style.width = w + 'px';
	canvas.style.height = h + 'px';
	canvas.focus();
});

/* Callback when a project is loaded. */
EMSCRIPTEN_KEEPALIVE void onLoadProject(void)
{
	start_engine();
}

/* When the tab is shown. */
void EMSCRIPTEN_KEEPALIVE setVisible(void)
{
	resume_sound();
}

/* When the tab is hidden. */
void EMSCRIPTEN_KEEPALIVE setHidden(void)
{
	pause_sound();
}

/* When the mouse pointer leaves Canvas. */
void EMSCRIPTEN_KEEPALIVE mouseLeave(void)
{
	on_event_touch_cancel();
}

/*
 * HAL API
 */

bool log_info(const char *s, ...)
{
	char buf[1024];

	va_list ap;
	va_start(ap, s);
	vsnprintf(buf, sizeof(buf), s, ap);
	va_end(ap);

	printf("%s\n", buf);

	return true;
}

bool log_warn(const char *s, ...)
{
	char buf[1024];

	va_list ap;
	va_start(ap, s);
	vsnprintf(buf, sizeof(buf), s, ap);
	va_end(ap);

	printf("%s\n", buf);

	return true;
}

bool log_error(const char *s, ...)
{
	char buf[1024];

	va_list ap;
	va_start(ap, s);
	vsnprintf(buf, sizeof(buf), s, ap);
	va_end(ap);

	printf("%s\n", buf);

	EM_ASM({
		alert(UTF8ToString($0));
	}, buf);

	return true;
}

bool log_out_of_memory(void)
{
	log_error("Out of memory.");
	return true;
}

void notify_image_update(struct image *img)
{
	fill_sound_buffer();
	opengl_notify_image_update(img);
	fill_sound_buffer();
}

void notify_image_free(struct image *img)
{
	fill_sound_buffer();
	opengl_notify_image_free(img);
	fill_sound_buffer();
}

void render_image_normal(
	int dst_left,
	int dst_top,
	int dst_width,
	int dst_height,
	struct image *src_image,
	int src_left,
	int src_top,
	int src_width,
	int src_height,
	int alpha)
{
	opengl_render_image_normal(dst_left, dst_top, dst_width, dst_height, src_image, src_left, src_top, src_width, src_height, alpha);
}

void render_image_add(
	int dst_left,
	int dst_top,
	int dst_width,
	int dst_height,
	struct image *src_image,
	int src_left,
	int src_top,
	int src_width,
	int src_height,
	int alpha)
{
	opengl_render_image_add(dst_left, dst_top, dst_width, dst_height, src_image, src_left, src_top, src_width, src_height, alpha);
}

void render_image_dim(
	int dst_left,
	int dst_top,
	int dst_width,
	int dst_height,
	struct image *src_image,
	int src_left,
	int src_top,
	int src_width,
	int src_height,
	int alpha)
{
	opengl_render_image_dim(dst_left, dst_top, dst_width, dst_height, src_image, src_left, src_top, src_width, src_height, alpha);
}

void render_image_rule(
	struct image *src_img,
	struct image *rule_img,
	int threshold)
{
	opengl_render_image_rule(src_img, rule_img, threshold);
}

void render_image_melt(
	struct image *src_img,
	struct image *rule_img,
	int threshold)
{
	opengl_render_image_melt(src_img, rule_img, threshold);
}

void
render_image_3d_normal(
	float x1,
	float y1,
	float x2,
	float y2,
	float x3,
	float y3,
	float x4,
	float y4,
	struct image *src_image,
	int src_left,
	int src_top,
	int src_width,
	int src_height,
	int alpha)
{
	opengl_render_image_3d_normal(x1,
				      y1,
				      x2,
				      y2,
				      x3,
				      y3,
				      x4,
				      y4,
				      src_image,
				      src_left,
				      src_top,
				      src_width,
				      src_height,
				      alpha);
}

void
render_image_3d_add(
	float x1,
	float y1,
	float x2,
	float y2,
	float x3,
	float y3,
	float x4,
	float y4,
	struct image *src_image,
	int src_left,
	int src_top,
	int src_width,
	int src_height,
	int alpha)
{
	opengl_render_image_3d_add(x1,
				   y1,
				   x2,
				   y2,
				   x3,
				   y3,
				   x4,
				   y4,
				   src_image,
				   src_left,
				   src_top,
				   src_width,
				   src_height,
				   alpha);
}

bool make_save_directory(void)
{
	return true;
}

char *make_valid_path(const char *dir, const char *fname)
{
	/* stub */
	return strdup("");
}

void reset_lap_timer(uint64_t *t)
{
	struct timeval tv;

	gettimeofday(&tv, NULL);

	*t = (uint64_t)(tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

uint64_t get_lap_timer_millisec(uint64_t *t)
{
	struct timeval tv;
	uint64_t end;
	
	gettimeofday(&tv, NULL);

	end = (uint64_t)(tv.tv_sec * 1000 + tv.tv_usec / 1000);

	return (uint64_t)(end - *t);
}

bool exit_dialog(void)
{
	/* stub */
	return true;
}

bool title_dialog(void)
{
	/* stub */
	return true;
}

bool delete_dialog(void)
{
	/* stub */
	return true;
}

bool overwrite_dialog(void)
{
	/* stub */
	return true;
}

bool default_dialog(void)
{
	/* stub */
	return true;
}

bool play_video(const char *fname, bool is_skippable)
{
	char *path;

	path = make_real_path(fname);

	EM_ASM_({
		document.getElementById("canvas").style.display = "none";

		var v = document.getElementById("video");
		v.style.display = "block";
		v.src = s2GetFileURL(Module.UTF8ToString($0));
		v.load();
		v.addEventListener('ended', function() {
			document.getElementById("canvas").style.display = "block";
			document.getElementById("video").style.display = "none";
		});
		v.play();
	}, path);

	free(path);

	return true;
}

void stop_video(void)
{
	EM_ASM_({
		var c = document.getElementById("canvas");
		c.style.display = "block";

		var v = document.getElementById("video");
		v.style.display = "none";
		v.pause();
		v.src = "";
		v.load();
	});
}

bool is_video_playing(void)
{
	int ended;

	ended = EM_ASM_INT({
		var v = document.getElementById("video");
		return v.ended;
	});

	return !ended;
}

bool is_full_screen_supported(void)
{
	return false;
}

bool is_full_screen_mode(void)
{
	return false;
}

void enter_full_screen_mode(void)
{
	/* stub */
}

void leave_full_screen_mode(void)
{
	/* stub */
}

const char *get_system_locale(void)
{
	int lang_code;

	lang_code = EM_ASM_INT({
		if (window.navigator.language.startsWith("ja"))
			return 0;
		return 1;
	});

	if (lang_code == 0)
		return "ja";

	return "en";
}

void finish_frame_io(void)
{
	opengl_start_rendering();
}

/*
 * Get a system language.
 */
const char *get_lang_code(void)
{
	return lang_code;
}

EM_JS(int, get_system_lang_code, (void), {
	if (window.navigator.language.startsWith("en"))
		return 0;
	if (window.navigator.language.startsWith("fr"))
		return 1;
	if (window.navigator.language.startsWith("de"))
		return 2;
	if (window.navigator.language.startsWith("it"))
		return 3;
	if (window.navigator.language.startsWith("es"))
		return 4;
	if (window.navigator.language.startsWith("el"))
		return 5;
	if (window.navigator.language.startsWith("ru"))
		return 6;
	if (window.navigator.language.startsWith("zh_CN"))
		return 7;
	if (window.navigator.language.startsWith("zh_TW"))
		return 8;
	if (window.navigator.language.startsWith("ja"))
		return 9;
	return -1;
});
static void init_lang_code(void)
{
	switch (get_system_lang_code()) {
	case 0:
		lang_code = "en";
		break;
	case 1:
		lang_code = "fr";
		break;
	case 2:
		lang_code = "de";
		break;
	case 3:
		lang_code = "it";
		break;
	case 4:
		lang_code = "es";
		break;
	case 5:
		lang_code = "el";
		break;
	case 6:
		lang_code = "ru";
		break;
	case 7:
		lang_code = "zh_CN";
		break;
	case 8:
		lang_code = "zh_TW";
		break;
	case 9:
		lang_code = "ja";
		break;
	default:
		lang_code = "en";
		break;
	}
}

void set_continuous_swipe_enabled(bool is_enabled)
{
	is_continuous_swipe_enabled = is_enabled;
}
