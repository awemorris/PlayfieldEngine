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
	set_vm_int("isEscapeKeyPressed", 0);
	set_vm_int("isReturnKeyPressed", 0);
	set_vm_int("isSpaceKeyPressed", 0);
	set_vm_int("isTabKeyPressed", 0);
	set_vm_int("isBackspaceKeyPressed", 0);
	set_vm_int("isDeleteKeyPressed", 0);
	set_vm_int("isHomeKeyPressed", 0);
	set_vm_int("isEndKeyPressed", 0);
	set_vm_int("isPageupKeyPressed", 0);
	set_vm_int("isPagedownKeyPressed", 0);
	set_vm_int("isShiftKeyPressed", 0);
	set_vm_int("isControlKeyPressed", 0);
	set_vm_int("isAltKeyPressed", 0);
	set_vm_int("isUpKeyPressed", 0);
	set_vm_int("isDownKeyPressed", 0);
	set_vm_int("isLeftKeyPressed", 0);
	set_vm_int("isRightKeyPressed", 0);
	set_vm_int("isAKeyPressed", 0);
	set_vm_int("isBKeyPressed", 0);
	set_vm_int("isCKeyPressed", 0);
	set_vm_int("isDKeyPressed", 0);
	set_vm_int("isEKeyPressed", 0);
	set_vm_int("isFKeyPressed", 0);
	set_vm_int("isGKeyPressed", 0);
	set_vm_int("isHKeyPressed", 0);
	set_vm_int("isIKeyPressed", 0);
	set_vm_int("isJKeyPressed", 0);
	set_vm_int("isKKeyPressed", 0);
	set_vm_int("isLKeyPressed", 0);
	set_vm_int("isMKeyPressed", 0);
	set_vm_int("isNKeyPressed", 0);
	set_vm_int("isOKeyPressed", 0);
	set_vm_int("isPKeyPressed", 0);
	set_vm_int("isQKeyPressed", 0);
	set_vm_int("isRKeyPressed", 0);
	set_vm_int("isSKeyPressed", 0);
	set_vm_int("isTKeyPressed", 0);
	set_vm_int("isUKeyPressed", 0);
	set_vm_int("isVKeyPressed", 0);
	set_vm_int("isWKeyPressed", 0);
	set_vm_int("isXKeyPressed", 0);
	set_vm_int("isYKeyPressed", 0);
	set_vm_int("isZKeyPressed", 0);
	set_vm_int("is1KeyPressed", 0);
	set_vm_int("is2KeyPressed", 0);
	set_vm_int("is3KeyPressed", 0);
	set_vm_int("is4KeyPressed", 0);
	set_vm_int("is5KeyPressed", 0);
	set_vm_int("is6KeyPressed", 0);
	set_vm_int("is7KeyPressed", 0);
	set_vm_int("is8KeyPressed", 0);
	set_vm_int("is9KeyPressed", 0);
	set_vm_int("is0KeyPressed", 0);
	set_vm_int("isF1KeyPressed", 0);
	set_vm_int("isF2KeyPressed", 0);
	set_vm_int("isF3KeyPressed", 0);
	set_vm_int("isF4KeyPressed", 0);
	set_vm_int("isF5KeyPressed", 0);
	set_vm_int("isF6KeyPressed", 0);
	set_vm_int("isF7KeyPressed", 0);
	set_vm_int("isF8KeyPressed", 0);
	set_vm_int("isF9KeyPressed", 0);
	set_vm_int("isF10KeyPressed", 0);
	set_vm_int("isF11KeyPressed", 0);
	set_vm_int("isF12KeyPressed", 0);
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

	/* Initialize the upper layer. */
#ifdef USE_INITHOOK
	playfield_init_hook();
