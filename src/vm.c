/* -*- coding: utf-8; tab-width: 8; indent-tabs-mode: t; -*- */

/*
 * Copyright (c) 2025, Awe Morris. All rights reserved.
 */

/*
 * Virtrual Machine
 */

#include <playfield/playfield.h>

#include "engine.h"
#include "vm.h"
#include "api.h"
#include "tag.h"
#include "common.h"

/* NoctLang */
#include <noct/noct.h>

/* Standar C */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>

/* Bytecode File Header */
#define BYTECODE_HEADER		"Noct Bytecode"

/* Save data size. */
#define SERIALIZE_SIZE		(1 * 1024 * 1024)

/* NoctLang */
static NoctVM *vm;
static NoctEnv *env;

/* Forward Declaration */
static bool load_startup_file(void);
static bool call_setup(char **title, int *width, int *height, bool *fullscreen);
static bool get_int_param(NoctEnv *env, const char *name, int *ret);
static bool get_float_param(NoctEnv *env, const char *name, float *ret);
static bool get_string_param(NoctEnv *env, const char *name, const char **ret);
static bool get_value_param(NoctEnv *env, const char *name, NoctValue *value);
static bool get_dict_elem_int_param(NoctEnv *env, const char *name, const char *key, int *ret);
static bool serialize_save_data(NoctEnv *env, NoctValue *value, void *data, size_t buf_size, size_t *ret);
static bool deserialize_save_data(NoctEnv *env, NoctValue *value, void *data, size_t buf_size);
static bool install_api(NoctEnv *env);

/*
 * Create a VM, then call setup().
 */
bool create_vm(char **title, int *width, int *height, bool *fullscreen)
{
	/* Create a language runtime. */
	if (!noct_create_vm(&vm, &env))
		return false;

	/* Load the startup file. */
	if (!load_startup_file())
		return false;

	/* Call "setup()" and get a title and window size. */
	if (!call_setup(title, width, height, fullscreen)) {
		const char *file;
		int line;
		const char *msg;
		noct_get_error_file(env, &file);
		noct_get_error_line(env, &line);
		noct_get_error_message(env, &msg);
		log_error(PPS_TR("Error: %s: %d: %s"), file, line, msg);
		return false;
	}

	/* Install the API to the runtime. */
	if (!install_api(env))
		return false;

	return true;
}

/*
 * Destroy the VM.
 */
void destroy_vm(void)
{
	/* Destroy the VM. */
	noct_destroy_vm(vm);
}

/* Load the startup file. */
static bool load_startup_file(void)
{
	char *buf;

	/* Load a file content, i.e., a script text. */
	if (!load_file(STARTUP_FILE, &buf, NULL))
		return false;

	/* Register the script text to the language runtime. */
	if (!noct_register_source(env, STARTUP_FILE, buf)) {
		const char *file;
		int line;
		const char *msg;
		noct_get_error_file(env, &file);
		noct_get_error_line(env, &line);
		noct_get_error_message(env, &msg);
		log_error(PPS_TR("Error: %s: %d: %s"), file, line, msg);
		return false;
	}

	free(buf);

	return true;
}

/* Call "setup()" function to determin a title, width, and height. */
static bool call_setup(char **title, int *width, int *height, bool *fullscreen)
{
	NoctValue ret;
	NoctValue title_val;
	NoctValue width_val;
	NoctValue height_val;
	NoctValue fullscreen_val;
	const char *title_s;
	bool succeeded;

	succeeded = false;
	do {
		/* Call setup() and get a return dictionary. */
		if (!noct_enter_vm(env, "setup", 0, NULL, &ret))
			break;

		/* Get the "title" element from the dictionary. */
		if (title != NULL) {
			if (!noct_get_dict_elem(env, &ret, "title", &title_val))
				break;
			if (!noct_get_string(env, &title_val, &title_s))
				break;
			*title = strdup(title_s);
		}

		/* Get the "width" element from the dictionary. */
		if (width != NULL) {
			if (!noct_get_dict_elem(env, &ret, "width", &width_val))
				break;
			if (!noct_get_int(env, &width_val, width))
				break;
		}

		/* Get the "height" element from the dictionary. */
		if (height != NULL) {
			if (!noct_get_dict_elem(env, &ret, "height", &height_val))
				break;
			if (!noct_get_int(env, &height_val, height))
				break;
		}

		/* Get the "fullscreen" element from the dictionary. */
		if (fullscreen != NULL) {
			bool fullscreen_exist;
			if (!noct_check_dict_key(env, &ret, "fullscreen", &fullscreen_exist))
				return false;
			if (fullscreen_exist) {
				if (!noct_get_dict_elem(env, &ret, "fullscreen", &fullscreen_val))
					return false;
				*fullscreen = fullscreen_val.val.i;
			} else {
				*fullscreen = false;
			}
		}

		/* Do a fast GC. */
		noct_fast_gc(env);

		succeeded = true;
	} while (0);
	if (!succeeded) {
		const char *file;
		int line;
		const char *msg;
		noct_get_error_file(env, &file);
		noct_get_error_line(env, &line);
		noct_get_error_message(env, &msg);
		log_error(PPS_TR("Error: %s: %d: %s"), file, line, msg);
		return false;
	}

	return true;
}

