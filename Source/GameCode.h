#ifndef _GAMECODE_H
#define _GAMECODE_H 1

#include <d3d9.h>
#include <d3dx9.h>
#include <dxerr.h>
#include <dsound.h>
#include <dinput.h>
#include <windows.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#include "dxgraphics.h"
#include "dxaudio.h"
#include "dxinput.h"
#include "Characters.h"
#include "Maps.h"
#include "Monsters.h"
#include "Interface.h"
#include "Collection.h"
#include "Colors.h"
#include "Support.h"
#include "Mouse.h"
#include "Engine.h"
#include "Fonts.h"

#include "SpriteHandler.h"

#define APPTITLE "Starnight"

#define FULLSCREEN 0
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

int Game_Init(HWND);
void Game_Run(HWND);
void Game_End(HWND);

#endif