/* -*- coding: utf-8; tab-width: 8; indent-tabs-mode: t; -*- */

/*
 * Strato HAL
 * Swift support
 */

/*-
 * SPDX-License-Identifier: Zlib
 *
 * Playfield Engine
 * Copyright (c) 2025-2026 Awe Morris
 *
 * This software is derived from the codebase of Suika2.
 * Copyright (c) 1996-2024 Keiichi Tabata
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *      claim that you wrote the original software. If you use this software
 *      in a product, an acknowledgment in the product documentation would be
 *      appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *      misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 */

#ifndef STRATOHAL_SWIFT_H
#define STRATOHAL_SWIFT_H

#ifndef HAL_USE_SWIFT
#error "Swift support is not enabled."
#endif

#include <strato/strato.h>

/*
 * Swift Function Pointers
 */

extern void (*swift_log_info)(const char *s);
extern void (*swift_log_warn)(const char *s);
extern void (*swift_log_error)(const char *s);
extern void (*swift_make_save_directory)(void);
extern void (*swift_make_real_path)(const char *dir, const char *fname, const char *dst, int len);
extern void (*swift_notify_image_update)(int id, int width, int height, const uint32_t *pixels);
extern void (*swift_notify_image_free)(int id);
extern void (*swift_render_image_normal)(int dst_left, int dst_top, int dst_width, int dst_height, int src_img, int src_left, int src_top, int src_width, int src_height, int alpha);
extern void (*swift_render_image_add)(int dst_left, int dst_top, int dst_width, int dst_height, int src_img, int src_left, int src_top, int src_width, int src_height, int alpha);
extern void (*swift_render_image_sub)(int dst_left, int dst_top, int dst_width, int dst_height, int src_img, int src_left, int src_top, int src_width, int src_height, int alpha);
extern void (*swift_render_image_dim)(int dst_left, int dst_top, int dst_width, int dst_height, int src_img, int src_left, int src_top, int src_width, int src_height, int alpha);
extern void (*swift_render_image_rule)(int src_img, int rule_img, int threshold);
extern void (*swift_render_image_melt)(int src_img, int rule_img, int progress);
extern void (*swift_render_image_3d_normal)(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, int src_img, int src_left, int src_top, int src_width, int src_height, int alpha);
extern void (*swift_render_image_3d_add)(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, int src_img, int src_left, int src_top, int src_width, int src_height, int alpha);
extern void (*swift_render_image_3d_sub)(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, int src_img, int src_left, int src_top, int src_width, int src_height, int alpha);
extern void (*swift_render_image_3d_dim)(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, int src_img, int src_left, int src_top, int src_width, int src_height, int alpha);
extern void (*swift_reset_lap_timer)(uint64_t *origin);
extern uint64_t (*swift_get_lap_timer_millisec)(uint64_t *origin);
extern void (*swift_play_sound)(int stream, void *wave);
extern void (*swift_stop_sound)(int stream);
extern void (*swift_set_sound_volume)(int stream, float vol);
extern int (*swift_is_sound_finished)(int stream);
extern bool (*swift_play_video)(const char *fname, bool is_skippable);
extern void (*swift_stop_video)(void);
extern bool (*swift_is_video_playing)(void);
extern bool (*swift_is_full_screen_supported)(void);
extern bool (*swift_is_full_screen_mode)(void);
extern void (*swift_enter_full_screen_mode)(void);
extern void (*swift_leave_full_screen_mode)(void);
extern void (*swift_get_system_language)(char *dst, int len);
extern void (*swift_set_continuous_swipe_enabled)(bool is_enabled);
extern void (*swift_free_shared)(void *p);
extern bool (*swift_check_file_exist)(const char *file_name);
extern void *(*swift_get_file_contents)(const char *file_name, int *len);
extern void (*swift_open_save_file)(const char *file_name);
extern void (*swift_write_save_file)(int b);
extern void (*swift_close_save_file)(void);

#endif
