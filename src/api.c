/* -*- coding: utf-8; tab-width: 8; indent-tabs-mode: t; -*- */

/*
 * Copyright (c) 2025, Awe Morris. All rights reserved.
 */

/*
 * C API
 */

#include <playfield/playfield.h>

#include "engine.h"
#include "common.h"
#include "tag.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define TEXTURE_COUNT	(256)

/* Texture Struct */
struct texture_entry {
	bool is_used;
	struct image *img;
};

/* Texture table. */
static struct texture_entry tex_tbl[TEXTURE_COUNT];

/* Wave table. */
static struct wave *wave_tbl[SOUND_TRACKS];

/* Forward Declaration */
static int search_free_entry(void);
static bool create_texture(int width, int height, int *ret, struct image **img);
static char *make_save_file_name(const char *key);
static char get_hex_char(int val);

/*
 * Initialization
 */

/*
 * Initialize the API.
 */
bool
init_api(void)
{
	return true;
}

/*
 * Cleanup the API.
 */
void
cleanup_api(void)
{
	int i;

	for (i = 0; i < TEXTURE_COUNT; i++) {
		if (tex_tbl[i].is_used) {
			tex_tbl[i].is_used = false;
			destroy_image(tex_tbl[i].img);
		}
	}
	
}

/*
 * Texture
 */

/*
 * Load a texture.
 */
bool
playfield_load_texture(
	const char *fname,
	int *ret,
	int *width,
	int *height)
{
	int index;
	const char *ext;
	char *data;
	size_t size;

	/* Allocate a texture entry. */
	index = search_free_entry();
	if (index == -1) {
		log_error("Too many textures.");
		return false;
	}

	/* Get a file extension. */
	ext = strrchr(fname, '.');
	if (ext == NULL) {
		log_error(PPS_TR("Cannot determine the file type for \"%s\"."), fname);
		return false;
	}

	/* Load a file content. */
	if (!load_file(fname, &data, &size))
		return false;

	/* Load an image. */
	if (strcmp(ext, ".jpg") == 0 ||
	    strcmp(ext, ".JPG") == 0 ||
	    strcmp(ext, ".jpeg") == 0 ||
	    strcmp(ext, ".JPEG") == 0) {
		if (!create_image_with_webp((const uint8_t *)data, size, &tex_tbl[index].img)) {
			log_error(PPS_TR("Cannot load an image \"%s\"."), fname);
			return false;
		}
	} else if (strcmp(ext, ".webp") == 0 ||
		   strcmp(ext, ".WebP") == 0 ||
		   strcmp(ext, ".WEBP") == 0) {
		if (!create_image_with_webp((const uint8_t *)data, size, &tex_tbl[index].img)) {
			log_error(PPS_TR("Cannot load an image \"%s\"."), fname);
			return false;
		}
	} else {
		if (!create_image_with_png((const uint8_t *)data, size, &tex_tbl[index].img)) {
			log_error(PPS_TR("Cannot load an image \"%s\"."), fname);
			return false;
		}
	}
	free(data);

	/* Fill alpha channel. */
	notify_image_update(tex_tbl[index].img);

	/* Mark as used. */
	tex_tbl[index].is_used = true;

	/* Succeeded. */
	*ret = index;
	*width = tex_tbl[index].img->width;
	*height = tex_tbl[index].img->height;
	return true;
}

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
	int *ret)
{
	int index;

	/* Allocate a texture entry. */
	index = search_free_entry();
	if (index == -1) {
		log_error("Too many textures.");
		return false;
	}

	/* Create an image. */
	if (!create_image(width, height, &tex_tbl[index].img))
		return false;

	/* Mark as used. */
	tex_tbl[index].is_used = true;
	tex_tbl[index].img = tex_tbl[index].img;

	/* Clear the image. */
	clear_image(tex_tbl[index].img, make_pixel(a, r, g, b));
	notify_image_update(tex_tbl[index].img);

	/* Succeeded. */
	*ret = index;

	return true;
}

/* Create a texture. (for font drawing) */
static bool
create_texture(
	int width,
	int height,
	int *ret,
	struct image **img)
{
	int index;

	/* Allocate a texture entry. */
	index = search_free_entry();
	if (index == -1) {
		log_error(PPS_TR("Too many textures."));
		return false;
	}

	/* Create an image. */
	if (!create_image(width, height, img))
		return false;
	
	memset((*img)->pixels, 0, width * height * 4);

	/* Mark as used. */
	tex_tbl[index].is_used = true;
	tex_tbl[index].img = *img;

	/* Succeeded. */
	*ret = index;

	return true;
}

/* Search a free texture index. */
static int
search_free_entry(void)
{
	int i;

	for (i = 0; i < TEXTURE_COUNT; i++) {
		if (!tex_tbl[i].is_used)
			return i;
	}
	return -1;
}

