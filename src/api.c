/* -*- coding: utf-8; tab-width: 8; indent-tabs-mode: t; -*- */

/*
 * Copyright (c) 2025, Awe Morris. All rights reserved.
 */

/*
 * C API
 */

#include "engine.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

/*
 * Common
 */

bool load_file(const char *file, char **buf, size_t *size)
{
	struct rfile *f;
	size_t file_size, read_size;

	assert(buf != NULL);

	if (!open_rfile(file, &f)) {
		log_error(_("Cannot open file \"%s\".\n"), file);
		return false;
	}

	if (!get_rfile_size(f, &file_size)) {
		log_error(_("Cannot get the size of file \"%s\"."), file);
		return false;
	}

	if (buf != NULL) {
		*buf = malloc(file_size + 1);
		if (*buf == NULL) {
			log_out_of_memory();
			return false;
		}

		if (!read_rfile(f, *buf, file_size, &read_size)) {
			log_error("Cannot read file \"%s\".", file);
			free(*buf);
			return false;
		}

		(*buf)[file_size] = '\0';
	}

	close_rfile(f);

	if (size != NULL)
		*size = file_size;

	return true;
}

/*
 * Texture
 */

#define TEXTURE_COUNT	(256)

struct texture_entry {
	bool is_used;
	struct image *img;
};

/* Texture table. */
static struct texture_entry tex_tbl[TEXTURE_COUNT];

/* Forward Declaration */
static int search_free_entry(void);

/*
 * Create a texture. (for font drawing)
 */
bool noct2d_create_texture(int width, int height, int *ret, struct image **img)
{
	int index;

	/* Allocate a texture entry. */
	index = search_free_entry();
	if (index == -1) {
		log_error("Too many textures.");
		return false;
	}

	/* Create an image. */
	if (!create_image(width, height, img))
		return false;
	
	/* Mark as used. */
	tex_tbl[index].is_used = true;
	tex_tbl[index].img = *img;

	/* Succeeded. */
	*ret = index;

	return true;
}

/*
 * Load a texture.
 */
bool noct2d_load_texture(const char *fname, int *ret, int *width, int *height)
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
		log_error("Cannot determine a file type for \"%s\".", fname);
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
			log_error("Cannot load an image \"%s\".", fname);
			return false;
		}
	} else if (strcmp(ext, ".webp") == 0 ||
		   strcmp(ext, ".WebP") == 0 ||
		   strcmp(ext, ".WEBP") == 0) {
		if (!create_image_with_webp((const uint8_t *)data, size, &tex_tbl[index].img)) {
			log_error("Cannot load an image \"%s\".", fname);
			return false;
		}
	} else {
		if (!create_image_with_png((const uint8_t *)data, size, &tex_tbl[index].img)) {
			log_error("Cannot load an image \"%s\".", fname);
			return false;
		}
	}
	free(data);

	/* Fill alpha channel. */
	fill_image_alpha(tex_tbl[index].img);
	notify_image_update(tex_tbl[index].img);

	/* Mark as used. */
	tex_tbl[index].is_used = true;

	/* Succeeded. */
	*ret = index;
	*width = tex_tbl[index].img->width;
	*height = tex_tbl[index].img->height;
	return true;
}