#endif

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

	/* Call update(). */
	if (!call_vm_function("update"))
		return false;

	/* Call render(). */
	if (!call_vm_function("render"))
		return false;

	/* Check the exit flag. */
	exit_flag = 0;
	get_vm_int("exitFlag", &exit_flag);
	if (exit_flag) {
		/* Exit the game loop. */
		return false;
	}

	/* Clear input states. */
	//set_vm_int("isMouseLeftPressed", 0);
	//set_vm_int("isMouseRightPressed", 0);

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
	case KEY_ESCAPE:
		set_vm_int("isEscapeKeyPressed", 1);
		break;
	case KEY_RETURN:
		set_vm_int("isReturnKeyPressed", 1);
		break;
	case KEY_SPACE:
		set_vm_int("isSpaceKeyPressed", 1);
		break;
	case KEY_TAB:
		set_vm_int("isTabKeyPressed", 1);
		break;
	case KEY_BACKSPACE:
		set_vm_int("isBackspaceKeyPressed", 1);
		break;
	case KEY_DELETE:
		set_vm_int("isDeleteKeyPressed", 1);
		break;
	case KEY_HOME:
		set_vm_int("isHomeKeyPressed", 1);
		break;
	case KEY_END:
		set_vm_int("isEndKeyPressed", 1);
		break;
	case KEY_PAGEUP:
		set_vm_int("isPageupKeyPressed", 1);
		break;
	case KEY_PAGEDOWN:
		set_vm_int("isPagedownKeyPressed", 1);
		break;
	case KEY_SHIFT:
		set_vm_int("isShiftKeyPressed", 1);
		break;
	case KEY_CONTROL:
		set_vm_int("isControlKeyPressed", 1);
		break;
	case KEY_ALT:
		set_vm_int("isAltKeyPressed", 1);
		break;
	case KEY_UP:
		set_vm_int("isUpKeyPressed", 1);
		break;
	case KEY_DOWN:
		set_vm_int("isDownKeyPressed", 1);
		break;
	case KEY_LEFT:
		set_vm_int("isLeftKeyPressed", 1);
		break;
	case KEY_RIGHT:
		set_vm_int("isRightKeyPressed", 1);
		break;
	case KEY_A:
		set_vm_int("isAKeyPressed", 1);
		break;
	case KEY_B:
		set_vm_int("isBKeyPressed", 1);
		break;
	case KEY_C:
		set_vm_int("isCKeyPressed", 1);
		break;
	case KEY_D:
		set_vm_int("isDKeyPressed", 1);
		break;
	case KEY_E:
		set_vm_int("isEKeyPressed", 1);
		break;
	case KEY_F:
		set_vm_int("isFKeyPressed", 1);
		break;
	case KEY_G:
		set_vm_int("isGKeyPressed", 1);
		break;
	case KEY_H:
		set_vm_int("isHKeyPressed", 1);
		break;
	case KEY_I:
		set_vm_int("isIKeyPressed", 1);
		break;
	case KEY_J:
		set_vm_int("isJKeyPressed", 1);
		break;
	case KEY_K:
		set_vm_int("isKKeyPressed", 1);
		break;
	case KEY_L:
		set_vm_int("isLKeyPressed", 1);
		break;
	case KEY_M:
		set_vm_int("isMKeyPressed", 1);
		break;
	case KEY_N:
		set_vm_int("isNKeyPressed", 1);
		break;
	case KEY_O:
		set_vm_int("isOKeyPressed", 1);
		break;
	case KEY_P:
		set_vm_int("isPKeyPressed", 1);
		break;
	case KEY_Q:
		set_vm_int("isQKeyPressed", 1);
		break;
	case KEY_R:
		set_vm_int("isRKeyPressed", 1);
		break;
	case KEY_S:
		set_vm_int("isSKeyPressed", 1);
		break;
	case KEY_T:
		set_vm_int("isTKeyPressed", 1);
		break;
	case KEY_U:
		set_vm_int("isUKeyPressed", 1);
		break;
	case KEY_V:
		set_vm_int("isVKeyPressed", 1);
		break;
	case KEY_W:
		set_vm_int("isWKeyPressed", 1);
		break;
	case KEY_X:
		set_vm_int("isXKeyPressed", 1);
		break;
	case KEY_Y:
		set_vm_int("isYKeyPressed", 1);
		break;
	case KEY_Z:
		set_vm_int("isZKeyPressed", 1);
		break;
	case KEY_1:
		set_vm_int("is1KeyPressed", 1);
		break;
	case KEY_2:
		set_vm_int("is2KeyPressed", 1);
		break;
	case KEY_3:
		set_vm_int("is3KeyPressed", 1);
		break;
	case KEY_4:
		set_vm_int("is4KeyPressed", 1);
		break;
	case KEY_5:
		set_vm_int("is5KeyPressed", 1);
		break;
	case KEY_6:
		set_vm_int("is6KeyPressed", 1);
		break;
	case KEY_7:
		set_vm_int("is7KeyPressed", 1);
		break;
	case KEY_8:
		set_vm_int("is8KeyPressed", 1);
		break;
	case KEY_9:
		set_vm_int("is9KeyPressed", 1);
		break;
	case KEY_0:
		set_vm_int("is0KeyPressed", 1);
		break;
	case KEY_F1:
		set_vm_int("isF1KeyPressed", 1);
		break;
	case KEY_F2:
		set_vm_int("isF2KeyPressed", 1);
		break;
	case KEY_F3:
		set_vm_int("isF3KeyPressed", 1);
		break;
	case KEY_F4:
		set_vm_int("isF4KeyPressed", 1);
		break;
	case KEY_F5:
		set_vm_int("isF5KeyPressed", 1);
		break;
	case KEY_F6:
		set_vm_int("isF6KeyPressed", 1);
		break;
	case KEY_F7:
		set_vm_int("isF7KeyPressed", 1);
		break;
	case KEY_F8:
		set_vm_int("isF8KeyPressed", 1);
		break;
	case KEY_F9:
		set_vm_int("isF9KeyPressed", 1);
		break;
	case KEY_F10:
		set_vm_int("isF10KeyPressed", 1);
		break;
	case KEY_F11:
		set_vm_int("isF11KeyPressed", 1);
		break;
	case KEY_F12:
		set_vm_int("isF12KeyPressed", 1);
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
	case KEY_ESCAPE:
		set_vm_int("isEscapeKeyPressed", 0);
		break;
	case KEY_RETURN:
		set_vm_int("isReturnKeyPressed", 0);
		break;
	case KEY_SPACE:
		set_vm_int("isSpaceKeyPressed", 0);
		break;
	case KEY_TAB:
		set_vm_int("isTabKeyPressed", 0);
		break;
	case KEY_BACKSPACE:
		set_vm_int("isBackspaceKeyPressed", 0);
		break;
	case KEY_DELETE:
		set_vm_int("isDeleteKeyPressed", 0);
		break;
	case KEY_HOME:
		set_vm_int("isHomeKeyPressed", 0);
		break;
	case KEY_END:
		set_vm_int("isEndKeyPressed", 0);
		break;
	case KEY_PAGEUP:
		set_vm_int("isPageupKeyPressed", 0);
		break;
	case KEY_PAGEDOWN:
		set_vm_int("isPagedownKeyPressed", 0);
		break;
	case KEY_SHIFT:
		set_vm_int("isShiftKeyPressed", 0);
		break;
	case KEY_CONTROL:
		set_vm_int("isControlKeyPressed", 0);
		break;
	case KEY_ALT:
		set_vm_int("isAltKeyPressed", 0);
		break;
	case KEY_UP:
		set_vm_int("isUpKeyPressed", 0);
		break;
	case KEY_DOWN:
		set_vm_int("isDownKeyPressed", 0);
		break;
	case KEY_LEFT:
		set_vm_int("isLeftKeyPressed", 0);
		break;
	case KEY_RIGHT:
		set_vm_int("isRightKeyPressed", 0);
		break;
	case KEY_A:
		set_vm_int("isAKeyPressed", 0);
		break;
	case KEY_B:
		set_vm_int("isBKeyPressed", 0);
		break;
	case KEY_C:
		set_vm_int("isCKeyPressed", 0);
		break;
	case KEY_D:
		set_vm_int("isDKeyPressed", 0);
		break;
	case KEY_E:
		set_vm_int("isEKeyPressed", 0);
		break;
	case KEY_F:
		set_vm_int("isFKeyPressed", 0);
		break;
	case KEY_G:
		set_vm_int("isGKeyPressed", 0);
		break;
	case KEY_H:
		set_vm_int("isHKeyPressed", 0);
		break;
	case KEY_I:
		set_vm_int("isIKeyPressed", 0);
		break;
	case KEY_J:
		set_vm_int("isJKeyPressed", 0);
		break;
	case KEY_K:
		set_vm_int("isKKeyPressed", 0);
		break;
	case KEY_L:
		set_vm_int("isLKeyPressed", 0);
		break;
	case KEY_M:
		set_vm_int("isMKeyPressed", 0);
		break;
	case KEY_N:
		set_vm_int("isNKeyPressed", 0);
		break;
	case KEY_O:
		set_vm_int("isOKeyPressed", 0);
		break;
	case KEY_P:
		set_vm_int("isPKeyPressed", 0);
		break;
	case KEY_Q:
		set_vm_int("isQKeyPressed", 0);
		break;
	case KEY_R:
		set_vm_int("isRKeyPressed", 0);
		break;
	case KEY_S:
		set_vm_int("isSKeyPressed", 0);
		break;
	case KEY_T:
		set_vm_int("isTKeyPressed", 0);
		break;
	case KEY_U:
		set_vm_int("isUKeyPressed", 0);
		break;
	case KEY_V:
		set_vm_int("isVKeyPressed", 0);
		break;
	case KEY_W:
		set_vm_int("isWKeyPressed", 0);
		break;
	case KEY_X:
		set_vm_int("isXKeyPressed", 0);
		break;
	case KEY_Y:
		set_vm_int("isYKeyPressed", 0);
		break;
	case KEY_Z:
		set_vm_int("isZKeyPressed", 0);
		break;
	case KEY_1:
		set_vm_int("is1KeyPressed", 0);
		break;
	case KEY_2:
		set_vm_int("is2KeyPressed", 0);
		break;
	case KEY_3:
		set_vm_int("is3KeyPressed", 0);
		break;
	case KEY_4:
		set_vm_int("is4KeyPressed", 0);
		break;
	case KEY_5:
		set_vm_int("is5KeyPressed", 0);
		break;
	case KEY_6:
		set_vm_int("is6KeyPressed", 0);
		break;
	case KEY_7:
		set_vm_int("is7KeyPressed", 0);
		break;
	case KEY_8:
		set_vm_int("is8KeyPressed", 0);
		break;
	case KEY_9:
		set_vm_int("is9KeyPressed", 0);
		break;
	case KEY_0:
		set_vm_int("is0KeyPressed", 0);
		break;
	case KEY_F1:
		set_vm_int("isF1KeyPressed", 0);
		break;
	case KEY_F2:
		set_vm_int("isF2KeyPressed", 0);
		break;
	case KEY_F3:
		set_vm_int("isF3KeyPressed", 0);
		break;
	case KEY_F4:
		set_vm_int("isF4KeyPressed", 0);
		break;
	case KEY_F5:
		set_vm_int("isF5KeyPressed", 0);
		break;
	case KEY_F6:
		set_vm_int("isF6KeyPressed", 0);
		break;
	case KEY_F7:
		set_vm_int("isF7KeyPressed", 0);
		break;
	case KEY_F8:
		set_vm_int("isF8KeyPressed", 0);
		break;
	case KEY_F9:
		set_vm_int("isF9KeyPressed", 0);
		break;
	case KEY_F10:
		set_vm_int("isF10KeyPressed", 0);
		break;
	case KEY_F11:
		set_vm_int("isF11KeyPressed", 0);
		break;
	case KEY_F12:
		set_vm_int("isF12KeyPressed", 0);
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
		set_vm_int("isMouseLeftPressed", 0);
	}
}

void on_event_swipe_down(void)
{
	if (is_running) {
		set_vm_int("isMouseLeftPressed", 0);
	}
}

void on_event_swipe_up(void)
{
	if (is_running) {
		set_vm_int("isMouseLeftPressed", 0);
	}
}
