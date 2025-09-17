/* -*- coding: utf-8; tab-width: 8; indent-tabs-mode: t; -*- */

/*
 * Copyright (c) 2025, Awe Morris. All rights reserved.
 */

#include <playfield/playfield.h>

#include "mainloop.h"
#include "api.h"
#include "vm.h"
#include "i18n.h"

#include <stdio.h>

static bool is_running;
static bool is_fulscreen_start;
static uint64_t lap_origin;

/*
 * This function is called when the app is going to be initialized.
 */
bool on_event_boot(char **title, int *width, int *height)
{
	char *title_ret;
	int width_ret;
	int height_ret;
	bool fullscreen_ret;
	
#ifdef USE_TRANSLATION
	/* Initialize the locale. */
	playfield_init_locale();
#endif

	/* Initialize the API. */
	if (!init_api())
		return false;

	/* Create a VM, then call setup(). */
	if (!create_vm(&title_ret, &width_ret, &height_ret, &fullscreen_ret))
		return false;

	/* Save the window size. */
	if (!set_vm_int("screenWidth", width_ret))
		return false;
	if (!set_vm_int("screenHeight", height_ret))
		return false;

	/* Make the exit flag. */
	if (!set_vm_int("exitFlag", 0))
		return false;

	if (title != NULL)
		*title = title_ret;
	if (width != NULL)
		*width = width_ret;
	if (height != NULL)
		*height = height_ret;
	is_fulscreen_start = fullscreen_ret;

	return true;
}

/*
 * This function is called right before the game loop.
 */
bool on_event_start(void)
{
	if (is_fulscreen_start)
		enter_full_screen_mode();

	/* Initialize the API variables. */
	set_vm_int("mousePosX", 0);
	set_vm_int("mousePosY", 0);
	set_vm_int("millisec", 0);
	set_vm_int("isMouseLeftPressed", 0);
	set_vm_int("isMouseRightPressed", 0);
	set_vm_int("isKeyUpPressed", 0);
	set_vm_int("isKeyDownPressed", 0);
	set_vm_int("isKeyLeftPressed", 0);
	set_vm_int("isKeyRightPressed", 0);
	set_vm_int("isKeyReturnPressed", 0);
        set_vm_int("isGamepadLeftPressed", 0);
        set_vm_int("isGamepadRightPressed", 0);
        set_vm_int("isGamepadUpPressed", 0);
        set_vm_int("isGamepadDownPressed", 0);
        set_vm_int("isGamepadAPressed", 0);
        set_vm_int("isGamepadBPressed", 0);
        set_vm_int("isGamepadXPressed", 0);
        set_vm_int("isGamepadYPressed", 0);
        set_vm_int("isGamepadLPressed", 0);
        set_vm_int("isGamepadRPressed", 0);
	set_vm_int("gamepadAnalogX1", 0);
	set_vm_int("gamepadAnalogY1", 0);
	set_vm_int("gamepadAnalogX2", 0);
	set_vm_int("gamepadAnalogY2", 0);
	set_vm_int("gamepadAnalogL", 0);
	set_vm_int("gamepadAnalogR", 0);

	/* Initialize the lap timer. */
	reset_lap_timer(&lap_origin);

	/* Call start(). */
	if (!call_vm_function("start"))
		return false;

	is_running = true;

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

	is_running = false;
}

void on_event_key_press(int key)
{
	if (!is_running)
		return;

	switch (key) {
	case KEY_LEFT:
		set_vm_int("isKeyLeftPressed", 1);
		break;
	case KEY_RIGHT:
		set_vm_int("isKeyRightPressed", 1);
		break;
	case KEY_UP:
		set_vm_int("isKeyUpPressed", 1);
		break;
	case KEY_DOWN:
		set_vm_int("isKeyDownPressed", 1);
		break;
	case KEY_RETURN:
		set_vm_int("isKeyReturnPressed", 1);
		break;
	case KEY_GAMEPAD_LEFT:
		set_vm_int("isGamepadLeftPressed", 1);
		break;
	case KEY_GAMEPAD_RIGHT:
		set_vm_int("isGamepadRightPressed", 1);
		break;
	case KEY_GAMEPAD_UP:
		set_vm_int("isGamepadUpPressed", 1);
		break;
	case KEY_GAMEPAD_DOWN:
		set_vm_int("isGamepadDownPressed", 1);
		break;
	case KEY_GAMEPAD_A:
		set_vm_int("isGamepadAPressed", 1);
		break;
	case KEY_GAMEPAD_B:
		set_vm_int("isGamepadBPressed", 1);
		break;
	case KEY_GAMEPAD_X:
		set_vm_int("isGamepadXPressed", 1);
		break;
	case KEY_GAMEPAD_Y:
		set_vm_int("isGamepadYPressed", 1);
		break;
	case KEY_GAMEPAD_L:
		set_vm_int("isGamepadLPressed", 1);
		break;
	case KEY_GAMEPAD_R:
		set_vm_int("isGamepadRPressed", 1);
		break;
	default:
		break;
	}
}

