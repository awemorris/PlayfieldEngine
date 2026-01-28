//* -*- coding: utf-8; tab-width: 8; indent-tabs-mode: t; -*- */

/*
 * StratoHAL
 * Gamepad HAL for DirectInput
 */

/*-
 * SPDX-License-Identifier: Zlib
 *
 * Copyright (c) 2025-2026 Awe Morris
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

extern "C" {
#include <stratohal/platform.h>
#include "digamepad.h"
};

#include <windows.h>

#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>

static LPDIRECTINPUT8 pDI;
static LPDIRECTINPUTDEVICE8W pGamepad;
static DIDEVCAPS diDevCaps;

static BOOL CALLBACK EnumGamepadCallback(const DIDEVICEINSTANCE* pdidInstance, VOID* pContext);
static BOOL CALLBACK EnumAxesCallback(const DIDEVICEOBJECTINSTANCE* pdidoi, VOID *pContext);

BOOL
DInputInitialize(HINSTANCE hInst, HWND hWnd)
{
    HRESULT hr;

    hr = DirectInput8Create(hInst, DIRECTINPUT_VERSION, IID_IDirectInput8, (LPVOID*)&pDI, NULL);
    if (FAILED(hr))
    {
        log_info("DirectInput initialize error.");
        return FALSE;
    }

    hr = pDI->EnumDevices(DI8DEVCLASS_GAMECTRL, EnumGamepadCallback, NULL, DIEDFL_ATTACHEDONLY);
    if (FAILED(hr))
    {
        log_info("DirectInput enumeration error.");
        return FALSE;
    }
    if (pGamepad == NULL)
    {
	// No gamepad.
        return FALSE;
    }

    hr = pGamepad->SetDataFormat(&c_dfDIJoystick2);
    if (FAILED(hr))
    {
        log_info("DirectInput gamepad data format error.");
        return FALSE;
    }

    hr = pGamepad->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
    if (FAILED(hr))
    {
        log_info("DirectInput cooperative level error.");
        return FALSE;
    }

    diDevCaps.dwSize = sizeof(DIDEVCAPS);
    hr = pGamepad->GetCapabilities(&diDevCaps);
    if (FAILED(hr))
    {
        log_info("DirectInput capabilities error.");
        return FALSE;
    }

    hr = pGamepad->EnumObjects(EnumAxesCallback, (VOID*)hWnd, DIDFT_AXIS);
    if (FAILED(hr))
    {
        log_info("DirectInput axis error.");
	return FALSE;
    }

    return TRUE;
}

static BOOL CALLBACK
EnumGamepadCallback(
    const DIDEVICEINSTANCE *pdidInstance,
    VOID *pContext)
{
    HRESULT hr;

    hr = pDI->CreateDevice(pdidInstance->guidInstance, &pGamepad, NULL);
    if (FAILED(hr))
        return DIENUM_CONTINUE; // Unplugged?

    // Use the first one.
    return DIENUM_STOP;
}

static BOOL CALLBACK
EnumAxesCallback(
    const DIDEVICEOBJECTINSTANCE* pdidoi,
    VOID *pContext)
{
    DIPROPRANGE diprg; 
    diprg.diph.dwSize       = sizeof(DIPROPRANGE); 
    diprg.diph.dwHeaderSize = sizeof(DIPROPHEADER); 
    diprg.diph.dwHow        = DIPH_BYOFFSET; 
    diprg.diph.dwObj        = pdidoi->dwOfs;
    diprg.lMin              = -32768;
    diprg.lMax              = +32767;
    
    if (FAILED(pGamepad->SetProperty(DIPROP_RANGE, &diprg.diph)))
        return DIENUM_STOP;

    return DIENUM_CONTINUE;
}

VOID
DInputCleanup(VOID)
{
    if (pGamepad != NULL)
    {
        pGamepad->Unacquire();
        pGamepad->Release();
        pGamepad = NULL;
    }

    if (pDI)
    {
        pDI->Release();
        pDI = NULL;
    }
}

VOID DInputUpdate(VOID)
{
    HRESULT hr;
    DIJOYSTATE2 js;

    if (pGamepad == NULL)
        return;

    pGamepad->Acquire();

    do {
        hr = pGamepad->Poll();
        if (FAILED(hr))
            return;

        hr = pGamepad->GetDeviceState(sizeof(DIJOYSTATE2), &js);
        if (hr == DIERR_INPUTLOST)
        {
            hr = pGamepad->Acquire();
            if (FAILED(hr))
                return;
        }
    } while (hr == DIERR_INPUTLOST);

    on_event_analog_input(ANALOG_X1, js.lX);
    on_event_analog_input(ANALOG_Y1, js.lY);
    on_event_analog_input(ANALOG_X2, js.lRx);
    on_event_analog_input(ANALOG_Y2, js.lRy);
    on_event_analog_input(ANALOG_L, js.lZ);
    on_event_analog_input(ANALOG_L, js.lRz);

    if (js.rgdwPOV[0] == 0)
    {
        on_event_key_press(KEY_GAMEPAD_UP);
        on_event_key_release(KEY_GAMEPAD_RIGHT);
        on_event_key_release(KEY_GAMEPAD_DOWN);
        on_event_key_release(KEY_GAMEPAD_LEFT);
    }
    else if (js.rgdwPOV[0] == 4500)
    {
        on_event_key_press(KEY_GAMEPAD_UP);
        on_event_key_press(KEY_GAMEPAD_RIGHT);
        on_event_key_release(KEY_GAMEPAD_DOWN);
        on_event_key_release(KEY_GAMEPAD_LEFT);
    }
    else if (js.rgdwPOV[0] == 9000)
    {
        on_event_key_release(KEY_GAMEPAD_UP);
        on_event_key_press(KEY_GAMEPAD_RIGHT);
        on_event_key_release(KEY_GAMEPAD_DOWN);
        on_event_key_release(KEY_GAMEPAD_LEFT);
    }
    else if (js.rgdwPOV[0] == 13500)
    {
        on_event_key_release(KEY_GAMEPAD_UP);
        on_event_key_press(KEY_GAMEPAD_RIGHT);
        on_event_key_press(KEY_GAMEPAD_DOWN);
        on_event_key_release(KEY_GAMEPAD_LEFT);
    }
    else if (js.rgdwPOV[0] == 18000)
    {
        on_event_key_release(KEY_GAMEPAD_UP);
        on_event_key_release(KEY_GAMEPAD_RIGHT);
        on_event_key_press(KEY_GAMEPAD_DOWN);
        on_event_key_release(KEY_GAMEPAD_LEFT);
    }
    else if (js.rgdwPOV[0] == 22500)
    {
        on_event_key_release(KEY_GAMEPAD_UP);
        on_event_key_release(KEY_GAMEPAD_RIGHT);
        on_event_key_press(KEY_GAMEPAD_DOWN);
        on_event_key_press(KEY_GAMEPAD_LEFT);
    }
    else if (js.rgdwPOV[0] == 27000)
    {
        on_event_key_release(KEY_GAMEPAD_UP);
        on_event_key_release(KEY_GAMEPAD_RIGHT);
        on_event_key_release(KEY_GAMEPAD_DOWN);
        on_event_key_press(KEY_GAMEPAD_LEFT);
    }
    else if (js.rgdwPOV[0] == 31500)
    {
        on_event_key_press(KEY_GAMEPAD_UP);
        on_event_key_release(KEY_GAMEPAD_RIGHT);
        on_event_key_release(KEY_GAMEPAD_DOWN);
        on_event_key_press(KEY_GAMEPAD_LEFT);
    }
    else
    {
        on_event_key_release(KEY_GAMEPAD_UP);
        on_event_key_release(KEY_GAMEPAD_RIGHT);
        on_event_key_release(KEY_GAMEPAD_DOWN);
        on_event_key_release(KEY_GAMEPAD_LEFT);
    }

    if (js.rgbButtons[1] & 0x80)
	on_event_key_press(KEY_GAMEPAD_A);
    else
	on_event_key_release(KEY_GAMEPAD_A);

    if (js.rgbButtons[2] & 0x80)
	on_event_key_press(KEY_GAMEPAD_B);
    else
	on_event_key_release(KEY_GAMEPAD_B);

    if (js.rgbButtons[0] & 0x80)
	on_event_key_press(KEY_GAMEPAD_X);
    else
	on_event_key_release(KEY_GAMEPAD_X);

    if (js.rgbButtons[3] & 0x80)
	on_event_key_press(KEY_GAMEPAD_Y);
    else
	on_event_key_release(KEY_GAMEPAD_Y);

    if (js.rgbButtons[4] & 0x80)
	on_event_key_press(KEY_GAMEPAD_L);
    else
	on_event_key_release(KEY_GAMEPAD_L);

    if (js.rgbButtons[5] & 0x80)
	on_event_key_press(KEY_GAMEPAD_R);
    else
	on_event_key_release(KEY_GAMEPAD_R);
}