/*
 * Call a VM function.
 */
bool call_vm_function(const char *func_name)
{
	NoctValue ret;

	/* Call a function. */
	if (!noct_enter_vm(env, func_name, 0, NULL, &ret)) {
		const char *file;
		int line;
		const char *msg;
		noct_get_error_file(env, &file);
		noct_get_error_line(env, &line);
		noct_get_error_message(env, &msg);
		log_error(PPS_TR("Error: %s: %d: %s"), file, line, msg);
		return false;
	}

	/* Do a fast GC. */
	fast_gc();

	return true;
}

/*
 * Call a tag function.
 */
bool call_vm_tag_function(bool *tag_end)
{
	struct tag *t;
	NoctValue dict;
	int i;
	char func_name[256];
	NoctValue func_val;
	NoctFunc *func;
	NoctValue ret;

	*tag_end = false;

	/* Get a current command. */
	t = get_current_tag();
	if (t == NULL) {
		/* Reached to the end. Finish the game loop. */
		*tag_end = true;
		return true;
	}

	/* Make a parameter dictionary. */
	if (!noct_make_empty_dict(env, &dict)) {
		log_error(PPS_TR("In tag %s:%d: runtime error."),
			  get_tag_file_name(),
			  get_tag_line());
		return false;
	}

	/* Setup properties as dictionary items. */
	for (i = 0; i < t->prop_count; i++) {
		NoctValue str;
		if (!noct_make_string(env, &str, t->prop_value[i])) {
			log_error(PPS_TR("In tag %s:%d: runtime error."),
				  get_tag_file_name(),
				  get_tag_line());
			return false;
		}
		if (!noct_set_dict_elem(env, &dict, t->prop_name[i], &str)) {
			log_error(PPS_TR("In tag %s:%d: runtime error."),
				  get_tag_file_name(),
				  get_tag_line());
			return false;
		}
	}

	/* Make a tag function name. */
	snprintf(func_name, sizeof(func_name), "Tag_%s", t->tag_name);

	/* Get a corresponding function.  */
	if (!noct_get_global(env, func_name, &func_val)) {
		log_error(PPS_TR("%s:%d: Tag \"%s\" not found."),
			  get_tag_file_name(),
			  get_tag_line(),
			  t->tag_name);
		return false;
	}
	if (!noct_get_func(env, &func_val, &func)) {
		log_error(PPS_TR("%s:%d: \"tag_%s\" is not a function."),
			  get_tag_file_name(),
			  get_tag_line(),
			  t->tag_name);
		return false;
	}

	/* Call the function. */
	if (!noct_enter_vm(env, func_name, 1, &dict, &ret)) {
		const char *file;
		int line;
		const char *msg;

		log_error(PPS_TR("In tag %s:%d: Tag \"%s\" execution error."),
			  get_tag_file_name(),
			  get_tag_line(),
			  t->tag_name);

		noct_get_error_file(env, &file);
		noct_get_error_line(env, &line);
		noct_get_error_message(env, &msg);
		log_error(PPS_TR("Error: %s: %d: %s"), file, line, msg);
		return false;
	}

	return true;
}

/*
 * Set a VM integer.
 */
bool set_vm_int(const char *prop_name, int val)
{
	NoctValue api, prop_val;

	noct_pin_local(env, 2, &api, &prop_val);

	if (!noct_get_global(env, "Engine", &api))
		return false;
	noct_make_int(env, &prop_val, val);
	if (!noct_set_dict_elem(env, &api, prop_name, &prop_val))
		return false;

	noct_unpin_local(env, 2, &api, &prop_val);

	return true;
}

/*
 * Get a VM integer.
 */
bool get_vm_int(const char *prop_name, int *val)
{
	NoctValue dict, dict_val;

	noct_pin_local(env, 2, &dict, &dict_val);

	if (!noct_get_global(env, "Engine", &dict))
		return false;
	if (!noct_get_dict_elem_check_int(env, &dict, "exitFlag", &dict_val, val))
		return false;

	noct_unpin_local(env, 2, &dict, &dict_val);

	return true;
}

/*
 * Do a fast GC.
 */
void fast_gc(void)
{
	noct_fast_gc(env);
}

/*
 * Do a full GC.
 */
void full_gc(void)
{
	noct_compact_gc(env);
}

/*
 * API
 */

