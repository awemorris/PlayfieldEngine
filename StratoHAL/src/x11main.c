/* -*- tab-width: 8; indent-tabs-mode: t; -*- */

/*
 * Copyright (c) 2025, Awe Morris. All rights reserved.
 */

/*
 * X11 Main
 */

/* HAL */
#include "stratohal/platform.h"	/* Public Interface */
#include "stdfile.h"			/* Standard C File Implementation */
#include "x11graphics.h"		/* X11 Graphics Implementation */
#if defined(TARGET_LINUX)
#include "asound.h"			/* ALSA Sound Implemenatation */
#else
#include "bsdsound.h"			/* BSD Sound Implementation */
#endif

/* Xlib */
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/xpm.h>
#include <X11/Xatom.h>
#include <X11/Xlocale.h>

/* POSIX */
#include <sys/types.h>
#include <sys/stat.h>	/* stat(), mkdir() */
#include <sys/time.h>	/* gettimeofday() */
#include <unistd.h>	/* usleep(), access() */

/* Standard C */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <assert.h>

/* Gstreamer Video HAL */
#include "gstplay.h"

/* Log File */
#define LOG_FILE	"log.txt"

/* Save Directory */
#define SAVE_DIR	"save"

/* Frame Time */
#define FRAME_MILLI	(16)	/* Millisec of a frame */
#define SLEEP_MILLI	(5)	/* Millisec to sleep */

/* Window Config */
static char *window_title;
static int window_width;
static int window_height;

/* X11 Objects */
Display *display;
Window window = BadAlloc;
static Pixmap icon = BadAlloc;
static Pixmap icon_mask = BadAlloc;
static Atom delete_message = BadAlloc;

/* Frame Start Time */
static struct timeval tv_start;

/* Log File */
#define LOG_BUF_SIZE	(4096)
static FILE *log_fp;

/* Locale */
const char *noct2d_lang_code;

/* Flag to indicate whether we are playing a video or not */
static bool is_gst_playing;

/* Flag to indicate whether a video is skippable or not */
static bool is_gst_skippable;

/* Icon */
extern char *icon_xpm[35];

/* forward declaration */
static void init_locale(void);
static bool init_hal(int argc, char *argv[]);
static bool open_log_file(void);
static void close_log_file(void);
static bool open_display(void);
static bool set_window_title(void);
static bool show_window(void);
static void set_window_size(void);
static bool set_event_mask(void);
static void set_close_button(void);
static void close_display(void);
static bool setup_window(void);
static bool create_icon_image(void);
static void cleanup_hal(void);
static void destroy_window(void);
static void destroy_icon_image(void);
static void run_game_loop(void);
static bool run_frame(void);
static bool wait_for_next_frame(void);
static bool next_event(void);
static void event_key_press(XEvent *event);
static void event_key_release(XEvent *event);
static int get_key_code(XEvent *event);
static void event_button_press(XEvent *event);
static void event_button_release(XEvent *event);
static void event_motion_notify(XEvent *event);

/*
 * Main
 */
int main(int argc, char *argv[])
{
	/* Initialize HAL. */
	if (!init_hal(argc, argv))
		return 1;

	/* Do a start callback. */
	if (!on_event_start())
		return 1;

	/* Run game loop. */
	run_game_loop();

	/* Do a stop callback.. */
	on_event_stop();

	/* Cleanup HAL. */
	cleanup_hal();

	return 0;
}

/* Initialize the locale. */
static void init_locale(void)
{
	const char *locale;

	locale = setlocale(LC_ALL, "");

	if (locale == NULL || locale[0] == '\0' || locale[1] == '\0')
		noct2d_lang_code = "en";
	else if (strncmp(locale, "en", 2) == 0)
		noct2d_lang_code = "en";
	else if (strncmp(locale, "fr", 2) == 0)
		noct2d_lang_code = "fr";
	else if (strncmp(locale, "de", 2) == 0)
		noct2d_lang_code = "de";
	else if (strncmp(locale, "it", 2) == 0)
		noct2d_lang_code = "it";
	else if (strncmp(locale, "es", 2) == 0)
		noct2d_lang_code = "es";
	else if (strncmp(locale, "el", 2) == 0)
		noct2d_lang_code = "el";
	else if (strncmp(locale, "ru", 2) == 0)
		noct2d_lang_code = "ru";
	else if (strncmp(locale, "zh_CN", 5) == 0)
		noct2d_lang_code = "zh";
	else if (strncmp(locale, "zh_TW", 5) == 0)
		noct2d_lang_code = "tw";
	else if (strncmp(locale, "ja", 2) == 0)
		noct2d_lang_code = "ja";
	else
		noct2d_lang_code = "en";

	setlocale(LC_ALL, "C");
}

