/* -*- coding: utf-8; tab-width: 8; indent-tabs-mode: t; -*- */

/*
 * Copyright (c) 2025, Awe Morris. All rights reserved.
 */

#include "engine.h"
#include "vm.h"

/* The runtime. */
struct rt_env *rt;

/* Forward Declaration */
static bool setup_variables(void);
static bool load_startup_file(void);
static bool call_setup(char **title, int *width, int *height);
static bool get_int_param(struct rt_env *rt, const char *name, int *ret);
#if 0
static bool get_float_param(struct rt_env *rt, const char *name, float *ret);
#endif
static bool get_string_param(struct rt_env *rt, const char *name, const char **ret);
static bool get_dict_elem_int_param(struct rt_env *rt, const char *name, const char *key, int *ret);
static bool install_api(struct rt_env *rt);

/*
 * Create a VM.
 */
bool create_vm(char **title, int *width, int *height)
{
	/* Create a language runtime. */
	if (!noct_create(&rt))
		return false;

	/* Setup variables. */
	if (!setup_variables())
		return false;

	/* Load the startup file. */
	if (!load_startup_file())
		return false;

	/* Call "setup()" and get a title and window size. */
	if (!call_setup(title, width, height)) {
		log_error(_("%s:%d: error: %s\n"),
			  noct_get_error_file(rt),
			  noct_get_error_line(rt),
			  noct_get_error_message(rt));
		return false;
	}

	/* Install the API to the runtime. */
	if (!install_api(rt))
		return false;

	return true;
}

/* Setup global variables. */
static bool setup_variables(void)
{
	struct rt_value dict;
	bool succeeded;

	/* Try: */
	succeeded = false;
	do {
		/* Add a global variable "App". */
		if (!noct_make_empty_dict(rt, &dict))
			break;
		if (!noct_set_global(rt, "App", &dict))
			break;

		succeeded = true;
	} while (0);

	if (!succeeded) {
		log_error(_("error: %s\n"), noct_get_error_message(rt));
		return false;
	}

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
	if (!noct_register_source(rt, STARTUP_FILE, buf)) {
		log_error(_("%s:%d: error: %s"),
			  noct_get_error_file(rt),
			  noct_get_error_line(rt),
			  noct_get_error_message(rt));
		return false;
	}

	free(buf);

	return true;
}

/* Call "setup()" function to determin a title, width, and height. */
static bool call_setup(char **title, int *width, int *height)
{
	struct rt_value ret;
	struct rt_value title_val;
	struct rt_value width_val;
	struct rt_value height_val;
	const char *title_s;
	bool succeeded;

	succeeded = false;
	do {
		/* Call setup() and get a return dictionary. */
		if (!noct_call_with_name(rt, "setup", NULL, 0, NULL, &ret))
			break;

		/* Get the "title" element from the dictionary. */
		if (title != NULL) {
			if (!noct_get_dict_elem(rt, &ret, "title", &title_val))
				break;
			if (!noct_get_string(rt, &title_val, &title_s))
				break;
			*title = strdup(title_s);
		}

		/* Get the "width" element from the dictionary. */
		if (width != NULL) {
			if (!noct_get_dict_elem(rt, &ret, "width", &width_val))
				break;
			if (!noct_get_int(rt, &width_val, width))
				break;
		}

		/* Get the "height" element from the dictionary. */
		if (height != NULL) {
			if (!noct_get_dict_elem(rt, &ret, "height", &height_val))
				break;
			if (!noct_get_int(rt, &height_val, height))
				break;
		}

		noct_shallow_gc(rt);

		succeeded = true;
	} while (0);
	if (!succeeded) {
		log_error(_("%s:%d: error: %s\n"),
			  noct_get_error_file(rt),
			  noct_get_error_line(rt),
			  noct_get_error_message(rt));
	}
	
	return true;
}

/*
 * Call a VM function.
 */
bool call_vm_function(const char *func_name)
{
	struct rt_value ret;

	/* Call a function. */
	if (!noct_call_with_name(rt, func_name, NULL, 0, NULL, &ret)) {
		log_error(_("%s:%d: error: %s\n"),
			  noct_get_error_file(rt),
			  noct_get_error_line(rt),
			  noct_get_error_message(rt));
		return false;
	}

	/* Do a shallow GC. */
	shallow_gc();

	/* Do a deep GC if required. */
	if (get_heap_usage() > 256 * 1024 * 1024)
		deep_gc();

	return true;
}

/*
 * Call a tag function.
 */
