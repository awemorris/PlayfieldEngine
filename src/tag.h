/* -*- coding: utf-8; tab-width: 8; indent-tabs-mode: t; -*- */

/*
 * Copyright (c) 2025, Awe Morris. All rights reserved.
 */

/*
 * Tag System
 */

#ifndef PLAYFIELD_TAG_H
#define PLAYFIELD_TAG_H

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

#endif
