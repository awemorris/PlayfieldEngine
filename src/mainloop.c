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
		set_vm_int("isKeyEscapePressed", 1);
		break;
	case KEY_RETURN:
		set_vm_int("isKeyReturnPressed", 1);
		break;
	case KEY_SPACE:
		set_vm_int("isKeySpacePressed", 1);
		break;
	case KEY_TAB:
		set_vm_int("isKeyTabPressed", 1);
		break;
	case KEY_BACKSPACE:
		set_vm_int("isKeyBackspacePressed", 1);
		break;
	case KEY_DELETE:
		set_vm_int("isKeyDeletePressed", 1);
		break;
	case KEY_HOME:
		set_vm_int("isKeyHomePressed", 1);
		break;
	case KEY_END:
		set_vm_int("isKeyEndPressed", 1);
		break;
	case KEY_PAGEUP:
		set_vm_int("isKeyPageupPressed", 1);
		break;
	case KEY_PAGEDOWN:
		set_vm_int("isKeyPagedownPressed", 1);
		break;
	case KEY_SHIFT:
		set_vm_int("isKeyShiftPressed", 1);
		break;
	case KEY_CONTROL:
		set_vm_int("isKeyControlPressed", 1);
		break;
	case KEY_ALT:
		set_vm_int("isKeyAltPressed", 1);
		break;
	case KEY_UP:
		set_vm_int("isKeyUpPressed", 1);
		break;
	case KEY_DOWN:
		set_vm_int("isKeyDownPressed", 1);
		break;
	case KEY_LEFT:
		set_vm_int("isKeyLeftPressed", 1);
		break;
	case KEY_RIGHT:
		set_vm_int("isKeyRightPressed", 1);
		break;
	case KEY_A:
		set_vm_int("isKeyAPressed", 1);
		break;
	case KEY_B:
		set_vm_int("isKeyBPressed", 1);
		break;
	case KEY_C:
		set_vm_int("isKeyCPressed", 1);
		break;
	case KEY_D:
		set_vm_int("isKeyDPressed", 1);
		break;
	case KEY_E:
		set_vm_int("isKeyEPressed", 1);
		break;
	case KEY_F:
		set_vm_int("isKeyFPressed", 1);
		break;
	case KEY_G:
		set_vm_int("isKeyGPressed", 1);
		break;
	case KEY_H:
		set_vm_int("isKeyHPressed", 1);
		break;
	case KEY_I:
		set_vm_int("isKeyIPressed", 1);
		break;
	case KEY_J:
		set_vm_int("isKeyJPressed", 1);
		break;
	case KEY_K:
		set_vm_int("isKeyKPressed", 1);
		break;
	case KEY_L:
		set_vm_int("isKeyLPressed", 1);
		break;
	case KEY_M:
		set_vm_int("isKeyMPressed", 1);
		break;
	case KEY_N:
		set_vm_int("isKeyNPressed", 1);
		break;
	case KEY_O:
		set_vm_int("isKeyOPressed", 1);
		break;
	case KEY_P:
		set_vm_int("isKeyPPressed", 1);
		break;
	case KEY_Q:
		set_vm_int("isKeyQPressed", 1);
		break;
	case KEY_R:
		set_vm_int("isKeyRPressed", 1);
		break;
	case KEY_S:
		set_vm_int("isKeySPressed", 1);
		break;
	case KEY_T:
		set_vm_int("isKeyTPressed", 1);
		break;
	case KEY_U:
		set_vm_int("isKeyUPressed", 1);
		break;
	case KEY_V:
		set_vm_int("isKeyVPressed", 1);
		break;
	case KEY_W:
		set_vm_int("isKeyWPressed", 1);
		break;
	case KEY_X:
		set_vm_int("isKeyXPressed", 1);
		break;
	case KEY_Y:
		set_vm_int("isKeyYPressed", 1);
		break;
	case KEY_Z:
		set_vm_int("isKeyZPressed", 1);
		break;
	case KEY_1:
		set_vm_int("isKey1Pressed", 1);
		break;
	case KEY_2:
		set_vm_int("isKey2Pressed", 1);
		break;
	case KEY_3:
		set_vm_int("isKey3Pressed", 1);
		break;
	case KEY_4:
		set_vm_int("isKey4Pressed", 1);
		break;
	case KEY_5:
		set_vm_int("isKey5Pressed", 1);
		break;
	case KEY_6:
		set_vm_int("isKey6Pressed", 1);
		break;
	case KEY_7:
		set_vm_int("isKey7Pressed", 1);
		break;
	case KEY_8:
		set_vm_int("isKey8Pressed", 1);
		break;
	case KEY_9:
		set_vm_int("isKey9Pressed", 1);
		break;
	case KEY_0:
		set_vm_int("isKey0Pressed", 1);
		break;
	case KEY_F1:
		set_vm_int("isKeyF1Pressed", 1);
		break;
	case KEY_F2:
		set_vm_int("isKeyF2Pressed", 1);
		break;
	case KEY_F3:
		set_vm_int("isKeyF3Pressed", 1);
		break;
	case KEY_F4:
		set_vm_int("isKeyF4Pressed", 1);
		break;
	case KEY_F5:
		set_vm_int("isKeyF5Pressed", 1);
		break;
	case KEY_F6:
		set_vm_int("isKeyF6Pressed", 1);
		break;
	case KEY_F7:
		set_vm_int("isKeyF7Pressed", 1);
		break;
	case KEY_F8:
		set_vm_int("isKeyF8Pressed", 1);
		break;
	case KEY_F9:
		set_vm_int("isKeyF9Pressed", 1);
		break;
	case KEY_F10:
		set_vm_int("isKeyF10Pressed", 1);
		break;
	case KEY_F11:
		set_vm_int("isKeyF11Pressed", 1);
		break;
	case KEY_F12:
		set_vm_int("isKeyF12Pressed", 1);
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
		set_vm_int("isKeyEscapePressed", 0);
		break;
	case KEY_RETURN:
		set_vm_int("isKeyReturnPressed", 0);
		break;
	case KEY_SPACE:
		set_vm_int("isKeySpacePressed", 0);
		break;
	case KEY_TAB:
		set_vm_int("isKeyTabPressed", 0);
		break;
	case KEY_BACKSPACE:
		set_vm_int("isKeyBackspacePressed", 0);
		break;
	case KEY_DELETE:
		set_vm_int("isKeyDeletePressed", 0);
		break;
	case KEY_HOME:
		set_vm_int("isKeyHomePressed", 0);
		break;
	case KEY_END:
		set_vm_int("isKeyEndPressed", 0);
		break;
	case KEY_PAGEUP:
		set_vm_int("isKeyPageupPressed", 0);
		break;
	case KEY_PAGEDOWN:
		set_vm_int("isKeyPagedownPressed", 0);
		break;
	case KEY_SHIFT:
		set_vm_int("isKeyShiftPressed", 0);
		break;
	case KEY_CONTROL:
		set_vm_int("isKeyControlPressed", 0);
		break;
	case KEY_ALT:
		set_vm_int("isKeyAltPressed", 0);
		break;
	case KEY_UP:
		set_vm_int("isKeyUpPressed", 0);
		break;
	case KEY_DOWN:
		set_vm_int("isKeyDownPressed", 0);
		break;
	case KEY_LEFT:
		set_vm_int("isKeyLeftPressed", 0);
		break;
	case KEY_RIGHT:
		set_vm_int("isKeyRightPressed", 0);
		break;
	case KEY_A:
		set_vm_int("isKeyAPressed", 0);
		break;
	case KEY_B:
		set_vm_int("isKeyBPressed", 0);
		break;
	case KEY_C:
		set_vm_int("isKeyCPressed", 0);
		break;
	case KEY_D:
		set_vm_int("isKeyDPressed", 0);
		break;
	case KEY_E:
		set_vm_int("isKeyEPressed", 0);
		break;
	case KEY_F:
		set_vm_int("isKeyFPressed", 0);
		break;
	case KEY_G:
		set_vm_int("isKeyGPressed", 0);
		break;
	case KEY_H:
		set_vm_int("isKeyHPressed", 0);
		break;
	case KEY_I:
		set_vm_int("isKeyIPressed", 0);
		break;
	case KEY_J:
		set_vm_int("isKeyJPressed", 0);
		break;
	case KEY_K:
		set_vm_int("isKeyKPressed", 0);
		break;
	case KEY_L:
		set_vm_int("isKeyLPressed", 0);
		break;
	case KEY_M:
		set_vm_int("isKeyMPressed", 0);
		break;
	case KEY_N:
		set_vm_int("isKeyNPressed", 0);
		break;
	case KEY_O:
		set_vm_int("isKeyOPressed", 0);
		break;
	case KEY_P:
		set_vm_int("isKeyPPressed", 0);
		break;
	case KEY_Q:
		set_vm_int("isKeyQPressed", 0);
		break;
	case KEY_R:
		set_vm_int("isKeyRPressed", 0);
		break;
	case KEY_S:
		set_vm_int("isKeySPressed", 0);
		break;
	case KEY_T:
		set_vm_int("isKeyTPressed", 0);
		break;
	case KEY_U:
		set_vm_int("isKeyUPressed", 0);
		break;
	case KEY_V:
		set_vm_int("isKeyVPressed", 0);
		break;
	case KEY_W:
		set_vm_int("isKeyWPressed", 0);
		break;
	case KEY_X:
		set_vm_int("isKeyXPressed", 0);
		break;
	case KEY_Y:
		set_vm_int("isKeyYPressed", 0);
		break;
	case KEY_Z:
		set_vm_int("isKeyZPressed", 0);
		break;
	case KEY_1:
		set_vm_int("isKey1Pressed", 0);
		break;
	case KEY_2:
		set_vm_int("isKey2Pressed", 0);
		break;
	case KEY_3:
		set_vm_int("isKey3Pressed", 0);
		break;
	case KEY_4:
		set_vm_int("isKey4Pressed", 0);
		break;
	case KEY_5:
		set_vm_int("isKey5Pressed", 0);
		break;
	case KEY_6:
		set_vm_int("isKey6Pressed", 0);
		break;
	case KEY_7:
		set_vm_int("isKey7Pressed", 0);
		break;
	case KEY_8:
		set_vm_int("isKey8Pressed", 0);
		break;
	case KEY_9:
		set_vm_int("isKey9Pressed", 0);
		break;
	case KEY_0:
		set_vm_int("isKey0Pressed", 0);
		break;
	case KEY_F1:
		set_vm_int("isKeyF1Pressed", 0);
		break;
	case KEY_F2:
		set_vm_int("isKeyF2Pressed", 0);
		break;
	case KEY_F3:
		set_vm_int("isKeyF3Pressed", 0);
		break;
	case KEY_F4:
		set_vm_int("isKeyF4Pressed", 0);
		break;
	case KEY_F5:
		set_vm_int("isKeyF5Pressed", 0);
		break;
	case KEY_F6:
		set_vm_int("isKeyF6Pressed", 0);
		break;
	case KEY_F7:
		set_vm_int("isKeyF7Pressed", 0);
		break;
	case KEY_F8:
		set_vm_int("isKeyF8Pressed", 0);
		break;
	case KEY_F9:
		set_vm_int("isKeyF9Pressed", 0);
		break;
	case KEY_F10:
		set_vm_int("isKeyF10Pressed", 0);
		break;
	case KEY_F11:
		set_vm_int("isKeyF11Pressed", 0);
		break;
	case KEY_F12:
		set_vm_int("isKeyF12Pressed", 0);
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
