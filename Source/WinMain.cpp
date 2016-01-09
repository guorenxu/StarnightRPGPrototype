#include <d3d9.h>
#include <d3dx9.h>
#include <time.h>
#include <stdio.h>
#include "GameCode.h"

int Game_Init(HWND hwnd);

LRESULT WINAPI WinProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
    switch( msg )
    {
        case WM_DESTROY:
            if (d3ddev != NULL) d3ddev->Release();
            if (d3d != NULL) d3d->Release();

            if (dsound != NULL) delete dsound;

            if (dinput != NULL) dinput->Release();
            Kill_Keyboard();
            Kill_Mouse();

            Game_End(hWnd);

            PostQuitMessage(0);
            return 0;
    }
    return DefWindowProc( hWnd, msg, wParam, lParam );
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEX wc;
    wc.cbSize = sizeof(WNDCLASSEX); 

    wc.style         = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc   = (WNDPROC)WinProc;
    wc.cbClsExtra	 = 0;
    wc.cbWndExtra	 = 0;
    wc.hInstance     = hInstance;
    wc.hIcon         = NULL;
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wc.lpszMenuName  = NULL;
    wc.lpszClassName = APPTITLE;
    wc.hIconSm       = NULL;

    return RegisterClassEx(&wc);
}

int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR     lpCmdLine,
                   int       nCmdShow)
{
	MSG msg;
    HWND hWnd;

	MyRegisterClass(hInstance);

    DWORD style;
    if (FULLSCREEN)
        style = WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP;
    else
        style = WS_OVERLAPPED;

    hWnd = CreateWindow(
       APPTITLE,
       APPTITLE,
       style,
       CW_USEDEFAULT,
       CW_USEDEFAULT, 
       SCREEN_WIDTH,     
       SCREEN_HEIGHT,     
       NULL,            
       NULL,         
       hInstance,       
       NULL);           

    if (!hWnd)
      return FALSE;

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);
	
    Init_Direct3D(hWnd, SCREEN_WIDTH, SCREEN_HEIGHT, FULLSCREEN);

    Init_DirectSound(hWnd);

    Init_DirectInput(hWnd);
    
	Game_Init(hWnd);

    int done = 0;
	while (!done)
    {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) 
	    {
            if (msg.message == WM_QUIT)
                done = 1;

		    TranslateMessage(&msg);
		    DispatchMessage(&msg);
	    }
        else
            Game_Run(hWnd);
    }

	return msg.wParam;
}