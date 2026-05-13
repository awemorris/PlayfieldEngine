/* -*- coding: utf-8; tab-width: 8; indent-tabs-mode: t; -*- */

/*
 * StratoHAL
 * C# Support
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

#ifndef STRATOHAL_CSHARP_H
#define STRATOHAL_CSHARP_H

#ifndef HAL_USE_CSHARP
#error "C# support is not enabled."
#endif

#include <strato/strato.h>

#define UNSAFEPTR(t)  intptr_t	/* For C# */

HAL_DLL
void init_hal_func_table(
	void (*p_log_info)(UNSAFEPTR(const char *) s),
	void (*p_log_warn)(UNSAFEPTR(const char *) s),
	void (*p_log_error)(UNSAFEPTR(const char *) s),
	void (*p_log_out_of_memory)(void),
	void (*p_make_save_directory)(void),
	void (*p_make_real_path)(UNSAFEPTR(const char *) fname, UNSAFEPTR(const char *) dst, int len),
	void (*p_notify_image_update)(int id, int width, int height, UNSAFEPTR(const uint32_t *) pixels),
	void (*p_notify_image_free)(int id),
	void (*p_render_image_normal)(int dst_left, int dst_top, int dst_width, int dst_height, int src_img, int src_left, int src_top, int src_width, int src_height, int alpha),
	void (*p_render_image_add)(int dst_left, int dst_top, int dst_width, int dst_height, int src_img, int src_left, int src_top, int src_width, int src_height, int alpha),
	void (*p_render_image_sub)(int dst_left, int dst_top, int dst_width, int dst_height, int src_img, int src_left, int src_top, int src_width, int src_height, int alpha),
	void (*p_render_image_dim)(int dst_left, int dst_top, int dst_width, int dst_height, int src_img, int src_left, int src_top, int src_width, int src_height, int alpha),
	void (*p_render_image_rule)(int src_img, int rule_img, int threshold),
	void (*p_render_image_melt)(int src_img, int rule_img, int progress),
	void (*p_render_image_cross)(int src_img, int rule_img, int src1_left, int src1_top, int src2_left, int src2_top, int progress),
	void (*p_render_image_3d_normal)(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, int src_img, int src_left, int src_top, int src_width, int src_height, int alpha),
	void (*p_render_image_3d_add)(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, int src_img, int src_left, int src_top, int src_width, int src_height, int alpha),
	void (*p_render_image_3d_sub)(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, int src_img, int src_left, int src_top, int src_width, int src_height, int alpha),
	void (*p_render_image_3d_dim)(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, int src_img, int src_left, int src_top, int src_width, int src_height, int alpha),
	void (*p_render_image_3d_cross)(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, int src_img, float src1_x1, float src1_y1, float src1_x2, float src1_y2, float src1_x3, float src1_y3, float src1_x4, float src1_y4, float src2_x1, float src2_y1, float src2_x2, float src2_y2, float src2_x3, float src2_y3, float src2_x4, float src2_y4, int alpha),
	void (*p_reset_lap_timer)(UNSAFEPTR(uint64_t *) origin),
	uint64_t (*p_get_lap_timer_millisec)(UNSAFEPTR(uint64_t *) origin),
	void (*p_play_sound)(int stream, UNSAFEPTR(void *) wave),
	void (*p_stop_sound)(int stream),
	void (*p_set_sound_volume)(int stream, float vol),
	bool (*p_is_sound_finished)(int stream),
	bool (*p_play_video)(UNSAFEPTR(const char *) fname, bool is_skippable),
	void (*p_stop_video)(void),
	bool (*p_is_video_playing)(void),
	bool (*p_is_full_screen_supported)(void),
	bool (*p_is_full_screen_mode)(void),
	void (*p_enter_full_screen_mode)(void),
	void (*p_leave_full_screen_mode)(void),
	void (*p_get_system_language)(UNSAFEPTR(char *) dst, int len),
	void (*p_set_continuous_swipe_enabled)(bool is_enabled),
	void (*p_free_shared)(UNSAFEPTR(void *) p),
	bool (*p_check_file_exist)(UNSAFEPTR(const char *) file_name),
	UNSAFEPTR(void *) (*p_get_file_contents)(UNSAFEPTR(const char *) file_name, UNSAFEPTR(int *) len),
	void (*p_open_save_file)(UNSAFEPTR(const char *) file_name),
	void (*p_write_save_file)(int b),
	void (*p_close_save_file)(void)
);

#endif
