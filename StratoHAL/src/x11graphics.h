/* -*- tab-width: 8; indent-tabs-mode: t; -*- */

/*
 * Copyright (c) 2025, Awe Morris. All rights reserved.
 */

/*
 * X11 Graphics Abstraction
 */

#ifndef CAMINANTE_PLATFORM_X11GRAPHICS_H
#define CAMINANTE_PLATFORM_X11GRAPHICS_H

#include <X11/Xlib.h>

/* Color Format */
#define DEPTH		(24)
#define BPP		(32)

extern Display *display;
extern Window window;

extern bool init_x11_graphics(int width, int height);
extern void cleanup_x11_graphics(void);
extern void start_x11_rendering(void);
extern void end_x11_rendering(void);

#endif
