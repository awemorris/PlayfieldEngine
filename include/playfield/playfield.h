/* -*- coding: utf-8; tab-width: 8; indent-tabs-mode: t; -*- */

/*
 * Playfield Engine
 * Copyright (c) 2025, 2026, Awe Morris. All rights reserved.
 */

/*
 * Playfield Engine C API
 */

#ifndef PLAYFIELD_PLAYFIELD_H
#define PLAYFIELD_PLAYFIELD_H

#include <playfield/c89compat.h>
#include <stratohal/platform.h>
#include <noct/noct.h>

/*
 * Texture
 */

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
 * Rendering
 */

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
 * Font
 */

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
 * Sound
 */

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
 * Save Data
 */

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
 * VM
 */

/*
 * Get the VM environment.
 */
NoctEnv *
playfield_get_vm_env(void);

/*
 * Call a VM function.
 */
bool
playfield_call_vm_function(
	const char *func_name);

/*
 * Call a VM tag function.
 */
bool
playfield_call_vm_tag_function(
	bool *tag_end);

/*
 * Set a VM integer.
 */
bool
playfield_set_vm_int(
	const char *prop_name,
	int val);

/*
 * Get a VM integer.
 */
bool
playfield_get_vm_int(
	const char *prop_name,
	int *val);

/*
 * Tag
 */

/*
 * Load a tag file and move to it.
 */
bool
playfield_move_to_tag_file(
	const char *file);

/*
 * Move to the next tag.
 */
bool
playfield_move_to_next_tag(void);

/*
 * Get the current tag file name.
 */
const char *
playfield_get_tag_file(void);

/*
 * Get the line number of the current tag.
 */
int
playfield_get_tag_line(void);

/*
 * Get the name of the current tag.
 */
const char*
playfield_get_tag_name(void);

/*
 * Get the property count of the current tag.
 */
int
playfield_get_tag_property_count(void);

/*
 * Get the property name of the current tag.
 */
const char *
playfield_get_tag_property_name(
	int index);

/*
 * Get the property value of the current tag.
 */
const char *
playfield_get_tag_property_value(
	int index);

#endif
