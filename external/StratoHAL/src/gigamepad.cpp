//* -*- coding: utf-8; tab-width: 4; indent-tabs-mode: t; -*- */

/*
 * Copyright (c) 2025, Awe Morris. All rights reserved.
 */

/*
 * Gamepad Input (GameInput on GDK)
 */

extern "C" {
#include <stratohal/platform.h>
#include "gigamepad.h"
};

#include <windows.h>
#include <GameInput.h>

static IGameInput *g_gameInput = NULL;

VOID GameInputInitialize(VOID)
{
    if (g_gameInput)
	return;

    HRESULT hr = GameInputCreate(&g_gameInput);
    if (FAILED(hr))
	g_gameInput = NULL;
}

VOID GameInputCleanup(VOID)
{
    if (g_gameInput) {
	g_gameInput->Release();
	g_gameInput = NULL;
    }
}

static inline float clampf(float v, float lo, float hi)
{
    if (v < lo)
	return lo;
    if (v > hi)
	return hi;
    return v;
}

static inline SHORT stick_to_i16(float v)
{
    v = clampf(v, -1.0f, 1.0f);
    return (SHORT)(v * 32767.0f);
}

static inline BYTE trigger_to_u8(float v)
{
    v = clampf(v, 0.0f, 1.0f);
    return (BYTE)(v * 255.0f + 0.5f);
}

VOID GameInputUpdate(VOID)
{
    if (!g_gameInput)
	return;

    IGameInputReading *reading = NULL;
    HRESULT hr = g_gameInput->GetCurrentReading(GameInputKindGamepad, NULL, &reading);
    if (FAILED(hr) || !reading)
	return;

    GameInputGamepadState pad;
    ZeroMemory(&pad, sizeof(pad));

    hr = reading->GetGamepadState(&pad);
    reading->Release();
    if (FAILED(hr))
	return;

    /* Analog */
    on_event_analog_input(ANALOG_X1, stick_to_i16(pad.leftThumbstickX));
    on_event_analog_input(ANALOG_Y1, stick_to_i16(pad.leftThumbstickY));
    on_event_analog_input(ANALOG_X2, stick_to_i16(pad.rightThumbstickX));
    on_event_analog_input(ANALOG_Y2, stick_to_i16(pad.rightThumbstickY));
    on_event_analog_input(ANALOG_L,  trigger_to_u8(pad.leftTrigger));
    on_event_analog_input(ANALOG_R,  trigger_to_u8(pad.rightTrigger));

    /* Buttons (GameInputGamepadButtons bitmask) */
    if (pad.buttons & GameInputGamepadDPadUp)
	on_event_key_press(KEY_GAMEPAD_UP);
    else
	on_event_key_release(KEY_GAMEPAD_UP);

    if (pad.buttons & GameInputGamepadDPadDown)
	on_event_key_press(KEY_GAMEPAD_DOWN);
    else
	on_event_key_release(KEY_GAMEPAD_DOWN);

    if (pad.buttons & GameInputGamepadDPadLeft)
	on_event_key_press(KEY_GAMEPAD_LEFT);
    else
	on_event_key_release(KEY_GAMEPAD_LEFT);

    if (pad.buttons & GameInputGamepadDPadRight)
	on_event_key_press(KEY_GAMEPAD_RIGHT);
    else
	on_event_key_release(KEY_GAMEPAD_RIGHT);

    if (pad.buttons & GameInputGamepadA)
	on_event_key_press(KEY_GAMEPAD_A);
    else
	on_event_key_release(KEY_GAMEPAD_A);

    if (pad.buttons & GameInputGamepadB)
	on_event_key_press(KEY_GAMEPAD_B);
    else
	on_event_key_release(KEY_GAMEPAD_B);

    if (pad.buttons & GameInputGamepadX)
	on_event_key_press(KEY_GAMEPAD_X);
    else
	on_event_key_release(KEY_GAMEPAD_X);

    if (pad.buttons & GameInputGamepadY)
	on_event_key_press(KEY_GAMEPAD_Y);
    else
	on_event_key_release(KEY_GAMEPAD_Y);

    if (pad.buttons & GameInputGamepadLeftShoulder)
	on_event_key_press(KEY_GAMEPAD_L);
    else
	on_event_key_release(KEY_GAMEPAD_L);

    if (pad.buttons & GameInputGamepadRightShoulder)
	on_event_key_press(KEY_GAMEPAD_R);
    else
	on_event_key_release(KEY_GAMEPAD_R);
}