/* debug() */
static bool debug(NoctEnv *env)
{
	NoctValue param;
	int type;
	bool succeeded;

	type = 0;
	succeeded = false;
	do {
		if (!noct_get_arg(env, 0, &param))
			break;

		if (!noct_get_value_type(env, &param, &type))
			break;

		succeeded = true;
	} while (0);
	if (!succeeded) {
		const char *file;
		int line;
		const char *msg;
		noct_get_error_file(env, &file);
		noct_get_error_line(env, &line);
		noct_get_error_message(env, &msg);
		log_error(PPS_TR("Error: %s: %d: %s"), file, line, msg);
		return false;
	}

	switch (type) {
	case NOCT_VALUE_INT:
	{
		int d;
		noct_get_int(env, &param, &d);
		log_info("%d", d);
		break;
	}
	case NOCT_VALUE_FLOAT:
	{
		float f;
		noct_get_float(env, &param, &f);
		log_info("%f", f);
		break;
	}
	case NOCT_VALUE_STRING:
	{
		const char *s;
		noct_get_string(env, &param, &s);
		log_info("%s", s);
		break;
	}
	default:
		log_info("[object]");
		break;
	}

	return true;
}

/* import() */
static bool import(NoctEnv *env)
{
	NoctValue file;
	const char *file_s;
	char *data;
	size_t len;

	/* Get the argument. */
	if (!noct_get_arg_check_string(env, 0, &file, &file_s))
		return false;

	/* Load the source file content. */
	if (!load_file(file_s, &data, &len))
		return false;

	/* Check for the bytecode header. */
	if (strncmp(data, BYTECODE_HEADER, strlen(BYTECODE_HEADER)) != 0) {
		/* It's a source file. */
		if (!noct_register_source(env, file_s, data)) {
			const char *file, *msg;
			int line;
			noct_get_error_file(env, &file);
			noct_get_error_line(env, &line);
			noct_get_error_message(env, &msg);
			log_error(PPS_TR("Error: %s: %d: %s"), file, line, msg);
			return false;
		}
	} else {
		/* It's a bytecode file. */
		if (!noct_register_bytecode(env, (void *)data, len)) {
			const char *file, *msg;
			int line;
			noct_get_error_file(env, &file);
			noct_get_error_line(env, &line);
			noct_get_error_message(env, &msg);
			log_error(PPS_TR("Error: %s: %d: %s"), file, line, msg);
			return false;
		}
	}

	free(data);

	return true;
}

/* Engine.moveToTagFile() */
static bool Engine_moveToTagFile(NoctEnv *env)
{
	const char *file;

	if (!get_string_param(env, "file", &file))
		return false;

	if (!playfield_move_to_tag_file(file))
		return false;

	return true;
}

/* Engine.moveToNextTag() */
static bool Engine_moveToNextTag(NoctEnv *env)
{
	UNUSED_PARAMETER(env);

	playfield_move_to_next_tag();

	return true;
}

/* Engine.callTagFunction() */
static bool Engine_callTagFunction(NoctEnv *env)
{
	bool tag_end;
	NoctValue ret;

	UNUSED_PARAMETER(env);

	if (!call_vm_tag_function(&tag_end))
		return false;

	if (!noct_set_return_make_int(env, &ret, tag_end ? 0 : 1))
		return false;

	return true;
}

/* Engine.getDate() */
static bool Engine_getDate(NoctEnv *env)
{
	NoctValue ret;
	NoctValue val;
	time_t t;
	struct tm *tm_info;
	bool is_ok;

	if (!noct_make_empty_dict(env, &ret))
		return false;

	time(&t);
	tm_info = localtime(&t);
	if (!noct_set_dict_elem_make_int(env, &ret, "year", &val, tm_info->tm_year + 1900))
		return false;
	if (!noct_set_dict_elem_make_int(env, &ret, "month", &val, tm_info->tm_mon + 1))
		return false;
	if (!noct_set_dict_elem_make_int(env, &ret, "day", &val, tm_info->tm_mday))
		return false;
	if (!noct_set_dict_elem_make_int(env, &ret, "hour", &val, tm_info->tm_hour))
		return false;
	if (!noct_set_dict_elem_make_int(env, &ret, "minute", &val, tm_info->tm_min))
		return false;
	if (!noct_set_dict_elem_make_int(env, &ret, "second", &val, tm_info->tm_sec))
		return false;
	if (!noct_set_return(env, &ret))
		return false;

	return true;
}

/* Engine.createColorTexture() */
static bool Engine_createColorTexture(NoctEnv *env)
{
	int r, g, b, a;
	int width;
	int height;
	int tex_id;
	NoctValue ret, tmp;

	if (!get_int_param(env, "width", &width))
		return false;
	if (!get_int_param(env, "height", &height))
		return false;
	if (!get_int_param(env, "r", &r))
		return false;
	if (!get_int_param(env, "g", &g))
		return false;
	if (!get_int_param(env, "b", &b))
		return false;
	if (!get_int_param(env, "a", &a))
		return false;

	if (!playfield_create_color_texture(width, height, r, g, b, a, &tex_id))
		return false;

	if (!noct_make_empty_dict(env, &ret))
		return false;
	if (!noct_set_dict_elem_make_int(env, &ret, "id", &tmp, tex_id))
		return false;
	if (!noct_set_dict_elem_make_int(env, &ret, "width", &tmp, width))
		return false;
	if (!noct_set_dict_elem_make_int(env, &ret, "height", &tmp, height))
		return false;
	if (!noct_set_return(env, &ret))
		return false;

	return true;
}

