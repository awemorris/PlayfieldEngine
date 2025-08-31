/* -*- coding: utf-8; tab-width: 8; indent-tabs-mode: t; -*- */

/*
 * Copyright (c) 2025, Awe Morris. All rights reserved.
 */

#ifndef PICOPICO_NOCT2D_H
#define PICOPICO_NOCT2D_H

#include <picopico/c89compat.h>
#include <stratohal/platform.h>

/*
 * C API
 */

struct image;

/*
 * Create a color texture.
 */
bool
picopico_create_color_texture(
	int width,
	int height,
	int r,
	int g,
	int b,
	int a,
	int *ret);

/*
 * Load a texture.
 */
bool
picopico_load_texture(
	const char *fname,
	int *ret,
	int *width,
	int *height);

/*
 * Destroy a texture.
 */
void
picopico_destroy_texture(
	int tex_id);

/*
 * Render a texture.
 */
void
picopico_render_texture(
	int dst_left,
	int dst_top,
	int dst_width,
	int dst_height,
	int tex_id,
	int src_x,
	int src_y,
	int src_width,
	int src_height,
	int alpha);

/*
 * Render a texture.
 */
void
picopico_render_texture_3d(
	float x1,
	float y1,
	float x2,
	float y2,
	float x3,
	float y3,
	float x4,
	float y4,
	int tex_id,
	int src_left,
	int src_top,
	int src_width,
	int src_height,
	int alpha);

/*
 * Render a texture.
 */
void
picopico_draw(
	int tex_id,
	int x,
	int y);

/*
 * Load a font.
 */
bool
picopico_load_font(
	int slot,
	const char *file);

/*
 * Create a text texture.
 */
bool
picopico_create_text_texture(
	int slot,
	const char *text,
	int size,
	pixel_t color,
	int *tex_id,
	int *width,
	int *height);

/*
 * Play a sound on a stream.
 */
bool
picopico_play_sound(
	int stream,
	const char *file);

/*
 * Stop a sound on a stream.
 */
bool
picopico_stop_sound(
	int stream);

/*
 * Set a sound volume on a stream.
 */
bool
picopico_set_volume(
	int stream,
	float val);

/*
 * Move to a tag file.
 */
bool
picopico_move_to_tag_file(
	const char *file);

/*
 * Move to a next tag.
 */
void
picopico_move_to_next_tag(void);

#endif