bool call_vm_tag_function(void)
{
	struct tag *t;
	struct rt_value dict;
	int i;
	char func_name[256];
	struct rt_value func_val;
	struct rt_func *func;
	struct rt_value ret;

	/* Get a current command. */
	t = get_current_tag();
	if (t == NULL) {
		/* Reached to the end. Finish the game loop. */
		return false;
	}

	/* Make a parameter dictionary. */
	if (!noct_make_empty_dict(rt, &dict)) {
		log_error(_("In scenario %s:%d: runtime error.\n"),
			  get_tag_file_name(),
			  get_tag_line());
		return false;
	}

	/* Setup properties as dictionary items. */
	for (i = 0; i < t->prop_count; i++) {
		struct rt_value str;
		if (!noct_make_string(rt, &str, t->prop_value[i])) {
			log_error(_("In scenario %s:%d: runtime error.\n"),
				  get_tag_file_name(),
				  get_tag_line());
			return false;
		}
		if (!noct_set_dict_elem(rt, &dict, t->prop_name[i], &str)) {
			log_error(_("In scenario %s:%d: runtime error.\n"),
				  get_tag_file_name(),
				  get_tag_line());
			return false;
		}
	}

	/* Make a tag function name. */
	snprintf(func_name, sizeof(func_name), "tag_%s", t->tag_name);

	/* Get a corresponding function.  */
	if (!noct_get_global(rt, func_name, &func_val)) {
		log_error(_("%s:%d: Tag \"%s\" not found.\n"),
			  get_tag_file_name(),
			  get_tag_line(),
			  t->tag_name);
		return false;
	}
	if (!noct_get_func(rt, &func_val, &func)) {
		log_error(_("%s:%d: \"tag_%s\" is not a function.\n"),
			  get_tag_file_name(),
			  get_tag_line(),
			  t->tag_name);
		return false;
	}

	/* Call the function. */
	if (!noct_call_with_name(rt, func_name, NULL, 1, &dict, &ret)) {
		log_error(_("In scenario %s:%d: Tag \"%s\" execution error.\n"),
			  get_tag_file_name(),
			  get_tag_line(),
			  t->tag_name);
		log_error(_("%s:%d: %s"),
			  noct_get_error_file(rt),
			  noct_get_error_line(rt),
			  noct_get_error_message(rt));
		return false;
	}

	return true;
}

/*
 * Set a VM integer.
 */
bool set_vm_int(const char *prop_name, int val)
{
	struct rt_value api, prop_val;

	if (!noct_get_global(rt, "API", &api))
		return false;
	noct_make_int(&prop_val, val);
	if (!noct_set_dict_elem(rt, &api, prop_name, &prop_val))
		return false;

	return true;
}

/*
 * Get the heap usage.
 */
size_t get_heap_usage(void)
{
	size_t ret;

	rt_get_heap_usage(rt, &ret);

	return ret;
}

/*
 * Do a shallow GC.
 */
void shallow_gc(void)
{
	noct_shallow_gc(rt);
}

/*
 * Do a deep GC.
 */
void deep_gc(void)
{
	noct_deep_gc(rt);
}

/*
 * API
 */

/* debug() */
static bool debug(struct rt_env *rt)
{
	struct rt_value param;
	int type;
	bool succeeded;

	type = 0;
	succeeded = false;
	do {
		if (!noct_get_arg(rt, 0, &param))
			break;

		if (!noct_get_value_type(rt, &param, &type))
			break;

		succeeded = true;
	} while (0);
	if (!succeeded) {
		log_error(_("%s:%d: error: %s\n"),
			  noct_get_error_file(rt),
			  noct_get_error_line(rt),
			  noct_get_error_message(rt));
		return false;
	}

	switch (type) {
	case NOCT_VALUE_INT:
	{
		int d;
		noct_get_int(rt, &param, &d);
		printf("%d\n", d);
		break;
	}
	case NOCT_VALUE_FLOAT:
	{
		float f;
		noct_get_float(rt, &param, &f);
		printf("%f\n", f);
		break;
	}
	case NOCT_VALUE_STRING:
	{
		const char *s;
		noct_get_string(rt, &param, &s);
		printf("%s\n", s);
		break;
	}
	default:
		printf("[object]\n");
		break;
	}

	return true;
}

/* API.moveToTagFile() */
static bool API_moveToTagFile(struct rt_env *rt)
{
	const char *file;

	if (!get_string_param(rt, "file", &file))
		return false;

	if (!move_to_tag_file(file))
		return false;

	return true;
}

/* API.moveToNextTag() */
static bool API_moveToNextTag(struct rt_env *rt)
{
	UNUSED_PARAMETER(rt);

	move_to_next_tag();

	return true;
}

/* API.callTagFunction() */
static bool API_callTagFunction(struct rt_env *rt)
{
	UNUSED_PARAMETER(rt);

	if (!call_vm_tag_function())
		return false;

	return true;
}