/* Engine.loadTexture() */
static bool Engine_loadTexture(NoctEnv *env)
{
	const char *file;
	int tex_id;
	int tex_width;
	int tex_height;
	NoctValue ret, tmp;

	if (!get_string_param(env, "file", &file))
		return false;

	if (!playfield_load_texture(file, &tex_id, &tex_width, &tex_height))
		return false;

	if (!noct_make_empty_dict(env, &ret))
		return false;
	if (!noct_set_dict_elem_make_int(env, &ret, "id", &tmp, tex_id))
		return false;
	if (!noct_set_dict_elem_make_int(env, &ret, "width", &tmp, tex_width))
		return false;
	if (!noct_set_dict_elem_make_int(env, &ret, "height", &tmp, tex_height))
		return false;
	if (!noct_set_return(env, &ret))
		return false;

	return true;
}

/* Engine.destroyTexture() */
static bool Engine_destroyTexture(NoctEnv *env)
{
	int tex_id;

	if (!get_dict_elem_int_param(env, "texture", "id", &tex_id))
		return false;

	playfield_destroy_texture(tex_id);

	return true;
}

/* Engine.renderTexture() */
static bool Engine_renderTexture(NoctEnv *env)
{
	int dst_left;
	int dst_top;
	int dst_width;
	int dst_height;
	int tex_id;
	int src_left;
	int src_top;
	int src_width;
	int src_height;
	int alpha;

	if (!get_int_param(env, "dstLeft", &dst_left))
		return false;
	if (!get_int_param(env, "dstTop", &dst_top))
		return false;
	if (!get_int_param(env, "dstWidth", &dst_width))
		return false;
	if (!get_int_param(env, "dstHeight", &dst_height))
		return false;
	if (!get_dict_elem_int_param(env, "texture", "id", &tex_id))
		return false;
	if (!get_int_param(env, "srcLeft", &src_left))
		return false;
	if (!get_int_param(env, "srcTop", &src_top))
		return false;
	if (!get_int_param(env, "srcWidth", &src_width))
		return false;
	if (!get_int_param(env, "srcHeight", &src_height))
		return false;
	if (!get_int_param(env, "alpha", &alpha))
		return false;

	playfield_render_texture(
		dst_left,
		dst_top,
		dst_width,
		dst_height,
		tex_id,
		src_left,
		src_top,
		src_width,
		src_height,
		alpha);

	return true;
}

/* Engine.renderTexture3D() */
static bool Engine_renderTexture3D(NoctEnv *env)
{
	int x1, y1, x2, y2, x3, y3, x4, y4;
	int tex_id;
	int src_left;
	int src_top;
	int src_width;
	int src_height;
	int alpha;

	if (!get_int_param(env, "x1", &x1))
		return false;
	if (!get_int_param(env, "y1", &y1))
		return false;
	if (!get_int_param(env, "x2", &x2))
		return false;
	if (!get_int_param(env, "y2", &y2))
		return false;
	if (!get_int_param(env, "x3", &x3))
		return false;
	if (!get_int_param(env, "y3", &y3))
		return false;
	if (!get_int_param(env, "x4", &x4))
		return false;
	if (!get_int_param(env, "y4", &y4))
		return false;
	if (!get_dict_elem_int_param(env, "texture", "id", &tex_id))
		return false;
	if (!get_int_param(env, "srcLeft", &src_left))
		return false;
	if (!get_int_param(env, "srcTop", &src_top))
		return false;
	if (!get_int_param(env, "srcWidth", &src_width))
		return false;
	if (!get_int_param(env, "srcHeight", &src_height))
		return false;
	if (!get_int_param(env, "alpha", &alpha))
		return false;

	playfield_render_texture_3d(
		x1, y1, x2, y2, x3, y3, x4, y4,
		tex_id,
		src_left, src_top, src_width, src_height,
		alpha);

	return true;
}

/* Engine.draw() */
static bool Engine_draw(NoctEnv *env)
{
	int tex_id, x, y;

	if (!get_dict_elem_int_param(env, "texture", "id", &tex_id))
		return false;
	if (!get_int_param(env, "x", &x))
		return false;
	if (!get_int_param(env, "y", &y))
		return false;

	playfield_draw(tex_id, x, y);

	return true;
}

/* Engine.playSound() */
static bool Engine_playSound(NoctEnv *env)
{
	int stream;
	const char *file;

	if (!get_int_param(env, "stream", &stream))
		return false;
	if (!get_string_param(env, "file", &file))
		return false;

	if (!playfield_play_sound(stream, file))
		return false;

	return true;
}

/* Engine.stopSound() */
static bool Engine_stopSound(NoctEnv *env)
{
	int stream;

	if (!get_int_param(env, "stream", &stream))
		return false;

	if (!playfield_stop_sound(stream))
		return false;

	return true;
}

/* Engine.stopSound() */
static bool Engine_setSoundVolume(NoctEnv *env)
{
	int stream;

	if (!get_int_param(env, "stream", &stream))
		return false;

	if (!playfield_stop_sound(stream))
		return false;

	return true;
}