/* Initialize HAL. */
static bool init_hal(int argc, char *argv[])
{
	/* Initialize the locale. */
	init_locale();

	/* Initialize the file HAL. */
	if (!init_file())
		return false;

	/* Do a boot callback. */
	if (!on_event_boot(&window_title, &window_width, &window_height))
		return false;

	/* Initialize the sound HAL. */
	if (!init_sound()) {
		/* Ignore a failure. */
		log_warn("Can't initialize sound.\n");
	}

	/* Open an X11 display. */
	if (!open_display()) {
		log_error("Can't open display.\n");
		return false;
	}

	/* Initialize graphics (OpenGL or XImage). */
	if (!init_x11_graphics(window_width, window_height)) {
		log_error("Failed to initialize graphics.");
		return false;
	}

	/* Setup the window created by init_x11_graphics(). */
	if (!setup_window()) {
		log_error("Failed to setup a window.");
		return false;
	}

	/* Create an icon. */
	if (!create_icon_image()) {
		log_error("Can't create icon.\n");
		return false;
	}

	/* Initialize the viddeo HAL. */
	gstplay_init(argc, argv);

	return true;
}

/* Open an X11 display. */
static bool open_display(void)
{
	display = XOpenDisplay(NULL);
	if (display == NULL) {
		log_error("XOpenDisplay() failed.");
		return false;
	}
	return true;
}

/* Setup the window. */
static bool setup_window(void)
{
	/* Set the window title. */
	if (!set_window_title())
		return false;

	/* Show the window. */
	if (!show_window())
		return false;

	/* Set the fixed window size. */
	set_window_size();

	/* Set the event mask. */
	if (!set_event_mask())
		return false;

	/* Capture close button events if possible. */
	set_close_button();

	return true;
}

/* Set the window title. */
static bool set_window_title(void)
{
	XTextProperty tp;
	int ret;

	ret = XmbTextListToTextProperty(display, &window_title, 1, XCompoundTextStyle, &tp);
	if (ret == XNoMemory || ret == XLocaleNotSupported) {
		log_error("XmbTextListToTextProperty() failed.");
		return false;
	}
	XSetWMName(display, window, &tp);
	XFree(tp.value);

	return true;
}

/* Show the window. */
static bool show_window(void)
{
	int ret;

	ret = XMapWindow(display, window);
	if (ret == BadWindow) {
		log_error("XMapWindow() failed.");
		return false;
	}

	return true;
}

/* Set the fixed window size. */
static void set_window_size(void)
{
	XSizeHints *sh;

	sh = XAllocSizeHints();
	sh->flags = PMinSize | PMaxSize;
	sh->min_width = window_width;
	sh->min_height = window_height;
	sh->max_width = window_width;
	sh->max_height = window_height;
	XSetWMSizeHints(display, window, sh, XA_WM_NORMAL_HINTS);
	XFree(sh);
}

/* Set the event mask. */
static bool set_event_mask(void)
{
	int ret;

	ret = XSelectInput(display,
			   window,
			   KeyPressMask |
			   ExposureMask |
			   ButtonPressMask |
			   ButtonReleaseMask |
			   KeyReleaseMask |
			   PointerMotionMask);
	if (ret == BadWindow) {
		log_error("XSelectInput() failed.");
		return false;
	}

	return true;
}

/* Capture close button events if possible. */
static void set_close_button(void)
{
	delete_message = XInternAtom(display, "WM_DELETE_WINDOW", True);
	if (delete_message != None && delete_message != BadAlloc && delete_message != BadValue)
		XSetWMProtocols(display, window, &delete_message, 1);
}