/*
 * Destroy a texture.
 */
void
playfield_destroy_texture(
	int tex_id)
{
	assert(tex_id >= 0);
	assert(tex_id < TEXTURE_COUNT);
	assert(tex_tbl[tex_id].is_used);
	assert(tex_tbl[tex_id].img != NULL);

	/* Mark as used. */
	tex_tbl[tex_id].is_used = false;
	destroy_image(tex_tbl[tex_id].img);
}

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
	int src_left,
	int src_top,
	int src_width,
	int src_height,
	int alpha)
{
	struct texture_entry *t;

	assert(tex_id >= 0 &&  tex_id < TEXTURE_COUNT);

	t = &tex_tbl[tex_id];
	assert(t->is_used);
	assert(t->img != NULL);

	render_image_normal(dst_left,
			    dst_top,
			    dst_width,
			    dst_height,
			    t->img,
			    src_left,
			    src_top,
			    src_width,
			    src_height,
			    alpha);
}

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
	int alpha)
{
	struct texture_entry *t;

	assert(tex_id >= 0 &&  tex_id < TEXTURE_COUNT);

	t = &tex_tbl[tex_id];
	assert(t->is_used);
	assert(t->img != NULL);

	render_image_3d_normal(x1, y1, x2, y2, x3, y3, x4, y4,
			       t->img,
			       src_left, src_top, src_width, src_height,
			       alpha);
}

/*
 * Render a texture.
 */
void
playfield_draw(
	int tex_id,
	int x,
	int y)
{
	struct texture_entry *t;

	assert(tex_id >= 0 &&  tex_id < TEXTURE_COUNT);

	t = &tex_tbl[tex_id];
	assert(t->is_used);
	assert(t->img != NULL);

	render_image_normal(x,
			    y,
			    t->img->width,
			    t->img->height,
			    t->img,
			    0,
			    0,
			    t->img->width,
			    t->img->height,
			    255);
}

/*
 * Font
 */

/*
 * Load a font file to a font slot.
 */
bool
playfield_load_font(
	int slot,
	const char *file)
{
	uint8_t *data;
	size_t len;

	/* Check the font slot index. */
	if (slot < 0 || slot >= GLYPH_DATA_COUNT) {
		log_error(PPS_TR("Invalid font slot index."));
		return false;
	}

	/* Load the file content. */
	if (!load_file(file, (char **)&data, &len))
		return false;

	/* Load the glyph date. */
	if (!load_glyph_data(slot, data, len)) {
		free(data);
		return false;
	}
	free(data);

	return true;
}

/*
 * Convert a color code (#rrggbb) to a pixel value.
 */
pixel_t color_code_to_pixel_value(const char *code)
{
	uint32_t r, g, b;
	pixel_t cl;
	int rgb;

	if (code[0] != '#')
		return 0;

	/* Read a color string. */
	rgb = 0;
	(void)sscanf(code, "%x", &rgb);
	r = (rgb >> 16) & 0xff;
	g = (rgb >> 8) & 0xff;
	b = rgb & 0xff;
	cl = make_pixel(0xff, r, g, b);

	return cl;
}

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
	int *height)
{
	struct image *img;
	int w, h;
	int x, y;
	int tid;

	/* Get the rendered width and height of the text. */
	get_string_width_and_height(slot, size, text, &w, &h);
	if (w == 0)
		w = 1;
	if (h == 0)
		h = 1;

	/* Create a texture. */
	if (!create_texture(w, h, &tid, &img))
		return false;

	/* Draw for each character. */
	x = 0;
	y = 0;
	while (*text != '\0') {
		uint32_t codepoint;
		int mblen;
		int cw, ch;

		/* Get a character. */
		mblen = utf8_to_utf32(text, &codepoint);
		if (mblen == -1)
			return -1;

		/* Get a character width. */
		draw_glyph(img,
			   slot,
			   size, 	/* font size */
			   size, 	/* base size */
			   0,		/* outline size */
			   x,
			   y,
			   color,
			   0,		/* outline color */
			   codepoint,
			   &cw,
			   &ch,
			   false);
		x += cw;

		/* Move to a next character. */
		text += mblen;
	}

	*tex_id = tid;
	*width = w;
	*height = h;

	return true;
}

/*
 * Sound
 */

/*
 * Play a sound file on a stream.
 */
bool
playfield_play_sound(
	int stream,
	const char *file)
{
	if (stream < 0 || stream >= SOUND_TRACKS) {
		log_error(PPS_TR("Invalid sound stream index."));
		return false;
	}

	wave_tbl[stream] = create_wave_from_file(file, false);
	if (wave_tbl[stream] == NULL)
		return false;

	if (!play_sound(stream, wave_tbl[stream]))
		return false;

	return true;
}

/*
 * Stop the sound on a stream.
 */
