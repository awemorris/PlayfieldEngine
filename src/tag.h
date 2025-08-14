/* -*- coding: utf-8; tab-width: 8; indent-tabs-mode: t; -*- */

/*
 * Copyright (c) 2025, Awe Morris. All rights reserved.
 */

/*
 * Tag System
 */

#ifndef NOCT2D_TAG_H
#define NOCT2D_TAG_H

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

/* Initialize the tag system. */
void init_tag(void);

/* Cleanup the tag system. */
void cleanup_tag(void);

/* Load a tag file. */
bool load_tag_file(const char *file);

/* Get a tag file name. */
const char *get_tag_file_name(void);

/* Get a tag line. */
int get_tag_line(void);

/* Get a current tag. */
struct tag *get_current_tag(void);

/* Move to the next tag. */
void move_to_next_tag(void);

#endif
