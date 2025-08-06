/* -*- coding: utf-8; tab-width: 8; indent-tabs-mode: t; -*- */

/*
 * Copyright (c) 2025, Awe Morris. All rights reserved.
 */

#include "engine.h"
#include "vm.h"

/* NoctLang */
#include <noct/noct.h>

/* NoctLang. */
NoctVM *vm;
NoctEnv *env;

/* Forward Declaration */
static bool load_startup_file(void);
static bool call_setup(char **title, int *width, int *height);
static bool get_int_param(NoctEnv *env, const char *name, int *ret);
#if 0
static bool get_float_param(NoctEnv *env, const char *name, float *ret);
#endif
static bool get_string_param(NoctEnv *env, const char *name, const char **ret);
static bool get_dict_elem_int_param(NoctEnv *env, const char *name, const char *key, int *ret);
static bool install_api(NoctEnv *env);

/*
 * Create a VM.
 */
bool create_vm(char **title, int *width, int *height)
{
	/* Create a language runtime. */
	if (!noct_create_vm(&vm, &env))
		return false;

	/* Load the startup file. */
	if (!load_startup_file())
		return false;

	/* Call "setup()" and get a title and window size. */
	if (!call_setup(title, width, height)) {
		const char *file;
		int line;
		const char *msg;
		noct_get_error_file(env, &file);
		noct_get_error_line(env, &line);
		noct_get_error_message(env, &msg);
		log_error(_("%s:%d: error: %s\n"), file, line, msg);
		return false;
	}

	/* Install the API to the runtime. */
	if (!install_api(env))
		return false;

	return true;
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
		log_error(_("%s:%d: error: %s\n"), file, line, msg);
		return false;
	}

	free(buf);

	return true;
}

/* Call "setup()" function to determin a title, width, and height. */
static bool call_setup(char **title, int *width, int *height)
{
	NoctValue ret;
	NoctValue title_val;
	NoctValue width_val;
	NoctValue height_val;
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
		log_error(_("%s:%d: error: %s\n"), file, line, msg);
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
		log_error(_("%s:%d: error: %s\n"), file, line, msg);
		return false;
	}

	/* Do a fast GC. */
	fast_gc();

	return true;
}

/*
 * Call a tag function.
 */
