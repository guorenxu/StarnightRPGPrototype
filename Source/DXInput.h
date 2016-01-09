#ifndef _DXINPUT_H
#define _DXINPUT_H 1

#include <dinput.h>

int Init_DirectInput(HWND);
int Init_Keyboard(HWND);
void Poll_Keyboard();
int Key_Down(int);
void Kill_Keyboard();
void Poll_Mouse();
int Init_Mouse(HWND);
int Mouse_Button(int);
int Mouse_X();
int Mouse_Y();
int BMouse_X();
int BMouse_Y();
void Update_BM();
void Kill_Mouse();

extern LPDIRECTINPUT8 dinput;
extern LPDIRECTINPUTDEVICE8 dimouse;
extern LPDIRECTINPUTDEVICE8 dikeyboard;
extern DIMOUSESTATE mouse_state;
extern DIMOUSESTATE b_mouse_state;

#endif