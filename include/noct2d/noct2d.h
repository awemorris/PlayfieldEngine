/* -*- coding: utf-8; tab-width: 8; indent-tabs-mode: t; -*- */

/*
 * Copyright (c) 2025, Awe Morris. All rights reserved.
 */

#ifndef NOCT2D_NOCT2D_H
#define NOCT2D_NOCT2D_H

#include <noct2d/c89compat.h>
#include <stratohal/platform.h>

/*
 * C API
 */

struct image;

/*
 * Load a texture.
 */
bool
noct2d_load_texture(
	const char *fname,
	int *ret,
	int *width,
	int *height);

/*
 * Destroy a texture.
 */
void
noct2d_destroy_texture(
	int tex_id);

/*
 * Render a texture.
 */
void
noct2d_render_texture(
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
noct2d_draw(
	int tex_id,
	int x,
	int y);

/*
 * Load a font.
 */
bool
noct2d_load_font(
	int slot,
	const char *file);

/*
 * Create a text texture.
 */
bool
noct2d_create_text_texture(
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
noct2d_play_sound(
	int stream,
	const char *file);

/*
 * Stop a sound on a stream.
 */
bool
noct2d_stop_sound(
	int stream);

/*
 * Set a sound volume on a stream.
 */
bool
noct2d_set_volume(
	int stream,
	float val);

/*
 * Move to a tag file.
 */
bool
noct2d_move_to_tag_file(
	const char *file);

/*
 * Move to a next tag.
 */
void
noct2d_move_to_next_tag(void);

#endif
