/* -*- coding: utf-8; tab-width: 8; indent-tabs-mode: t; -*- */

/*
 * Copyright (c) 2025, Awe Morris. All rights reserved.
 */

/*
 * Main header.
 */

#ifndef ENGINE_ENGINE_H
#define ENGINE_ENGINE_H

/* StratoHAL */
#include "stratohal/platform.h"

/* NoctLang */
#include <noct/noct.h>

/* Standard C */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

/* The file name of the startup file. */
#define STARTUP_FILE	"main.ns"

/*
 * C API
 */

/* Maximum properties in a tag. */
#define PROP_MAX	128

/* Command struct. */
struct tag {
	char *tag_name;
	int prop_count;
	char *prop_name[PROP_MAX];
	char *prop_value[PROP_MAX];
	int line;
};

/* Load a file content. */
bool load_file(const char *file, char **buf, size_t *size);

/* Create a texture. (for font drawing) */
bool create_texture(int width, int height, int *ret, struct image **img);

/* Load a texture. */
bool load_texture(const char *fname, int *ret, int *width, int *height);

/* Destroy a texture. */
void destroy_texture(int tex_id);

/* Render a texture. */
void render_texture(int dst_left, int dst_top, int dst_width, int dst_height,
		    int tex_id, int src_x, int src_y, int src_width,
		    int src_height, int alpha);

/* Load a font. */
bool load_font(int slot, const char *file);

/* Convert a color code to a pixel value. */
pixel_t color_code_to_pixel_value(const char *code);

/* Create a text texture. */
bool create_text_texture(int slot, const char *text, int size, pixel_t color,
			 int *tex_id, int *width, int *height);

/* Play a sound on a stream. */
bool play_sound_stream(int stream, const char *file);

/* Stop a sound on a stream. */
bool stop_sound_stream(int stream);

/* Set a sound volume on a stream. */
bool set_stream_volume(int stream, float val);

/* Move to a tag file. */
bool move_to_tag_file(const char *file);

/* Move to a next tag. */
void move_to_next_tag(void);

/* Get a tag file name. */
const char *get_tag_file_name(void);

/* Get a tag line. */
int get_tag_line(void);

/* Get a current tag. */
struct tag *get_current_tag(void);

/* Clean up tag data. */
void cleanup_tag(void);

#endif
