/* -*- tab-width: 8; indent-tabs-mode: t; -*- */

/*
 * Copyright (c) 2025, Awe Morris. All rights reserved.
 */

/*
 * X11 Graphics Implementation for OpenGL
 */

#if defined(USE_X11_OPENGL)

/* HAL */
#include "stratohal/platform.h"	/* Public Interface */
#include "x11graphics.h"		/* X11 Graphics */

/* OpenGL */
#include <GL/gl.h>			/* OpenGL */
#include <GL/glx.h>			/* GLX */
#include "glrender.h"			/* OpenGL Compatibility Helper */

/* GLX Objects */
static GLXWindow glx_window = None;
static GLXContext glx_context = None;

/* OpenGL 3.0 API */
GLuint (APIENTRY *glCreateShader)(GLenum type);
void (APIENTRY *glShaderSource)(GLuint shader, GLsizei count, const GLchar *const*string, const GLint *length);
void (APIENTRY *glCompileShader)(GLuint shader);
void (APIENTRY *glGetShaderiv)(GLuint shader, GLenum pname, GLint *params);
void (APIENTRY *glGetShaderInfoLog)(GLuint shader, GLsizei bufSize, GLsizei *length, GLchar *infoLog);
void (APIENTRY *glAttachShader)(GLuint program, GLuint shader);
void (APIENTRY *glLinkProgram)(GLuint program);
void (APIENTRY *glGetProgramiv)(GLuint program, GLenum pname, GLint *params);
void (APIENTRY *glGetProgramInfoLog)(GLuint program, GLsizei bufSize, GLsizei *length, GLchar *infoLog);
GLuint (APIENTRY *glCreateProgram)(void);
void (APIENTRY *glUseProgram)(GLuint program);
void (APIENTRY *glGenVertexArrays)(GLsizei n, GLuint *arrays);
void (APIENTRY *glBindVertexArray)(GLuint array);
void (APIENTRY *glGenBuffers)(GLsizei n, GLuint *buffers);
void (APIENTRY *glBindBuffer)(GLenum target, GLuint buffer);
GLint (APIENTRY *glGetAttribLocation)(GLuint program, const GLchar *name);
void (APIENTRY *glVertexAttribPointer)(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void *pointer);
void (APIENTRY *glEnableVertexAttribArray)(GLuint index);
GLint (APIENTRY *glGetUniformLocation)(GLuint program, const GLchar *name);
void (APIENTRY *glUniform1i)(GLint location, GLint v0);
void (APIENTRY *glBufferData)(GLenum target, GLsizeiptr size, const void *data, GLenum usage);
void (APIENTRY *glDeleteShader)(GLuint shader);
void (APIENTRY *glDeleteProgram)(GLuint program);
void (APIENTRY *glDeleteVertexArrays)(GLsizei n, const GLuint *arrays);
void (APIENTRY *glDeleteBuffers)(GLsizei n, const GLuint *buffers);
struct API
{
	void **func;
	const char *name;
};
static struct API api[] =
{
	{(void **)&glCreateShader, "glCreateShader"},
	{(void **)&glShaderSource, "glShaderSource"},
	{(void **)&glCompileShader, "glCompileShader"},
	{(void **)&glGetShaderiv, "glGetShaderiv"},
	{(void **)&glGetShaderInfoLog, "glGetShaderInfoLog"},
	{(void **)&glAttachShader, "glAttachShader"},
	{(void **)&glLinkProgram, "glLinkProgram"},
	{(void **)&glGetProgramiv, "glGetProgramiv"},
	{(void **)&glGetProgramInfoLog, "glGetProgramInfoLog"},
	{(void **)&glCreateProgram, "glCreateProgram"},
	{(void **)&glUseProgram, "glUseProgram"},
	{(void **)&glGenVertexArrays, "glGenVertexArrays"},
	{(void **)&glBindVertexArray, "glBindVertexArray"},
	{(void **)&glGenBuffers, "glGenBuffers"},
	{(void **)&glBindBuffer, "glBindBuffer"},
	{(void **)&glGetAttribLocation, "glGetAttribLocation"},
	{(void **)&glVertexAttribPointer, "glVertexAttribPointer"},
	{(void **)&glEnableVertexAttribArray, "glEnableVertexAttribArray"},
	{(void **)&glGetUniformLocation, "glGetUniformLocation"},
	{(void **)&glUniform1i, "glUniform1i"},
	{(void **)&glBufferData, "glBufferData"},
	{(void **)&glDeleteShader, "glDeleteShader"},
	{(void **)&glDeleteProgram, "glDeleteProgram"},
	{(void **)&glDeleteVertexArrays, "glDeleteVertexArrays"},
	{(void **)&glDeleteBuffers, "glDeleteBuffers"},
};

