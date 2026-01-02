/* -*- coding: utf-8; tab-width: 8; indent-tabs-mode: t; -*- */

/*
 * Copyright (c) 2025, Awe Morris. All rights reserved.
 */

#ifndef PLAYFIELD_VM_H
#define PLAYFIELD_VM_H

#include "stratohal/platform.h"

bool create_vm(char **title, int *width, int *height, bool *fullscreen);
void destroy_vm(void);

#endif