/* Engine.loadFont() */
static bool Engine_loadFont(NoctEnv *rt)
{
	int slot;
	const char *file;

	if (!get_int_param(env, "slot", &slot))
		return false;
	if (!get_string_param(env, "file", &file))
		return false;

	if (!playfield_load_font(slot, file))
		return false;

	return true;
}

/* Engine.createTextTexture() */
static bool Engine_createTextTexture(NoctEnv *env)
{
	int slot;
	const char *text;
	int size;
	const char *color;
	int r, g, b, a;
	int tex_id;
	int tex_width;
	int tex_height;
	NoctValue ret, tmp;

	if (!get_int_param(env, "slot", &slot))
		return false;
	if (!get_string_param(env, "text", &text))
		return false;
	if (!get_int_param(env, "size", &size))
		return false;
	if (!get_int_param(env, "r", &r))
		return false;
	if (!get_int_param(env, "g", &g))
		return false;
	if (!get_int_param(env, "b", &b))
		return false;
	if (!get_int_param(env, "a", &a))
		return false;

	if (!playfield_create_text_texture(slot,
					   text,
					   size,
					   make_pixel(a, r, g, b),
					   &tex_id,
					   &tex_width,
					   &tex_height))
		return false;

	if (!noct_make_empty_dict(env, &ret))
		return false;
	if (!noct_set_dict_elem_make_int(env, &ret, "id", &tmp, tex_id))
		return false;
	if (!noct_set_dict_elem_make_int(env, &ret, "width", &tmp, tex_width))
		return false;
	if (!noct_set_dict_elem_make_int(env, &ret, "height", &tmp, tex_height))
		return false;
	if (!noct_set_return(env, &ret))
		return false;

	return true;
}

/* Engine.writeSaveData() */
static bool Engine_writeSaveData(NoctEnv *env)
{
	const char *key;
	NoctValue value;
	void *data;
	size_t size;

	if (!get_string_param(env, "key", &key))
		return false;
	if (!get_value_param(env, "value", &value))
		return false;

	data = malloc(SERIALIZE_SIZE);
	if (data == NULL) {
		log_out_of_memory();
		return false;
	}

	if (!serialize_save_data(env, &value, data, SERIALIZE_SIZE, &size)) {
		free(data);
		return false;
	}

	if (!playfield_write_save_data(key, data, size)) {
		free(data);
		return false;
	}

	free(data);

	return true;
}

/* Engine.readSaveData() */
static bool Engine_readSaveData(NoctEnv *env)
{
	const char *key;
	NoctValue ret;
	void *data;
	size_t size;

	if (!get_string_param(env, "key", &key))
		return false;

	data = malloc(SERIALIZE_SIZE);
	if (data == NULL) {
		log_out_of_memory();
		return false;
	}

	if (!playfield_read_save_data(key, data, SERIALIZE_SIZE, &size)) {
		free(data);
		return false;
	}

	if (!deserialize_save_data(env, &ret, data, size)) {
		free(data);
		return false;
	}
	free(data);

	if (!noct_set_return(env, &ret))
		return false;

	return true;
}

/*
 * Helpers
 */

/* Get an integer parameter. */
static bool get_int_param(NoctEnv *env, const char *name, int *ret)
{
	NoctValue param, elem;
	float f;
	const char *s;

	noct_pin_local(env, 2, &param, &elem);

	if (!noct_get_arg(env, 0, &param)) {
		noct_error(env, PPS_TR("Parameter is not set."));
		noct_unpin_local(env, 2, &param, &elem);
		return false;
	}

	if (!noct_get_dict_elem(env, &param, name, &elem)) {
		noct_error(env, PPS_TR("Parameter %s is not set."), name);
		noct_unpin_local(env, 2, &param, &elem);
		return false;
	}

	switch (elem.type) {
	case NOCT_VALUE_INT:
		noct_get_int(env, &elem, ret);
		break;
	case NOCT_VALUE_FLOAT:
		noct_get_float(env, &elem, &f);
		*ret = (int)f;
		break;
	case NOCT_VALUE_STRING:
		noct_get_string(env, &elem, &s);
		*ret = atoi(s);
		break;
	default:
		noct_error(env, "Unexpected parameter value for %s.", name);
		noct_unpin_local(env, 2, &param, &elem);
		return false;
	}

	noct_unpin_local(env, 2, &param, &elem);

	return true;
}