bool init_x11_graphics(int width, int height)
{
	int pix_attr[] = {
		GLX_DRAWABLE_TYPE, GLX_WINDOW_BIT,
		GLX_RENDER_TYPE, GLX_RGBA_BIT,
		GLX_DOUBLEBUFFER, True,
		GLX_RED_SIZE, 1,
		GLX_GREEN_SIZE, 1,
		GLX_BLUE_SIZE, 1,
		None
	};
	int ctx_attr[]= {
		GLX_CONTEXT_MAJOR_VERSION_ARB, 2,
		GLX_CONTEXT_MINOR_VERSION_ARB, 0,
		GLX_CONTEXT_FLAGS_ARB, 0,
		GLX_CONTEXT_PROFILE_MASK_ARB, GLX_CONTEXT_CORE_PROFILE_BIT_ARB,
		None
	};
	GLXContext (*glXCreateContextAttribsARB)(Display *dpy,
						 GLXFBConfig config,
						 GLXContext share_context,
						 Bool direct,
						 const int *attrib_list);
	GLXFBConfig *config;
	XVisualInfo *vi;
	XSetWindowAttributes swa;
	XEvent event;
	int i, n;

	/* Choose a framebuffer format. */
	config = glXChooseFBConfig(display, DefaultScreen(display), pix_attr, &n);
	if (config == NULL)
		return false;
	vi = glXGetVisualFromFBConfig(display, config[0]);

	/* Create a window. */
	swa.border_pixel = 0;
	swa.event_mask = StructureNotifyMask;
	swa.colormap = XCreateColormap(display,
				       RootWindow(display, vi->screen),
				       vi->visual,
				       AllocNone);
	window = XCreateWindow(display,
			       RootWindow(display, vi->screen),
			       0,
			       0,
			       (unsigned int)width,
			       (unsigned int)height,
			       0,
			       vi->depth,
			       InputOutput,
			       vi->visual,
			       CWBorderPixel | CWColormap | CWEventMask,
			       &swa);
	XFree(vi);

	/* Create a GLX context. */
	glXCreateContextAttribsARB = (void *)glXGetProcAddress((const unsigned char *)"glXCreateContextAttribsARB");
	if (glXCreateContextAttribsARB == NULL) {
		XDestroyWindow(display, window);
		return false;
	}
	glx_context = glXCreateContextAttribsARB(display, config[0], 0, True, ctx_attr);
	if (glx_context == NULL) {
		XDestroyWindow(display, window);
		return false;
	}

	/* Create a GLX window. */
	glx_window = glXCreateWindow(display, config[0], window, NULL);
	XFree(config);

	/* Map the window to the screen, and wait for showing. */
	XMapWindow(display, window);
	XNextEvent(display, &event);

	/* Bind the GLX context to the window. */
	glXMakeContextCurrent(display, glx_window, glx_window, glx_context);

	/* Get the API pointers. */
	for (i = 0; i < (int)(sizeof(api)/sizeof(struct API)); i++) {
		*api[i].func = (void *)glXGetProcAddress((const unsigned char *)api[i].name);
		if(*api[i].func == NULL) {
			log_info("Failed to get %s", api[i].name);
			glXMakeContextCurrent(display, None, None, None);
			glXDestroyContext(display, glx_context);
			glXDestroyWindow(display, glx_window);
			glx_context = None;
			glx_window = None;
			return false;
		}
	}

	/* Initialize the OpenGL rendering subsystem. */
	if (!init_opengl(width, height)) {
		glXMakeContextCurrent(display, None, None, None);
		glXDestroyContext(display, glx_context);
		glXDestroyWindow(display, glx_window);
		glx_context = None;
		glx_window = None;
		return false;
	}

	return true;
}

void cleanup_x11_graphics(void)
{
	glXMakeContextCurrent(display, None, None, None);
	if (glx_context != None) {
		glXDestroyContext(display, glx_context);
		glx_context = None;
	}
	if (glx_window != None) {
		glXDestroyWindow(display, glx_window);
		glx_window = None;
	}

	cleanup_opengl();
}

void start_x11_rendering(void)
{
	opengl_start_rendering();
}

void end_x11_rendering(void)
{
	opengl_end_rendering();
	glXSwapBuffers(display, glx_window);
}

void notify_image_update(struct image *img)
{
	opengl_notify_image_update(img);
}

void notify_image_free(struct image *img)
{
	opengl_notify_image_free(img);
}

void render_image_normal(int dst_left,
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
	opengl_render_image_normal(dst_left,
				   dst_top,
				   dst_width,
				   dst_height,
				   src_image,
				   src_left,
				   src_top,
				   src_width,
				   src_height,
				   alpha);
}

void render_image_add(int dst_left,
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
	opengl_render_image_add(dst_left,
				dst_top,
				dst_width,
				dst_height,
				src_image,
				src_left,
				src_top,
				src_width,
				src_height,
				alpha);
}

void render_image_dim(int dst_left,
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
	opengl_render_image_dim(dst_left,
				dst_top,
				dst_width,
				dst_height,
				src_image,
				src_left,
				src_top,
				src_width,
				src_height,
				alpha);
}

void render_image_rule(struct image *src_img,
		       struct image *rule_img,
		       int threshold)
{
	opengl_render_image_rule(src_img, rule_img, threshold);
}

void render_image_melt(struct image *src_img,
		       struct image *rule_img,
		       int progress)
{
	opengl_render_image_melt(src_img, rule_img, progress);
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

#endif /* defined(USE_X11_OPENGL) */