/* Search a free texture index. */
static int search_free_entry(void)
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
void noct2d_destroy_texture(int tex_id)
{
	assert(tex_id > 0);
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
noct2d_render_texture(
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
noct2d_draw(
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
bool noct2d_load_font(int slot, const char *file)
{
	uint8_t *data;
	size_t len;

	/* Check the font slot index. */
	if (slot < 0 || slot >= GLYPH_DATA_COUNT) {
		log_error("Invalid font slot index.");
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
bool noct2d_create_text_texture(int slot, const char *text, int size, pixel_t color, int *tex_id, int *width, int *height)
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
	if (!noct2d_create_texture(w, h, &tid, &img))
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

/* Wave table. */
static struct wave *wave_tbl[SOUND_TRACKS];

bool noct2d_play_sound(int stream, const char *file)
{
	if (stream < 0 || stream >= SOUND_TRACKS) {
		log_error("Invalid stream index.");
		return false;
	}

	wave_tbl[stream] = create_wave_from_file(file, false);
	if (wave_tbl[stream] == NULL)
		return false;

	if (!play_sound(stream, wave_tbl[stream]))
		return false;

	return true;
}

bool noct2d_stop_sound(int stream)
{
	if (stream < 0 || stream >= SOUND_TRACKS) {
		log_error("Invalid stream index.");
		return false;
	}

	stop_sound(stream);

	destroy_wave(wave_tbl[stream]);
	wave_tbl[stream] = NULL;

	return true;
}

bool noct2d_set_sound_volue(int stream, float vol)
{
	if (stream < 0 || stream >= SOUND_TRACKS) {
		log_error("Invalid stream index.");
		return false;
	}

	set_sound_volume(stream, vol);

	return true;
}

/*
 * Tag
 */

/* False assertion */
#define NEVER_COME_HERE		0

/* Sizes. */
#define TAG_NAME_MAX	128
#define PROP_NAME_MAX	128
#define PROP_VALUE_MAX	4096
#define COMMAND_MAX	65536

/* Current tag file. */
static char cur_file[1024];

/* Current tag index. */
static int cur_index;

/* Tag table. */
static struct tag tag[COMMAND_MAX];

/* Tag size. */
static int tag_size;

/* Forward declaration. */
static bool parse_tag_document(const char *doc, bool (*callback)(const char *, int, const char **, const char **, int), char **error_msg, int *error_line);
static bool parse_tag_callback(const char *name, int props, const char **prop_name, const char **prop_value, int line);

/*
 * Cleanup the tag module.
 */
void cleanup_tag(void)
{
	struct tag *t;
	int i, j;

	cur_index = 0;

	strcpy(cur_file, "");

	for (i = 0; i < tag_size; i++) {
		t = &tag[i];
		free(t->tag_name);
		for (j = 0; j < PROP_MAX; j++) {
			if (t->prop_name[i] != NULL) {
				free(t->prop_name[i]);
				t->prop_name[i] = NULL;
			}
			if (t->prop_value[i] != NULL) {
				free(t->prop_value[i]);
				t->prop_value[i] = NULL;
			}
		}
	}
}

/* Get a file name of the current tag. */
const char *get_tag_file_name(void)
{
	return &cur_file[0];
}

/* Get a line number of the current tag. */
int get_tag_line(void)
{
	/* If the current tag index is invalid. */
	if (cur_index >= tag_size)
		return -1;
	
	return tag[cur_index].line;
}

/* Get a current tag. */
struct tag *get_current_tag(void)
{
	/* If the current command index is invalid. */
	if (cur_index >= tag_size)
		return NULL;
	
	return &tag[cur_index];
}

/*
 * Load a tag file and move to it.
 */
bool noct2d_move_to_tag_file(const char *file)
{
	char *buf;
	char *error_message;
	int error_line;

	/* Get the file content. */
	if (!load_file(file, &buf, NULL))
		return false;

	/* Destroy the existing commands. */
	cleanup_tag();

	/* Save the file name. */
	strncpy(cur_file, file, sizeof(cur_file) - 1);

	/* Parse the file content. */
	buf = NULL;
	if (!parse_tag_document(buf, parse_tag_callback, &error_message, &error_line)) {
		log_error(_("%s:%d: %s"),  file, error_line, error_message);
		free(buf);
		return false;
	}

	/* Free the file content. */
	free(buf);

	return true;
}

/*
 * Move to a next tag.
 */
void noct2d_move_to_next_tag(void)
{
	cur_index++;
}

/*
 * Tag Document Parser
 */

/* State machine */
enum state {
	ST_INIT,
	ST_TAGNAME,
	ST_PROPNAME,
	ST_PROPVALUE_QUOTE,
	ST_PROPVALUE_BODY,
};

/* Parse a tag document. */
bool
parse_tag_document(
	const char *doc,
	bool (*callback)(const char *, int, const char **, const char **, int),
	char **error_msg,
	int *error_line)
{
	static char tag_name[TAG_NAME_MAX];
	static char prop_name[PROP_MAX][PROP_NAME_MAX];
	static char prop_val[PROP_MAX][PROP_VALUE_MAX];

	const char *top;
	char c;
	int state;
	int line;
	int len;
	int prop_count;
	char *prop_name_tbl[PROP_MAX];
	char *prop_val_tbl[PROP_MAX];
	int i;

	for (i = 0; i < PROP_MAX; i++) {
		prop_name_tbl[i] = &prop_name[i][0];
		prop_val_tbl[i] = &prop_val[i][0];
	}

	state = ST_INIT;
	top = doc;
	line = 1;
	len = 0;
	prop_count = 0;
	while (*top != '\0') {
		c = *top++;
		switch (state) {
		case ST_INIT:
			if (c == '[') {
				state = ST_TAGNAME;
				len = 0;
				continue;
			}
			if (c == '\n') {
				line++;
				continue;
			}
			if (c == ' ' || c == '\r' || c == '\t')
				continue;

			*error_msg = strdup(_("Invalid character."));
			*error_line = line;
			return false;
		case ST_TAGNAME:
			if (len == 0 && (c == ' ' || c == '\r' || c == '\t' || c == '\n'))
				continue;
			if (c == '\n')
				line++;
			if (c == ' ' || c == '\r' || c == '\t' || c == '\n') {
				assert(len > 0);
				tag_name[len] = '\0';
				state = ST_PROPNAME;
				len = 0;
				continue;
			}
			if (c == ']') {
				tag_name[len] = '\0';
				if (!callback(tag_name, 0, NULL, NULL, line)) {
					*error_msg = strdup(_("Too many properties."));
					*error_line = line;
					return false;
				}
				state = ST_INIT;
				continue;
			}
			if (len >= TAG_NAME_MAX) {
				*error_msg = strdup(_("Tag name too long."));
				*error_line = line;
				return false;
			}
			tag_name[len++] = c;
			continue;
		case ST_PROPNAME:
			if (prop_count == PROP_MAX) {
				*error_msg = strdup(_("Too many properties."));
				*error_line = line;
				return false;
			}
			if (len == 0 && c == ' ')
				continue;
			if (len == 0 && c == ']') {
				if (!callback(tag_name, prop_count, (const char **)prop_name_tbl, (const char **)prop_val_tbl, line)) {
					*error_msg = strdup(_("Internal error."));
					*error_line = line;
					return false;
				}
				state = ST_INIT;
				continue;
			}
			if (len == 0 && c == '\n')
				line++;
			if (len == 0 && (c == ' ' || c == '\r' || c == '\t' || c == '\n'))
				continue;
			if (len > 0 && c == '=') {
				assert(len > 0);

				/* Terminate the property name. */
				prop_name[prop_count][len] = '\0';

				state = ST_PROPVALUE_QUOTE;
				len = 0;
				continue;
			}
			if (len >= PROP_NAME_MAX) {
				*error_msg = strdup(_("Property name too long."));
				*error_line = line;
				return false;
			}
			if ((c >= 'a' && c <= 'z') ||
			    (c >= 'A' && c <= 'Z') ||
			    (c >= '0' && c <= '9') ||
			    c == '-' ||
			    c == '_') {
				prop_name[prop_count][len++] = c;
				continue;
			}
			*error_msg = strdup(_("Invalid character."));
			*error_line = line;
			continue;
		case ST_PROPVALUE_QUOTE:
			if (c == '\n')
				line++;
			if (c == ' ' || c == '\r' || c == '\t' || c == '\n')
				continue;
			if (c == '\"') {
				state = ST_PROPVALUE_BODY;
				len = 0;
				continue;
			}
			continue;
		case ST_PROPVALUE_BODY:
			if (c == '\\') {
				switch (*top) {
				case '\"':
					prop_val[prop_count][len] = '\"';
					len++;
					top++;
					continue;
				case 'n':
					prop_val[prop_count][len] = '\n';
					len++;
					top++;
					continue;
				case '\\':
					prop_val[prop_count][len] = '\\';
					len++;
					top++;
					continue;
				default:
					prop_val[prop_count][len] = '\\';
					len++;
					continue;
				}
			}
			if (c == '\"') {
				prop_val[prop_count][len] = '\0';
				prop_count++;

				state = ST_PROPNAME;
				len = 0;
				continue;
			}
			if (len >= PROP_VALUE_MAX) {
				*error_msg = strdup(_("Property value too long."));
				*error_line = line;
				return false;
			}
			prop_val[prop_count][len++] = c;
			continue;
		default:
			assert(NEVER_COME_HERE);
			break;
		}
	}

	if (state == ST_INIT)
		return true;

	*error_msg = strdup(_("Unexpected EOF"));
	*error_line = line;
	return false;
}

/* Callback for when a tag is read. */
static bool parse_tag_callback(const char *name, int props, const char **prop_name, const char **prop_value, int line)
{
	struct tag *t;
	int i;

	/* If command table is full. */
	if (tag_size >= COMMAND_MAX) {
		log_error("Too many tags.");
		return false;
	}

	t = &tag[tag_size++];
	t->prop_count = props;

	/* Copy a tag name. */
	t->tag_name = strdup(name);
	if (t->tag_name == NULL) {
		log_out_of_memory();
		return false;
	}

	/* Copy properties. */
	for (i = 0; i < props; i++) {
		t->prop_name[i] = strdup(prop_name[i]);
		if (t->prop_name[i] == NULL) {
			log_out_of_memory();
			return false;
		}

		t->prop_value[i] = strdup(prop_value[i]);
		if (t->prop_value[i] == NULL) {
			log_out_of_memory();
			return false;
		}
	}

	t->line = line;

	return true;
}