/* Get a string parameter. */
static bool get_string_param(NoctEnv *env, const char *name, const char **ret)
{
	NoctValue param, elem;
	static char buf[128];

	noct_pin_local(env, 2, &param, &elem);

	if (!noct_get_arg(env, 0, &param)) {
		noct_error(env, PPS_TR("Parameter is not set."));
		noct_unpin_local(env, 2, &param, &elem);
		return false;
	}

	if (!noct_get_dict_elem(env, &param, name, &elem)) {
		noct_error(env, PPS_TR("Parameter %s is not set."), name);
		noct_unpin_local(env, 2, &param, &elem);
		return false;
	}

	switch (elem.type) {
	case NOCT_VALUE_INT:
	{
		int i;
		noct_get_int(env, &elem, &i);
		snprintf(buf, sizeof(buf), "%d", i);
		*ret = buf;
		break;
	}
	case NOCT_VALUE_FLOAT:
	{
		float f;
		noct_get_float(env, &elem, &f);
		snprintf(buf, sizeof(buf), "%f", f);
		*ret = buf;
		break;
	}
	case NOCT_VALUE_STRING:
		noct_get_string(env, &elem, ret);
		break;
	default:
		noct_error(env, PPS_TR("Unexpected parameter value for %s."), name);
		noct_unpin_local(env, 2, &param, &elem);
		return false;
	}

	noct_unpin_local(env, 2, &param, &elem);

	return true;
}

/* Get a value parameter. */
static bool get_value_param(NoctEnv *env, const char *name, NoctValue *value)
{
	NoctValue param;

	noct_pin_local(env, 1, &param);

	if (!noct_get_arg(env, 0, &param)) {
		noct_error(env, PPS_TR("Parameter is not set."));
		noct_unpin_local(env, 1, &param);
		return false;
	}

	if (!noct_get_dict_elem(env, &param, name, value)) {
		noct_error(env, PPS_TR("Parameter %s is not set."), name);
		noct_unpin_local(env, 1, &param);
		return false;
	}

	noct_unpin_local(env, 1, &param);

	return true;
}

/* Get an integer parameter. */
static bool get_dict_elem_int_param(NoctEnv *env, const char *name, const char *key, int *ret)
{
	NoctValue param, elem, ival;

	noct_pin_local(env, 3, &param, &elem, &ival);

	if (!noct_get_arg(env, 0, &param)) {
		noct_error(env, PPS_TR("Parameter is not set."));
		noct_unpin_local(env, 3, &param, &elem, &ival);
		return false;
	}

	if (!noct_get_dict_elem(env, &param, name, &elem)) {
		noct_error(env, PPS_TR("Parameter %s is not set."), name);
		noct_unpin_local(env, 3, &param, &elem, &ival);
		return false;
	}

	if (elem.type != NOCT_VALUE_DICT) {
		noct_error(env, PPS_TR("Unexpected parameter value for %s."), name);
		noct_unpin_local(env, 3, &param, &elem, &ival);
		return false;
	}

	if (!noct_get_dict_elem(env, &elem, key, &ival)) {
		noct_error(env, PPS_TR("Parameter %s doesn't have the key %s."), name, key);
		noct_unpin_local(env, 3, &param, &elem, &ival);
		return false;
	}

	if (ival.type != NOCT_VALUE_INT) {
		noct_error(env, PPS_TR("Unexpected parameter value for %s.%s."), name, key);
		noct_unpin_local(env, 3, &param, &elem, &ival);
		return false;
	}

	*ret = ival.val.i;

	noct_unpin_local(env, 3, &param, &elem, &ival);

	return true;
}

/*
 * Engine Installation
 */

/*
 * Install Engine functions to a runtime.
 */
bool install_api(NoctEnv *env)
{
	const char *params[] = {"param"};
	struct func {
		bool (*func)(struct rt_env *);
		const char *field;
		const char *name;
	} funcs[] = {
#define RTFUNC(name) {Engine_##name, #name, "Engine_" # name}
		{debug, NULL, "debug"},
		{import, NULL, "import"},
		RTFUNC(moveToTagFile),
		RTFUNC(moveToNextTag),
		RTFUNC(callTagFunction),
		RTFUNC(getDate),
		RTFUNC(createColorTexture),
		RTFUNC(loadTexture),
		RTFUNC(destroyTexture),
		RTFUNC(renderTexture),
		RTFUNC(renderTexture3D),
		RTFUNC(draw),
		RTFUNC(destroyTexture),
		RTFUNC(playSound),
		RTFUNC(stopSound),
		RTFUNC(loadFont),
		RTFUNC(createTextTexture),
		RTFUNC(writeSaveData),
		RTFUNC(readSaveData),
	};
	const int tbl_size = sizeof(funcs) / sizeof(struct func);
	struct rt_value dict;
	int i;

	/* Make a global variable "Engine". */
	if (!noct_make_empty_dict(env, &dict))
		return false;
	if (!noct_set_global(env, "Engine", &dict))
		return false;

	/* Register functions. */
	for (i = 0; i < tbl_size; i++) {
		struct rt_value funcval;

		/* Register a cfunc. */
		if (!noct_register_cfunc(env, funcs[i].name, 1, params, funcs[i].func, NULL))
			return false;

		/* Add to the API dictionary. */
		if (funcs[i].field != NULL) {
			/* Get a function value. */
			if (!noct_get_global(env, funcs[i].name, &funcval))
				return false;

			/* Make a dictionary element. */
			if (!noct_set_dict_elem(env, &dict, funcs[i].field, &funcval))
				return false;
		}
	}

	return true;
}

/*
 * Noct Value Serialization
 */

/* String Size Max */
#define SER_STRING_MAX		4096

