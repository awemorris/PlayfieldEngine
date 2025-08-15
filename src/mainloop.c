/* -*- coding: utf-8; tab-width: 8; indent-tabs-mode: t; -*- */

/*
 * Copyright (c) 2025, Awe Morris. All rights reserved.
 */

#include <noct2d/noct2d.h>

#include "mainloop.h"
#include "api.h"
#include "vm.h"
#include "i18n.h"

#include <stdio.h>

static uint64_t lap_origin;

/*
 * This function is called when the app is going to be initialized.
 */
bool on_event_boot(char **title, int *width, int *height)
{
#ifdef USE_TRANSLATION
	/* Initialize the locale. */
	noct2d_init_locale();
#endif

	/* Initialize the API. */
	if (!init_api())
		return false;

	/* Create a VM, then call setup(). */
	if (!create_vm(title, width, height))
		return false;

	/* Save the window size. */
	if (!set_vm_int("screenWidth", *width))
		return false;
	if (!set_vm_int("screenHeight", *height))
		return false;

	/* Make the exit flag. */
	if (!set_vm_int("exitFlag", 0))
		return false;

	return true;
}

/*
 * This function is called right before the game loop.
 */
bool on_event_start(void)
{
	/* Initialize the API variables. */
	set_vm_int("mousePosX", 0);
	set_vm_int("mousePosY", 0);
	set_vm_int("millisec", 0);
	set_vm_int("isMouseLeftPressed", 0);
	set_vm_int("isMouseRightPressed", 0);

	/* Initialize the lap timer. */
	reset_lap_timer(&lap_origin);

	/* Call start(). */
	if (!call_vm_function("start"))
		return false;

	return true;
}

/*
 * This function is called every frame periodically.
 */
bool on_event_frame(void)
{
	int exit_flag;

	/* Get the lap timer. */
	set_vm_int("millisec", (int)get_lap_timer_millisec(&lap_origin));

	/* Call frame(). */
	if (!call_vm_function("frame"))
		return false;

	/* Check the exit flag. */
	exit_flag = 0;
	get_vm_int("exitFlag", &exit_flag);
	if (exit_flag) {
		/* Exit the game loop. */
		return false;
	}

	/* Clear input states. */
	set_vm_int("isMouseLeftPressed", 0);
	set_vm_int("isMouseRightPressed", 0);

	/* Continue the game loop. */
	return true;
}

void on_event_stop(void)
{
	/* Cleanup the API */
	cleanup_api();

	/* Destroy the VM. */
	destroy_vm();
}

void on_event_key_press(int key)
{
	UNUSED_PARAMETER(key);
}

void on_event_key_release(int key)
{
	UNUSED_PARAMETER(key);
}

void on_event_mouse_press(int button, int x, int y)
{
	set_vm_int("mousePosX", x);
	set_vm_int("mousePosY", y);

	if (button == MOUSE_LEFT)
		set_vm_int("isMouseLeftPressed", 1);
	else
		set_vm_int("isMouseRightPressed", 1);
}

void on_event_mouse_release(int button, int x, int y)
{
	set_vm_int("mousePosX", x);
	set_vm_int("mousePosY", y);

	if (button == MOUSE_LEFT)
		set_vm_int("isMouseLeftPressed", 0);
	else
		set_vm_int("isMouseRightPressed", 0);
}

void on_event_mouse_move(int x, int y)
{
	set_vm_int("mousePosX", x);
	set_vm_int("mousePosY", y);
}

void on_event_touch_cancel(void)
{
}

void on_event_swipe_down(void)
{
}

void on_event_swipe_up(void)
{
}
