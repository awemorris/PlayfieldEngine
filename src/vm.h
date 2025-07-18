/* -*- coding: utf-8; tab-width: 8; indent-tabs-mode: t; -*- */

/*
 * Copyright (c) 2025, Awe Morris. All rights reserved.
 */

#ifndef ENGINE_VM_H
#define ENGINE_VM_H

#include "stratohal/c89compat.h"

bool create_vm(char **title, int *width, int *height);
bool call_vm_function(const char *func_name);
bool call_vm_tag_function(void);
bool set_vm_int(const char *prop_name, int val);
size_t get_heap_usage(void);
void shallow_gc(void);
void deep_gc(void);

#endif