/* Serialize Context */
struct ser_ctx {
	uint8_t *data;
	size_t size;
	size_t pos;
	char sbuf[SER_STRING_MAX];
};

/* Value Type */
enum {
	SER_TYPE_INT,
	SER_TYPE_FLOAT,
	SER_TYPE_STRING,
	SER_TYPE_ARRAY,
	SER_TYPE_DICT,
};

/* Forward Declaration */
static bool serialize_save_data_recursively(NoctEnv *env, NoctValue *value, struct ser_ctx *ctx);
static bool deserialize_save_data_recursively(NoctEnv *env, NoctValue *value, struct ser_ctx *ctx);
static bool ser_put_u8(struct ser_ctx *ctx, uint8_t val);
static bool ser_put_u32(struct ser_ctx *ctx, uint32_t val);
static bool ser_put_string(struct ser_ctx *ctx, const char *val);
static bool ser_get_u8(struct ser_ctx *ctx, uint8_t *val);
static bool ser_get_u32(struct ser_ctx *ctx, uint32_t *val);
static bool ser_get_string(struct ser_ctx *ctx, char **val);

/* Serialize a value to a data buffer. */
static bool serialize_save_data(NoctEnv *env, NoctValue *value, void *data, size_t buf_size, size_t *ret)
{
	struct ser_ctx ctx;

	ctx.data = (uint8_t *)data;
	ctx.size = buf_size;
	ctx.pos = 0;

	if (!serialize_save_data_recursively(env, value, &ctx))
		return false;

	assert(ctx.pos <= ctx.size);

	*ret = ctx.pos;

	return true;
}

/* Serialize a value recursively. */
static bool serialize_save_data_recursively(NoctEnv *env, NoctValue *value, struct ser_ctx *ctx)
{
	int type;
	int ival;
	float fval;
	const char *sval;
	int size;
	int i;

	if (!noct_get_value_type(env, value, &type))
		return false;

	switch (type) {
	case NOCT_VALUE_INT:
		if (!noct_get_int(env, value, &ival))
			return false;
		if (!ser_put_u8(ctx, SER_TYPE_INT))
			return false;
		if (!ser_put_u32(ctx, ival))
			return false;
		return true;
	case NOCT_VALUE_FLOAT:
		if (!noct_get_float(env, value, &fval))
			return false;
		ival = *(int *)&fval;
		if (!ser_put_u8(ctx, SER_TYPE_FLOAT))
			return false;
		if (!ser_put_u32(ctx, ival))
			return false;
		return true;
	case NOCT_VALUE_STRING:
		if (!noct_get_string(env, value, &sval))
			return false;
		if (!ser_put_u8(ctx, SER_TYPE_STRING))
			return false;
		if (!ser_put_string(ctx, sval))
			return false;
		return true;
	case NOCT_VALUE_ARRAY:
		if (!noct_get_array_size(env, value, &size))
			return false;
		if (!ser_put_u8(ctx, SER_TYPE_ARRAY))
			return false;
		if (!ser_put_u32(ctx, size))
			return false;
		for (i = 0; i < size; i++) {
			NoctValue elem;
			if (!noct_get_array_elem(env, value, i, &elem))
				return false;
			if (!serialize_save_data_recursively(env, &elem, ctx))
				return false;
		}
		return true;
	case NOCT_VALUE_DICT:
		if (!noct_get_dict_size(env, value, &size))
			return false;
		if (!ser_put_u8(ctx, SER_TYPE_DICT))
			return false;
		if (!ser_put_u32(ctx, size))
			return false;
		for (i = 0; i < size; i++) {
			NoctValue k, v;
			if (!noct_get_dict_key_by_index(env, value, i, &k))
				return false;
			if (!noct_get_string(env, &k, &sval))
				return false;
			if (!ser_put_string(ctx, sval))
				return false;
			if (!noct_get_dict_value_by_index(env, value, i, &v))
				return false;
			if (!serialize_save_data_recursively(env, &v, ctx))
				return false;
		}
		return true;
	case NOCT_VALUE_FUNC:
		log_error(PPS_TR("Cannot deserialize function."));
		return false;
	default:
		assert(0);
		break;
	}
	return false;
}

/* Deserialize a value from a data buffer. */
static bool deserialize_save_data(NoctEnv *env, NoctValue *value, void *data, size_t buf_size)
{
	struct ser_ctx ctx;

	ctx.data = (uint8_t *)data;
	ctx.size = buf_size;
	ctx.pos = 0;

	if (!deserialize_save_data_recursively(env, value, &ctx))
		return false;

	assert(ctx.pos <= ctx.size);

	return true;
}