/* Create an icon image. */
static bool create_icon_image(void)
{
	XWMHints *win_hints;
	XpmAttributes attr;
	Colormap cm;
	int ret;

	/* Create a color map. */
	cm = XCreateColormap(display, window,
			     DefaultVisual(display, DefaultScreen(display)),
			     AllocNone);
	if (cm == BadAlloc || cm == BadMatch || cm == BadValue ||
	    cm == BadWindow) {
		log_error("XCreateColorMap() failed.");
		return false;
	}

	/* Create a pixmap. */
	attr.valuemask = XpmColormap;
	attr.colormap = cm;
	ret = XpmCreatePixmapFromData(display, window, icon_xpm, &icon, &icon_mask, &attr);
	if (ret != XpmSuccess) {
		log_error("XpmCreatePixmapFromData() failed.");
		XFreeColormap(display, cm);
		return false;
	}

	/* Allocate for a WMHints. */
	win_hints = XAllocWMHints();
	if (!win_hints) {
		XFreeColormap(display, cm);
		return false;
	}

	/* Set the icon. */
	win_hints->flags = IconPixmapHint | IconMaskHint;
	win_hints->icon_pixmap = icon;
	win_hints->icon_mask = icon_mask;
	XSetWMHints(display, window, win_hints);

	/* Free the temporary objects. */
	XFree(win_hints);
	XFreeColormap(display,cm);
	return true;
}

/* Cleanup the subsystems. */
static void cleanup_hal(void)
{
	/* Cleanup sound. */
	cleanup_sound();

	/* Cleanup gprahics. */
	cleanup_x11_graphics();

	/* Destroy the window. */
	destroy_window();

	/* Destroy the icon. */
	destroy_icon_image();

	/* Close the display. */
	close_display();

	/* Close the log file. */
	close_log_file();
}

/* Destroy the window. */
static void destroy_window(void)
{
	if (display != NULL) {
		if (window != BadAlloc)
			XDestroyWindow(display, window);
	}
}

/* Destroy the icon image. */
static void destroy_icon_image(void)
{
	if (display != NULL) {
		if (icon != BadAlloc)
			XFreePixmap(display, icon);
		if (icon_mask != BadAlloc)
			XFreePixmap(display, icon_mask);
	}
}

/* Close the X11 display. */
static void close_display(void)
{
	if (display != NULL)
		XCloseDisplay(display);
}

/* Close the log file. */
static void close_log_file(void)
{
	if (log_fp != NULL)
		fclose(log_fp);
}

/* Run the event loop. */
static void run_game_loop(void)
{
	/* Get the frame start time. */
	gettimeofday(&tv_start, NULL);

	/* Main Loop */
	while (true) {
		/* Process video playback. */
		if (is_gst_playing) {
			gstplay_loop_iteration();
			if (!gstplay_is_playing()) {
				gstplay_stop();
				is_gst_playing = false;
			}
		}

		/* Run a frame. */
		if (!run_frame())
			break;

		/* Wait for the next frame timing. */
		if (!wait_for_next_frame())
			break;	/* Close button was pressed. */

		/* Get the frame start time. */
		gettimeofday(&tv_start, NULL);
	}
}

/* Run a frame. */
static bool run_frame(void)
{
	bool cont;

	/* Start rendering. */
	if (!is_gst_playing)
		start_x11_rendering();

	/* Call a frame event. */
	cont = on_event_frame();

	/* End rendering. */
	if (!is_gst_playing)
		end_x11_rendering();

	return cont;
}

/* Wait for the next frame timing. */
static bool wait_for_next_frame(void)
{
	struct timeval tv_end;
	uint32_t lap, wait, span;

	span = FRAME_MILLI;

	/* Do event processing and sleep until the time of next frame start. */
	do {
		/* Process events if exist. */
		while (XEventsQueued(display, QueuedAfterFlush) > 0)
			if (!next_event())
				return false;

		/* Get a lap time. */
		gettimeofday(&tv_end, NULL);
		lap = (uint32_t)((tv_end.tv_sec - tv_start.tv_sec) * 1000 +
				 (tv_end.tv_usec - tv_start.tv_usec) / 1000);

		/* Break if the time has come. */
		if (lap > span) {
			tv_start = tv_end;
			break;
		}

		/* Calc a sleep time. */
		wait = (span - lap > SLEEP_MILLI) ? SLEEP_MILLI : span - lap;

		/* Do sleep. */
		usleep(wait * 1000);

	} while(wait > 0);

	return true;
}