bool
playfield_stop_sound(
	int stream)
{
	if (stream < 0 || stream >= SOUND_TRACKS) {
		log_error(PPS_TR("Invalid sound stream index."));
		return false;
	}

	stop_sound(stream);

	destroy_wave(wave_tbl[stream]);
	wave_tbl[stream] = NULL;

	return true;
}

/*
 * Set the sound volume on a stream.
 */
bool
playfield_set_sound_volue(
	int stream,
	float vol)
{
	if (stream < 0 || stream >= SOUND_TRACKS) {
		log_error(PPS_TR("Invalid sound stream index."));
		return false;
	}

	set_sound_volume(stream, vol);

	return true;
}

/*
 * Tag
 */

/*
 * Load a tag file and move to it.
 */
bool
playfield_move_to_tag_file(
	const char *file)
{
	/* Load the tag file. */
	if (!load_tag_file(file))
		return false;

	return true;
}

/*
 * Move to a next tag.
 */
void
playfield_move_to_next_tag(void)
{
	move_to_next_tag();
}

/*
 * Write save data.
 */
bool
playfield_write_save_data(
	const char *key,
	const void *data,
	size_t size)
{
	char *fname;
	struct wfile *wf;
	size_t ret;

	/* Make a save file name. */
	fname = make_save_file_name(key);
	if (fname == NULL) {
		log_error(PPS_TR("Save data key too long."));
		return false;
	}

	/* Make the save directory. */
	if (!make_save_directory()) {
		log_error(PPS_TR("Cannot make the save directory."));
		free(fname);
		return false;
	}

	/* Open a save file. */
	if (!open_wfile(fname, &wf)) {
		log_error(PPS_TR("Cannot open a save file."));
		free(fname);
		return false;
	}
	free(fname);

	/* Write data to the save file. */
	if (!write_wfile(wf, data, size, &ret)) {
		log_error(PPS_TR("Cannot write to a save file."));
		return false;
	}

	/* Close the save file. */
	close_wfile(wf);

	return true;
}

/*
 * Read save data.
 */
bool
playfield_read_save_data(
	const char *key,
	void *data,
	size_t size,
	size_t *ret)
{
	char *fname;
	struct rfile *rf;

	/* Make a save file name. */
	fname = make_save_file_name(key);
	if (fname == NULL) {
		log_error(PPS_TR("Save data key too long."));
		return false;
	}

	/* Open a save file. */
	if (!open_rfile(fname, &rf)) {
		log_error(PPS_TR("Cannot open a save file."));
		free(fname);
		return false;
	}
	free(fname);

	/* Enable de-obfuscation. */
	decode_rfile(rf);

	/* Get a file size. */
	if (!get_rfile_size(rf, ret)) {
		log_error(PPS_TR("Cannot get the size of a save file."));
		return false;
	}
	if (size < *ret) {
		log_error(PPS_TR("Save file too large."));
		return false;
	}

	/* Read data to the save file. */
	if (!read_rfile(rf, data, *ret, ret)) {
		log_error(PPS_TR("Cannot read a save file."));
		return false;
	}

	/* Close the save file. */
	close_rfile(rf);

	return true;
}

/*
 * Check whether save data exist or not.
 */
bool
playfield_check_save_data(
	const char *key)
{
	char *fname;
	bool ret;

	/* Make a save file name. */
	fname = make_save_file_name(key);
	if (fname == NULL) {
		log_error(PPS_TR("Save data key too long."));
		return false;
	}

	ret = check_file_exist(fname);
	free(fname);

	return ret;
}

/* Make a save file name correspond to a key string. */
static char *
make_save_file_name(
	const char *key)
{
	char buf[1024];
	int i, len, pos;

	strcpy(buf, SAVE_DIR "/");

	len = strlen(key);
	if (len * 2 > sizeof(buf) - strlen(buf) - 1) {
		/* File name too long. */
		return NULL;
	}

	pos = strlen(buf);
	for (i = 0; i < len; i++) {
		buf[pos + 0] = get_hex_char(key[i] >> 4);
		buf[pos + 1] = get_hex_char(key[i] & 4);
		pos += 2;
	}
	buf[pos] = '\0';

	return strdup(buf);
}

/* Get a hex character. */
static char get_hex_char(int val)
{
	switch (val) {
	case 0:
		return '0';
	case 1:
		return '1';
	case 2:
		return '2';
	case 3:
		return '3';
	case 4:
		return '4';
	case 5:
		return '5';
	case 6:
		return '6';
	case 7:
		return '7';
	case 8:
		return '8';
	case 9:
		return '9';
	case 10:
		return 'a';
	case 11:
		return 'b';
	case 12:
		return 'c';
	case 13:
		return 'd';
	case 14:
		return 'e';
	case 15:
		return 'f';
	default:
		break;
	}
	assert(0);
	return -1;
}