/* Deserialize a value recursively. */
static bool deserialize_save_data_recursively(NoctEnv *env, NoctValue *value, struct ser_ctx *ctx)
{
	uint8_t type;
	uint32_t ival;
	float fval;
	char *sval;
	int size;
	int i;

	if (!ser_get_u8(ctx, &type))
		return false;

	switch (type) {
	case SER_TYPE_INT:
		if (!ser_get_u32(ctx, &ival))
			return false;
		if (!noct_make_int(env, value, ival))
			return false;
		return true;
	case SER_TYPE_FLOAT:
		if (!ser_get_u32(ctx, &ival))
			return false;
		fval = *(float *)&ival;
		if (!noct_make_float(env, value, fval))
			return false;
		return true;
	case SER_TYPE_STRING:
		if (!ser_get_string(ctx, &sval))
			return false;
		if (!noct_make_string(env, value, sval))
			return false;
		return true;
	case SER_TYPE_ARRAY:
		if (!ser_get_u32(ctx, &size))
			return false;
		if (!noct_make_empty_array(env, value))
			return false;
		if (!noct_resize_array(env, value, size))
			return false;
		for (i = 0; i < size; i++) {
			NoctValue elem;
			if (!deserialize_save_data_recursively(env, &elem, ctx))
				return false;
			if (!noct_set_array_elem(env, value, i, &elem))
				return false;
		}
		return true;
	case SER_TYPE_DICT:
		if (!ser_get_u32(ctx, &size))
			return false;
		if (!noct_make_empty_dict(env, value))
			return false;
		for (i = 0; i < size; i++) {
			NoctValue elem;
			char key[SER_STRING_MAX];
			if (!ser_get_string(ctx, &sval))
				return false;
			strcpy(key, sval);
			if (!deserialize_save_data_recursively(env, &elem, ctx))
				return false;
			if (!noct_set_dict_elem(env, value, key, &elem))
				return false;
		}
		return true;
	default:
		log_error(PPS_TR("Invalid save data."));
		return false;
	}
	return false;
}

/* Put a u8 to the data buffer. */
static bool ser_put_u8(struct ser_ctx *ctx, uint8_t val)
{
	if (ctx->pos + 1 > ctx->size)
		return false;

	ctx->data[ctx->pos] = val;
	ctx->pos++;

	return true;
}

/* Put a u32 to the data buffer. */
static bool ser_put_u32(struct ser_ctx *ctx, uint32_t val)
{
	if (ctx->pos + 4 > ctx->size)
		return false;

	ctx->data[ctx->pos + 0] = (uint8_t)(val & 0xff);
	ctx->data[ctx->pos + 1] = (uint8_t)((val >> 8) & 0xff);
	ctx->data[ctx->pos + 2] = (uint8_t)((val >> 16) & 0xff);
	ctx->data[ctx->pos + 3] = (uint8_t)((val >> 24) & 0xff);

	ctx->pos += 4;

	return true;
}

/* Put a string to the data buffer. */
static bool ser_put_string(struct ser_ctx *ctx, const char *val)
{
	size_t len;

	len = strlen(val);
	if (len > SER_STRING_MAX) {
		log_error(PPS_TR("String too long."));
		return false;
	}

	if (ctx->pos + 4 + len > ctx->size)
		return false;

	ctx->data[ctx->pos + 0] = (uint8_t)(len & 0xff);
	ctx->data[ctx->pos + 1] = (uint8_t)((len >> 8) & 0xff);
	ctx->data[ctx->pos + 2] = (uint8_t)((len >> 16) & 0xff);
	ctx->data[ctx->pos + 3] = (uint8_t)((len >> 24) & 0xff);
	ctx->pos += 4;

	memcpy(ctx->data + ctx->pos, val, len);
	ctx->pos += len;

	return true;
}

/* Get a u8 from the data buffer. */
static bool ser_get_u8(struct ser_ctx *ctx, uint8_t *val)
{
	if (ctx->pos + 1 > ctx->size)
		return false;

	*val = ctx->data[ctx->pos];
	ctx->pos++;

	return true;
}

/* Get a u32 from the data buffer. */
static bool ser_get_u32(struct ser_ctx *ctx, uint32_t *val)
{
	if (ctx->pos + 4 > ctx->size)
		return false;

	*val = ((uint32_t)ctx->data[ctx->pos + 0]) |
	       ((uint32_t)ctx->data[ctx->pos + 1] << 8) |
	       ((uint32_t)ctx->data[ctx->pos + 2] << 16) |
	       ((uint32_t)ctx->data[ctx->pos + 3] << 24);
	ctx->pos += 4;

	return true;
}

/* Get a string from the data buffer. */
static bool ser_get_string(struct ser_ctx *ctx, char **val)
{
	uint32_t len;

	if (ctx->pos + 4 > ctx->size)
		return false;

	len = ((uint32_t)ctx->data[ctx->pos + 0]) |
	      ((uint32_t)ctx->data[ctx->pos + 1] << 8) |
	      ((uint32_t)ctx->data[ctx->pos + 2] << 16) |
	      ((uint32_t)ctx->data[ctx->pos + 3] << 24);
	ctx->pos += 4;

	if (len >= SER_STRING_MAX) {
		log_error(PPS_TR("String too long."));
		return false;
	}

	memcpy(ctx->sbuf, ctx->data + ctx->pos, len);
	ctx->sbuf[len] = '\0';
	ctx->pos += len;

	*val = ctx->sbuf;

	return true;
}