/* Process an event. */
static bool next_event(void)
{
	XEvent event;

	XNextEvent(display, &event);
	switch (event.type) {
	case KeyPress:
		event_key_press(&event);
		break;
	case KeyRelease:
		event_key_release(&event);
		break;
	case ButtonPress:
		event_button_press(&event);
		break;
	case ButtonRelease:
		event_button_release(&event);
		break;
	case MotionNotify:
		event_motion_notify(&event);
		break;
	case MappingNotify:
		XRefreshKeyboardMapping(&event.xmapping);
		break;
	case ClientMessage:
		/* Close button was pressed. */
		if ((Atom)event.xclient.data.l[0] == delete_message)
			return false;
		break;
	}
	return true;
}

/* Process a KeyPress event. */
static void event_key_press(XEvent *event)
{
	int key;

	/* Get a key code. */
	key = get_key_code(event);
	if (key == -1)
		return;

	/* Call an event handler. */
	on_event_key_press(key);
}

/* Process a KeyRelease event. */
static void event_key_release(XEvent *event)
{
	int key;

	/* Ignore auto repeat events. */
	if (XEventsQueued(display, QueuedAfterReading) > 0) {
		XEvent next;
		XPeekEvent(display, &next);
		if (next.type == KeyPress &&
		    next.xkey.keycode == event->xkey.keycode &&
		    next.xkey.time == event->xkey.time) {
			XNextEvent(display, &next);
			return;
		}
	}

	/* Get a key code. */
	key = get_key_code(event);
	if (key == -1)
		return;

	/* Call an event handler. */
	on_event_key_release(key);
}

/* Convert 'KeySym' to 'enum key_code'. */
static int get_key_code(XEvent *event)
{
	char text[255];
	KeySym keysym;

	/* Get a KeySym. */
	XLookupString(&event->xkey, text, sizeof(text), &keysym, 0);

	/* Convert to key_code. */
	switch (keysym) {
	case XK_Return:
	case XK_KP_Enter:
		return KEY_RETURN;
	case XK_space:
		return KEY_SPACE;
		break;
	case XK_Control_L:
	case XK_Control_R:
		return KEY_CONTROL;
	case XK_Down:
		return KEY_DOWN;
	case XK_Up:
		return KEY_UP;
	case XK_Left:
		return KEY_LEFT;
	case XK_Right:
		return KEY_RIGHT;
	default:
		break;
	}
	return -1;
}

/* Process a ButtonPress event. */
static void event_button_press(XEvent *event)
{
	/* See the button type and dispatch. */
	switch (event->xbutton.button) {
	case Button1:
		on_event_mouse_press(MOUSE_LEFT,
				     event->xbutton.x,
				     event->xbutton.y);
		break;
	case Button3:
		on_event_mouse_press(MOUSE_RIGHT,
				     event->xbutton.x,
				     event->xbutton.y);
		break;
	case Button4:
		on_event_key_press(KEY_UP);
		on_event_key_release(KEY_UP);
		break;
	case Button5:
		on_event_key_press(KEY_DOWN);
		on_event_key_release(KEY_DOWN);
		break;
	default:
		break;
	}
}

/* Process a ButtonPress event. */
static void event_button_release(XEvent *event)
{
	/* See the button type and dispatch. */
	switch (event->xbutton.button) {
	case Button1:
		on_event_mouse_release(MOUSE_LEFT,
				       event->xbutton.x,
				       event->xbutton.y);
		break;
	case Button3:
		on_event_mouse_release(MOUSE_RIGHT,
				       event->xbutton.x,
				       event->xbutton.y);
		break;
	}
}

/* Process a MotionNotify event. */
static void event_motion_notify(XEvent *event)
{
	/* Call an event handler. */
	on_event_mouse_move(event->xmotion.x, event->xmotion.y);
}

/*
 * HAL
 */

/*
 * Put an INFO log.
 */
bool log_info(const char *s, ...)
{
	char buf[LOG_BUF_SIZE];
	va_list ap;

	va_start(ap, s);
	vsnprintf(buf, sizeof(buf), s, ap);
	va_end(ap);

	open_log_file();
	if (log_fp != NULL) {
		fprintf(log_fp, "%s\n", buf);
		fflush(log_fp);
		if (ferror(log_fp))
			return false;
	}
	printf("%s\n", buf);

	return true;
}

/*
 * Put a WARN log.
 */
bool log_warn(const char *s, ...)
{
	char buf[LOG_BUF_SIZE];
	va_list ap;

	va_start(ap, s);
	vsnprintf(buf, sizeof(buf), s, ap);
	va_end(ap);

	open_log_file();
	if (log_fp != NULL) {
		fprintf(log_fp, "%s\n", buf);
		fflush(log_fp);
		if (ferror(log_fp))
			return false;
	}
	printf("%s\n", buf);

	return true;
}

