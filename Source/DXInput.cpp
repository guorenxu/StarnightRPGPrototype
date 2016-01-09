#include "dxinput.h"

#define BUTTON_DOWN(obj, button) (obj.rgbButtons[button] & 0x80)

LPDIRECTINPUT8 dinput;
LPDIRECTINPUTDEVICE8 dimouse;
LPDIRECTINPUTDEVICE8 dikeyboard;
DIMOUSESTATE mouse_state;
DIMOUSESTATE b_mouse_state;

char keys[256];

int Init_DirectInput(HWND hwnd)
{
    HRESULT result = DirectInput8Create(
        GetModuleHandle(NULL), 
        DIRECTINPUT_VERSION, 
        IID_IDirectInput8,
        (void**)&dinput,
        NULL);

    result = dinput->CreateDevice(GUID_SysMouse, &dimouse, NULL);

    result = dinput->CreateDevice(GUID_SysKeyboard, &dikeyboard, NULL);

    return 1;
}


int Init_Mouse(HWND hwnd)
{
    HRESULT result = dimouse->SetDataFormat(&c_dfDIMouse);

    result = dimouse->SetCooperativeLevel(hwnd, DISCL_EXCLUSIVE | DISCL_FOREGROUND);

    result = dimouse->Acquire();

    return 1;
}

int Mouse_X()
{
    return mouse_state.lX;
}

int Mouse_Y()
{
    return mouse_state.lY;
}

int BMouse_Y()
{
	return b_mouse_state.lY;
}

int BMouse_X()
{
	return b_mouse_state.lX;
}

void Update_BM()
{
	if (b_mouse_state.lX + mouse_state.lX > 800)
	{
		mouse_state.lX = 800 - b_mouse_state.lX;
	}

	if (b_mouse_state.lX + mouse_state.lX < 0)
	{
		mouse_state.lX = -(b_mouse_state.lX);
	}

	if (b_mouse_state.lY + mouse_state.lY > 600)
	{
		mouse_state.lY = 600 - b_mouse_state.lY;
	}

	if (b_mouse_state.lY + mouse_state.lY < 0)
	{
		mouse_state.lY = -(b_mouse_state.lY);
	}

	b_mouse_state.lX = b_mouse_state.lX + mouse_state.lX;
	b_mouse_state.lY = b_mouse_state.lY + mouse_state.lY;
}

int Mouse_Button(int button)
{
    return BUTTON_DOWN(mouse_state, button);
}

void Poll_Mouse()
{
    dimouse->GetDeviceState(sizeof(mouse_state), (LPVOID)&mouse_state);
}

void Kill_Mouse()
{
    if (dimouse != NULL)
    {
        dimouse->Unacquire();
        dimouse->Release();
        dimouse = NULL;
    }
}

int Init_Keyboard(HWND hwnd)
{
    HRESULT result = dikeyboard->SetDataFormat(&c_dfDIKeyboard);

    result = dikeyboard->SetCooperativeLevel(hwnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
    if (result != DI_OK)
        return 0;

    result = dikeyboard->Acquire();
    if (result != DI_OK)
        return 0;

    return 1;
}

void Poll_Keyboard()
{
    dikeyboard->GetDeviceState(sizeof(keys), (LPVOID)&keys);
}

int Key_Down(int key)
{
    return (keys[key] & 0x80);
}

void Kill_Keyboard()
{
    if (dikeyboard != NULL)
    {
        dikeyboard->Unacquire();
        dikeyboard->Release();
        dikeyboard = NULL;
    }
}