/* API.loadTexture() */
static bool API_loadTexture(struct rt_env *rt)
{
	const char *file;
	int tex_id;
	int tex_width;
	int tex_height;
	struct rt_value ret, ival;

	if (!get_string_param(rt, "file", &file)) {
		noct_error(rt, _("file parameter is not set."));
		return false;
	}

	if (!load_texture(file, &tex_id, &tex_width, &tex_height)) {
		noct_error(rt, _("Failed to load a texture."));
		return false;
	}

	if (!noct_make_empty_dict(rt, &ret))
		return false;

	noct_make_int(&ival, tex_id);
	if (!noct_set_dict_elem(rt, &ret, "id", &ival))
		return false;
	
	noct_make_int(&ival, tex_width);
	if (!noct_set_dict_elem(rt, &ret, "width", &ival))
		return false;

	noct_make_int(&ival, tex_height);
	if (!noct_set_dict_elem(rt, &ret, "height", &ival))
		return false;

	if (!noct_set_return(rt, &ret))
		return false;

	return true;
}

/* API.renderTexture() */
static bool API_renderTexture(struct rt_env *rt)
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

	if (!get_int_param(rt, "dstLeft", &dst_left))
		return false;
	if (!get_int_param(rt, "dstTop", &dst_top))
		return false;
	if (!get_int_param(rt, "dstWidth", &dst_width))
		return false;
	if (!get_int_param(rt, "dstHeight", &dst_height))
		return false;
	if (!get_dict_elem_int_param(rt, "texture", "id", &tex_id))
		return false;
	if (!get_int_param(rt, "srcLeft", &src_left))
		return false;
	if (!get_int_param(rt, "srcTop", &src_top))
		return false;
	if (!get_int_param(rt, "srcWidth", &src_width))
		return false;
	if (!get_int_param(rt, "srcHeight", &src_height))
		return false;
	if (!get_int_param(rt, "alpha", &alpha))
		return false;

	render_texture(dst_left,
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

/* API.destroyTexture() */
static bool API_destroyTexture(struct rt_env *rt)
{
	int tex_id;

	if (!get_dict_elem_int_param(rt, "texture", "id", &tex_id))
		return false;

	destroy_texture(tex_id);

	return true;
}

/* API.playSound() */
static bool API_playSound(struct rt_env *rt)
{
	int stream;
	const char *file;
	struct rt_value ret;

	if (!get_int_param(rt, "stream", &stream))
		return false;
	if (!get_string_param(rt, "file", &file))
		return false;

	if (!play_sound_stream(stream, file))
		return false;

	noct_make_int(&ret, 1);
	if (!noct_set_return(rt, &ret))
		return false;

	return true;
}

/* API.stopSound() */
static bool API_stopSound(struct rt_env *rt)
{
	int stream;
	struct rt_value ret;

	if (!get_int_param(rt, "stream", &stream))
		return false;

	if (!stop_sound_stream(stream))
		return false;

	noct_make_int(&ret, 1);
	if (!noct_set_return(rt, &ret))
		return false;

	return true;
}

/* API.loadFont() */
static bool API_loadFont(struct rt_env *rt)
{
	int slot;
	const char *file;
	struct rt_value ret;

	if (!get_int_param(rt, "slot", &slot))
		return false;
	if (!get_string_param(rt, "file", &file))
		return false;

	if (!load_font(slot, file))
		return false;

	noct_make_int(&ret, 1);
	if (!noct_set_return(rt, &ret))
		return false;
	
	return true;
}

/* API.createTextTexture() */
static bool API_createTextTexture(struct rt_env *rt)
{
	int slot;
	const char *text;
	int size;
	const char *color;
	pixel_t pcolor;
	int tex_id;
	int tex_width;
	int tex_height;
	struct rt_value ret;
	struct rt_value ival;

	if (!get_int_param(rt, "slot", &slot))
		return false;
	if (!get_string_param(rt, "text", &text))
		return false;
	if (!get_int_param(rt, "size", &size))
		return false;
	if (!get_string_param(rt, "color", &color))
		return false;

	pcolor = color_code_to_pixel_value(color);

	if (!create_text_texture(slot, text, size, pcolor, &tex_id, &tex_width, &tex_height))
		return false;

	if (!noct_make_empty_dict(rt, &ret))
		return false;

	noct_make_int(&ival, tex_id);
	if (!noct_set_dict_elem(rt, &ret, "id", &ival))
		return false;
	
	noct_make_int(&ival, tex_width);
	if (!noct_set_dict_elem(rt, &ret, "width", &ival))
		return false;

	noct_make_int(&ival, tex_height);
	if (!noct_set_dict_elem(rt, &ret, "height", &ival))
		return false;

	if (!noct_set_return(rt, &ret))
		return false;

	return true;
}

/*
 * Helpers
 */

/* Get an integer parameter. */
static bool get_int_param(struct rt_env *rt, const char *name, int *ret)
{
	struct rt_value param, elem;
	float f;
	const char *s;

	if (!noct_get_arg(rt, 0, &param))
		return false;

	if (!noct_get_dict_elem(rt, &param, name, &elem))
		return false;

	switch (elem.type) {
	case NOCT_VALUE_INT:
		noct_get_int(rt, &elem, ret);
		break;
	case NOCT_VALUE_FLOAT:
		noct_get_float(rt, &elem, &f);
		*ret = (int)f;
		break;
	case NOCT_VALUE_STRING:
		noct_get_string(rt, &elem, &s);
		*ret = atoi(s);
		break;
	default:
		noct_error(rt, "Unexpected parameter value for %s.", name);
		return false;
	}

	return true;
}

#if 0
/* Get a float parameter. */
static bool get_float_param(struct rt_env *rt, const char *name, float *ret)
{
	struct rt_value param, elem;

	if (!rt_get_arg(rt, 0, &param))
		return false;

	if (!rt_get_dict_elem(rt, &param, name, &elem))
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
		rt_error(rt, "Unexpected parameter value for %s.", name);
		return false;
	}

	return true;
}
#endif

