/* -*- coding: utf-8; tab-width: 8; indent-tabs-mode: t; -*- */

/*
 * Copyright (c) 2025, Awe Morris. All rights reserved.
 */

#ifndef PLAYFIELD_PLAYFIELD_H
#define PLAYFIELD_PLAYFIELD_H

#include <playfield/c89compat.h>
#include <stratohal/platform.h>

/*
 * C API
 */

struct image;

/*
 * Create a color texture.
 */
bool
playfield_create_color_texture(
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
playfield_load_texture(
	const char *fname,
	int *ret,
	int *width,
	int *height);

/*
 * Destroy a texture.
 */
void
playfield_destroy_texture(
	int tex_id);

/*
 * Render a texture.
 */
void
playfield_render_texture(
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
playfield_render_texture_3d(
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
playfield_draw(
	int tex_id,
	int x,
	int y);

/*
 * Load a font.
 */
bool
playfield_load_font(
	int slot,
	const char *file);

/*
 * Create a text texture.
 */
bool
playfield_create_text_texture(
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
playfield_play_sound(
	int stream,
	const char *file);

/*
 * Stop a sound on a stream.
 */
bool
playfield_stop_sound(
	int stream);

/*
 * Set a sound volume on a stream.
 */
bool
playfield_set_volume(
	int stream,
	float val);

/*
 * Move to a tag file.
 */
bool
playfield_move_to_tag_file(
	const char *file);

/*
 * Move to a next tag.
 */
void
playfield_move_to_next_tag(void);

/*
 * Write save data.
 */
bool
playfield_write_save_data(
	const char *key,
	const void *data,
	size_t size);

/*
 * Read save data.
 */
bool
playfield_read_save_data(
	const char *key,
	void *data,
	size_t size,
	size_t *ret);

/*
 * Check whether save data exist or not.
 */
bool
playfield_check_save_data(
	const char *key);

/*
 * Call a VM function.
 */
bool call_vm_function(const char *func_name);

/*
 * Call a VM tag function.
 */
bool call_vm_tag_function(bool *tag_end);

/*
 * Set a VM integer.
 */
bool set_vm_int(const char *prop_name, int val);

/*
 * Get a VM integer.
 */
bool get_vm_int(const char *prop_name, int *val);

/*
 * Get the heap usage.
 */
size_t get_heap_usage(void);

/*
 * Do a fast GC.
 */
void fast_gc(void);

/*
 * Do a full GC.
 */
void full_gc(void);

/*
 * Load a tag file.
 */
bool load_tag_file(const char *file);

/*
 * Get a tag file name.
 */
const char *get_tag_file_name(void);

/*
 * Get a tag line.
 */
int get_tag_line(void);

/*
 * Get a current tag.
 */
struct tag *get_current_tag(void);

/*
 * Move to the next tag.
 */
void move_to_next_tag(void);

#endif