/*
 * Put an ERROR log.
 */
bool log_error(const char *s, ...)
{
	char buf[LOG_BUF_SIZE];
	va_list ap;

	va_start(ap, s);
	vsnprintf(buf, sizeof(buf), s, ap);
	va_end(ap);

	open_log_file();
	if (log_fp != NULL) {
		fprintf(log_fp, "%s\n", buf);
		fflush(log_fp);
		if (ferror(log_fp))
			return false;
	}
	printf("%s\n", buf);
	
	return true;
}

/*
 * Put an out-of-memory error.
 */
bool log_out_of_memory(void)
{
	log_error("Out of memory.");
	return true;
}

/* Open the log file. */
static bool open_log_file(void)
{
	if (log_fp == NULL) {
		log_fp = fopen(LOG_FILE, "w");
		if (log_fp == NULL) {
			printf("Can't open log file.\n");
			return false;
		}
	}
	return true;
}

/*
 * Make a save directory.
 */
bool make_save_directory(void)
{
	struct stat st = {0};

	if (stat(SAVE_DIR, &st) == -1)
		mkdir(SAVE_DIR, 0700);

	return true;
}

/*
 * Make an effective path from a directory name and a file name.
 */
char *make_real_path(const char *fname)
{
	char *buf;
	size_t len;

	/* Allocate a path buffer. */
	len = strlen(fname) + 1;
	buf = malloc(len);
	if (buf == NULL) {
		log_out_of_memory();
		return NULL;
	}

	/* Copy as is. */
	snprintf(buf, len, "%s", fname);

	return buf;
}

/*
 * Reset a timer.
 */
void reset_lap_timer(uint64_t *t)
{
	struct timeval tv;

	gettimeofday(&tv, NULL);

	*t = (uint64_t)(tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

/*
 * Get a timer lap.
 */
uint64_t get_lap_timer_millisec(uint64_t *t)
{
	struct timeval tv;
	uint64_t end;
	
	gettimeofday(&tv, NULL);

	end = (uint64_t)(tv.tv_sec * 1000 + tv.tv_usec / 1000);

	return (uint64_t)(end - *t);
}

/*
 * Show a exit dialog.
 */
bool exit_dialog(void)
{
	/* stub */
	return true;
}

/*
 * Show a back-to-title dialog.
 */
bool title_dialog(void)
{
	/* stub */
	return true;
}

/*
 * Show a delete confirmation dialog.
 */
bool delete_dialog(void)
{
	/* stub */
	return true;
}

/*
 * Show an overwrite confirmation dialog.
 */
bool overwrite_dialog(void)
{
	/* stub */
	return true;
}

/*
 * Show a reset-to-default dialog.
 */
bool default_dialog(void)
{
	/* stub */
	return true;
}

/*
 * Play a video.
 */
bool play_video(const char *fname, bool is_skippable)
{
	char *path;

	path = make_real_path(fname);

	is_gst_playing = true;
	is_gst_skippable = is_skippable;

	gstplay_play(path, window);

	free(path);

	return true;
}

/*
 * Stop the video.
 */
void stop_video(void)
{
	gstplay_stop();

	is_gst_playing = false;
}

/*
 * Check whether a video is playing.
 */
bool is_video_playing(void)
{
	return is_gst_playing;
}

/*
 * Check whether full screen mode is supported.
 */
bool is_full_screen_supported(void)
{
	return false;
}

/*
 * Check whether we are in full screen mode.
 */
bool is_full_screen_mode(void)
{
	return false;
}

/*
 * Enter full screen mode.
 */
void enter_full_screen_mode(void)
{
	/* stub */
}

/*
 * Leave full screen mode.
 */
void leave_full_screen_mode(void)
{
	/* stub */
}

/*
 * Get the system locale.
 */
const char *get_system_language(void)
{
	return noct2d_lang_code;
}

/*
 * Text-to-speach.
 */
void speak_text(const char *msg)
{
	UNUSED_PARAMETER(msg);
}

/*
 * Enable/disable message skip by touch move.
 */
void set_continuous_swipe_enabled(bool is_enabled)
{
	UNUSED_PARAMETER(is_enabled);
}