/* Get a string parameter. */
static bool get_string_param(struct rt_env *rt, const char *name, const char **ret)
{
	struct rt_value param, elem;
	static char buf[128];

	if (!noct_get_arg(rt, 0, &param))
		return false;

	if (!noct_get_dict_elem(rt, &param, name, &elem))
		return false;

	switch (elem.type) {
	case NOCT_VALUE_INT:
	{
		int i;
		noct_get_int(rt, &elem, &i);
		snprintf(buf, sizeof(buf), "%d", i);
		*ret = buf;
		break;
	}
	case NOCT_VALUE_FLOAT:
	{
		float f;
		noct_get_float(rt, &elem, &f);
		snprintf(buf, sizeof(buf), "%f", f);
		*ret = buf;
		break;
	}
	case NOCT_VALUE_STRING:
		noct_get_string(rt, &elem, ret);
		break;
	default:
		noct_error(rt, "Unexpected parameter value for %s.", name);
		return false;
	}

	return true;
}

/* Get an integer parameter. */
static bool get_dict_elem_int_param(struct rt_env *rt, const char *name, const char *key, int *ret)
{
	struct rt_value param, elem, ival;

	if (!noct_get_arg(rt, 0, &param))
		return false;

	if (!noct_get_dict_elem(rt, &param, name, &elem))
		return false;
	if (elem.type != NOCT_VALUE_DICT) {
		noct_error(rt, "Unexpected parameter value for %s.", name);
		return false;
	}

	if (!noct_get_dict_elem(rt, &elem, key, &ival))
		return false;
	if (ival.type != NOCT_VALUE_INT) {
		noct_error(rt, "Unexpected parameter value for %s.", name);
		return false;
	}

	*ret = ival.val.i;

	return true;
}

/*
 * API Installation
 */

/*
 * Install API functions to a runtime.
 */
bool install_api(struct rt_env *rt)
{
	const char *params[] = {"param"};
	struct func {
		bool (*func)(struct rt_env *);
		const char *field;
		const char *name;
	} funcs[] = {
#define RTFUNC(name) {API_##name, #name, "api_" # name}
		{debug, NULL, "debug"},
		RTFUNC(moveToTagFile),
		RTFUNC(moveToNextTag),
		RTFUNC(callTagFunction),
		RTFUNC(loadTexture),
		RTFUNC(renderTexture),
		RTFUNC(destroyTexture),
		RTFUNC(playSound),
		RTFUNC(stopSound),
		RTFUNC(loadFont),
		RTFUNC(createTextTexture),
	};
	const int tbl_size = sizeof(funcs) / sizeof(struct func);
	struct rt_value dict;
	int i;

	/* Make a global variable "API". */
	if (!noct_make_empty_dict(rt, &dict))
		return false;
	if (!noct_set_global(rt, "API", &dict))
		return false;

	/* Register functions. */
	for (i = 0; i < tbl_size; i++) {
		struct rt_value funcval;

		/* Register a cfunc. */
		if (!noct_register_cfunc(rt, funcs[i].name, 1, params, funcs[i].func, NULL))
			return false;

		/* Add to the API dictionary. */
		if (funcs[i].field != NULL) {
			/* Get a function value. */
			if (!noct_get_global(rt, funcs[i].name, &funcval))
				return false;

			/* Make a dictionary element. */
			if (!noct_set_dict_elem(rt, &dict, funcs[i].field, &funcval))
				return false;
		}
	}

	return true;
}
