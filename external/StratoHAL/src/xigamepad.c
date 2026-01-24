//* -*- coding: utf-8; tab-width: 8; indent-tabs-mode: t; -*- */

/*
 * Playfield Engine
 * Gamepad HAL for XInput
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
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 */

#include "stratohal/platform.h"
#include "xigamepad.h"

#include <windows.h>
#include <xinput.h>

VOID XInputUpdate(VOID)
{
    XINPUT_STATE state;
    DWORD result;

    result = XInputGetState(0, &state);
    if (result != ERROR_SUCCESS)
        return;

    on_event_analog_input(ANALOG_X1, state.Gamepad.sThumbLX);
    on_event_analog_input(ANALOG_Y1, state.Gamepad.sThumbLY);
    on_event_analog_input(ANALOG_X2, state.Gamepad.sThumbRX);
    on_event_analog_input(ANALOG_Y2, state.Gamepad.sThumbRY);
    on_event_analog_input(ANALOG_L, state.Gamepad.bLeftTrigger);
    on_event_analog_input(ANALOG_R, state.Gamepad.bRightTrigger);

    if (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP)
        on_event_key_press(KEY_GAMEPAD_UP);
    else
        on_event_key_release(KEY_GAMEPAD_UP);

    if (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN)
        on_event_key_press(KEY_GAMEPAD_DOWN);
    else
        on_event_key_release(KEY_GAMEPAD_DOWN);

    if (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT)
        on_event_key_press(KEY_GAMEPAD_LEFT);
    else
        on_event_key_release(KEY_GAMEPAD_LEFT);

    if (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT)
        on_event_key_press(KEY_GAMEPAD_RIGHT);
    else
        on_event_key_release(KEY_GAMEPAD_RIGHT);

    if (state.Gamepad.wButtons & XINPUT_GAMEPAD_A)
        on_event_key_press(KEY_GAMEPAD_A);
    else
        on_event_key_release(KEY_GAMEPAD_A);

    if (state.Gamepad.wButtons & XINPUT_GAMEPAD_B)
        on_event_key_press(KEY_GAMEPAD_B);
    else
        on_event_key_release(KEY_GAMEPAD_B);

    if (state.Gamepad.wButtons & XINPUT_GAMEPAD_X)
        on_event_key_press(KEY_GAMEPAD_X);
    else
        on_event_key_release(KEY_GAMEPAD_X);

    if (state.Gamepad.wButtons & XINPUT_GAMEPAD_Y)
        on_event_key_press(KEY_GAMEPAD_Y);
    else
        on_event_key_release(KEY_GAMEPAD_Y);

    if (state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER)
        on_event_key_press(KEY_GAMEPAD_L);
    else
        on_event_key_release(KEY_GAMEPAD_L);

    if (state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER)
        on_event_key_press(KEY_GAMEPAD_R);
    else
        on_event_key_release(KEY_GAMEPAD_R);
}