void on_event_key_release(int key)
{
	if (!is_running)
		return;

	switch (key) {
	case KEY_LEFT:
		set_vm_int("isKeyLeftPressed", 0);
		break;
	case KEY_RIGHT:
		set_vm_int("isKeyRightPressed", 0);
		break;
	case KEY_UP:
		set_vm_int("isKeyUpPressed", 0);
		break;
	case KEY_DOWN:
		set_vm_int("isKeyDownPressed", 0);
		break;
	case KEY_RETURN:
		set_vm_int("isKeyReturnPressed", 0);
		break;
	case KEY_GAMEPAD_LEFT:
		set_vm_int("isGamepadLeftPressed", 0);
		break;
	case KEY_GAMEPAD_RIGHT:
		set_vm_int("isGamepadRightPressed", 0);
		break;
	case KEY_GAMEPAD_UP:
		set_vm_int("isGamepadUpPressed", 0);
		break;
	case KEY_GAMEPAD_DOWN:
		set_vm_int("isGamepadDownPressed", 0);
		break;
	case KEY_GAMEPAD_A:
		set_vm_int("isGamepadAPressed", 0);
		break;
	case KEY_GAMEPAD_B:
		set_vm_int("isGamepadBPressed", 0);
		break;
	case KEY_GAMEPAD_X:
		set_vm_int("isGamepadXPressed", 0);
		break;
	case KEY_GAMEPAD_Y:
		set_vm_int("isGamepadYPressed", 0);
		break;
	case KEY_GAMEPAD_L:
		set_vm_int("isGamepadLPressed", 0);
		break;
	case KEY_GAMEPAD_R:
		set_vm_int("isGamepadRPressed", 0);
		break;
	default:
		break;
	}
}

void on_event_mouse_press(int button, int x, int y)
{
	if (is_running) {
		set_vm_int("mousePosX", x);
		set_vm_int("mousePosY", y);

		if (button == MOUSE_LEFT)
			set_vm_int("isMouseLeftPressed", 1);
		else
			set_vm_int("isMouseRightPressed", 1);
	}
}

void on_event_mouse_release(int button, int x, int y)
{
	if (is_running) {
		set_vm_int("mousePosX", x);
		set_vm_int("mousePosY", y);

		if (button == MOUSE_LEFT)
			set_vm_int("isMouseLeftPressed", 0);
		else
			set_vm_int("isMouseRightPressed", 0);
	}
}

void on_event_mouse_move(int x, int y)
{
	if (is_running) {
		set_vm_int("mousePosX", x);
		set_vm_int("mousePosY", y);
	}
}

void on_event_analog_input(int input, int val)
{
	if (is_running) {
		switch (input) {
		case ANALOG_X1:
			set_vm_int("gamepadAnalogX1", val);
			break;
		case ANALOG_Y1:
			set_vm_int("gamepadAnalogY1", val);
			break;
		case ANALOG_X2:
			set_vm_int("gamepadAnalogX2", val);
			break;
		case ANALOG_Y2:
			set_vm_int("gamepadAnalogY2", val);
			break;
		case ANALOG_L:
			set_vm_int("gamepadAnalogL", val);
			break;
		case ANALOG_R:
			set_vm_int("gamepadAnalogR", val);
			break;
		default:
			break;
		}
	}
}

void on_event_touch_cancel(void)
{
	if (is_running) {
	}
}

void on_event_swipe_down(void)
{
	if (is_running) {
	}
}

void on_event_swipe_up(void)
{
	if (is_running) {
	}
}