bool call_vm_tag_function(void)
{
	struct tag *t;
	NoctValue dict;
	int i;
	char func_name[256];
	NoctValue func_val;
	NoctFunc *func;
	NoctValue ret;

	/* Get a current command. */
	t = get_current_tag();
	if (t == NULL) {
		/* Reached to the end. Finish the game loop. */
		return false;
	}

	/* Make a parameter dictionary. */
	if (!noct_make_empty_dict(env, &dict)) {
		log_error(_("In scenario %s:%d: runtime error.\n"),
			  get_tag_file_name(),
			  get_tag_line());
		return false;
	}

	/* Setup properties as dictionary items. */
	for (i = 0; i < t->prop_count; i++) {
		NoctValue str;
		if (!noct_make_string(env, &str, t->prop_value[i])) {
			log_error(_("In scenario %s:%d: runtime error.\n"),
				  get_tag_file_name(),
				  get_tag_line());
			return false;
		}
		if (!noct_set_dict_elem(env, &dict, t->prop_name[i], &str)) {
			log_error(_("In scenario %s:%d: runtime error.\n"),
				  get_tag_file_name(),
				  get_tag_line());
			return false;
		}
	}

	/* Make a tag function name. */
	snprintf(func_name, sizeof(func_name), "tag_%s", t->tag_name);

	/* Get a corresponding function.  */
	if (!noct_get_global(env, func_name, &func_val)) {
		log_error(_("%s:%d: Tag \"%s\" not found.\n"),
			  get_tag_file_name(),
			  get_tag_line(),
			  t->tag_name);
		return false;
	}
	if (!noct_get_func(env, &func_val, &func)) {
		log_error(_("%s:%d: \"tag_%s\" is not a function.\n"),
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

		log_error(_("In scenario %s:%d: Tag \"%s\" execution error.\n"),
			  get_tag_file_name(),
			  get_tag_line(),
			  t->tag_name);

		noct_get_error_file(env, &file);
		noct_get_error_line(env, &line);
		noct_get_error_message(env, &msg);
		log_error(_("%s:%d: error: %s\n"), file, line, msg);
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

	if (!noct_get_global(env, "Engine", &api))
		return false;
	noct_make_int(env, &prop_val, val);
	if (!noct_set_dict_elem(env, &api, prop_name, &prop_val))
		return false;

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
		log_error(_("%s:%d: error: %s\n"), file, line, msg);
		return false;
	}

	switch (type) {
	case NOCT_VALUE_INT:
	{
		int d;
		noct_get_int(env, &param, &d);
		printf("%d\n", d);
		break;
	}
	case NOCT_VALUE_FLOAT:
	{
		float f;
		noct_get_float(env, &param, &f);
		printf("%f\n", f);
		break;
	}
	case NOCT_VALUE_STRING:
	{
		const char *s;
		noct_get_string(env, &param, &s);
		printf("%s\n", s);
		break;
	}
	default:
		printf("[object]\n");
		break;
	}

	return true;
}

/* Engine.moveToTagFile() */
static bool Engine_moveToTagFile(NoctEnv *env)
{
	const char *file;

	if (!get_string_param(env, "file", &file))
		return false;

	if (!noct2d_move_to_tag_file(file))
		return false;

	return true;
}

/* Engine.moveToNextTag() */
static bool Engine_moveToNextTag(NoctEnv *env)
{
	UNUSED_PARAMETER(env);

	noct2d_move_to_next_tag();

	return true;
}

/* Engine.callTagFunction() */
static bool Engine_callTagFunction(NoctEnv *env)
{
	UNUSED_PARAMETER(env);

	if (!call_vm_tag_function())
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
	NoctValue ret, ival;

	if (!get_string_param(env, "file", &file)) {
		noct_error(env, _("file parameter is not set."));
		return false;
	}

	if (!noct2d_load_texture(file, &tex_id, &tex_width, &tex_height)) {
		noct_error(env, _("Failed to load a texture."));
		return false;
	}

	if (!noct_make_empty_dict(env, &ret))
		return false;

	noct_make_int(env, &ival, tex_id);
	if (!noct_set_dict_elem(env, &ret, "id", &ival))
		return false;
	
	noct_make_int(env, &ival, tex_width);
	if (!noct_set_dict_elem(env, &ret, "width", &ival))
		return false;

	noct_make_int(env, &ival, tex_height);
	if (!noct_set_dict_elem(env, &ret, "height", &ival))
		return false;

	if (!noct_set_return(env, &ret))
		return false;

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

	noct2d_render_texture(
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

	noct2d_draw(tex_id, x, y);

	return true;
}

/* Engine.destroyTexture() */
static bool Engine_destroyTexture(NoctEnv *env)
{
	int tex_id;

	if (!get_dict_elem_int_param(env, "texture", "id", &tex_id))
		return false;

	noct2d_destroy_texture(tex_id);

	return true;
}

/* Engine.playSound() */
static bool Engine_playSound(NoctEnv *env)
{
	int stream;
	const char *file;
	NoctValue ret;

	if (!get_int_param(env, "stream", &stream))
		return false;
	if (!get_string_param(env, "file", &file))
		return false;

	if (!noct2d_play_sound(stream, file))
		return false;

	noct_make_int(env, &ret, 1);
	if (!noct_set_return(env, &ret))
		return false;

	return true;
}

/* Engine.stopSound() */
static bool Engine_stopSound(NoctEnv *env)
{
	int stream;
	NoctValue ret;

	if (!get_int_param(env, "stream", &stream))
		return false;

	if (!noct2d_stop_sound(stream))
		return false;

	noct_make_int(env, &ret, 1);
	if (!noct_set_return(env, &ret))
		return false;

	return true;
}

/* Engine.stopSound() */
static bool Engine_setSoundVolume(NoctEnv *env)
{
	int stream;
	NoctValue ret;

	if (!get_int_param(env, "stream", &stream))
		return false;

	if (!noct2d_stop_sound(stream))
		return false;

	noct_make_int(env, &ret, 1);
	if (!noct_set_return(env, &ret))
		return false;

	return true;
}

/* Engine.loadFont() */
static bool Engine_loadFont(NoctEnv *rt)
{
	int slot;
	const char *file;
	NoctValue ret;

	if (!get_int_param(env, "slot", &slot))
		return false;
	if (!get_string_param(env, "file", &file))
		return false;

	if (!noct2d_load_font(slot, file))
		return false;

	noct_make_int(env, &ret, 1);
	if (!noct_set_return(env, &ret))
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
	pixel_t pcolor;
	int tex_id;
	int tex_width;
	int tex_height;
	NoctValue ret;
	NoctValue ival;

	if (!get_int_param(env, "slot", &slot))
		return false;
	if (!get_string_param(env, "text", &text))
		return false;
	if (!get_int_param(env, "size", &size))
		return false;
	if (!get_string_param(env, "color", &color))
		return false;

	pcolor = color_code_to_pixel_value(color);

	if (!noct2d_create_text_texture(slot, text, size, pcolor, &tex_id, &tex_width, &tex_height))
		return false;

	if (!noct_make_empty_dict(env, &ret))
		return false;

	noct_make_int(env, &ival, tex_id);
	if (!noct_set_dict_elem(env, &ret, "id", &ival))
		return false;
	
	noct_make_int(env, &ival, tex_width);
	if (!noct_set_dict_elem(env, &ret, "width", &ival))
		return false;

	noct_make_int(env, &ival, tex_height);
	if (!noct_set_dict_elem(env, &ret, "height", &ival))
		return false;

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

	if (!noct_get_arg(env, 0, &param))
		return false;

	if (!noct_get_dict_elem(env, &param, name, &elem))
		return false;

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
		return false;
	}

	return true;
}

#if 0
/* Get a float parameter. */
static bool get_float_param(NoctEnv *env, const char *name, float *ret)
{
	NoctValue param, elem;

	if (!rt_get_arg(env, 0, &param))
		return false;

	if (!rt_get_dict_elem(env, &param, name, &elem))
		return false;

	switch (elem.type) {
	case NOCT_VALUE_INT:
		*ret = (float)elem.val.i;
		break;
	case NOCT_VALUE_FLOAT:
		*ret = elem.val.f;
		break;
	case NOCT_VALUE_STRING:
		*ret = (float)atof(elem.val.str->s);
		break;
	default:
		rt_error(env, "Unexpected parameter value for %s.", name);
		return false;
	}

	return true;
}
#endif

/* Get a string parameter. */
static bool get_string_param(NoctEnv *env, const char *name, const char **ret)
{
	NoctValue param, elem;
	static char buf[128];

	if (!noct_get_arg(env, 0, &param))
		return false;

	if (!noct_get_dict_elem(env, &param, name, &elem))
		return false;

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
		noct_error(env, "Unexpected parameter value for %s.", name);
		return false;
	}

	return true;
}

/* Get an integer parameter. */
static bool get_dict_elem_int_param(NoctEnv *env, const char *name, const char *key, int *ret)
{
	NoctValue param, elem, ival;

	if (!noct_get_arg(env, 0, &param))
		return false;

	if (!noct_get_dict_elem(env, &param, name, &elem))
		return false;
	if (elem.type != NOCT_VALUE_DICT) {
		noct_error(env, "Unexpected parameter value for %s.", name);
		return false;
	}

	if (!noct_get_dict_elem(env, &elem, key, &ival))
		return false;
	if (ival.type != NOCT_VALUE_INT) {
		noct_error(env, "Unexpected parameter value for %s.", name);
		return false;
	}

	*ret = ival.val.i;

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
		RTFUNC(moveToTagFile),
		RTFUNC(moveToNextTag),
		RTFUNC(callTagFunction),
		RTFUNC(loadTexture),
		RTFUNC(renderTexture),
		RTFUNC(draw),
		RTFUNC(destroyTexture),
		RTFUNC(playSound),
		RTFUNC(stopSound),
		RTFUNC(loadFont),
		RTFUNC(createTextTexture),
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
