/* -*- coding: utf-8; tab-width: 8; indent-tabs-mode: t; -*- */

/*
 * Copyright (c) 2025, Awe Morris. All rights reserved.
 */

/*
 * Main header.
 */

#ifndef NOCT2D_ENGINE_H
#define NOCT2D_ENGINE_H

#include <stratohal/platform.h>
#include <noct2d/noct2d.h>

/* Standard C */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

/* The file name of the startup file. */
#define STARTUP_FILE	"main.noct"

/*
 * Maximum properties in a tag.
 */
#define PROP_MAX	128

/*
 * Command struct.
 */
struct tag {
	char *tag_name;
	int prop_count;
	char *prop_name[PROP_MAX];
	char *prop_value[PROP_MAX];
	int line;
};

/* Load a file content. */
bool load_file(const char *file, char **buf, size_t *size);

/* Convert a color code to a pixel value. */
pixel_t color_code_to_pixel_value(const char *code);

/* Get a tag file name. */
const char *get_tag_file_name(void);

/* Get a tag line. */
int get_tag_line(void);

/* Get a current tag. */
struct tag *get_current_tag(void);

#endif
