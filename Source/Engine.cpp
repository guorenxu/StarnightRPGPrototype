#include <d3d9.h>
#include <d3dx9.h>

#include "Engine.h"
#include "Characters.h"
#include "SpriteHandler.h"
#include "Colors.h"
#include "Collection.h"
#include "DXInput.h"
#include "Monsters.h"
#include "Maps.h"
#include "Interface.h"
#include "DXInput.h"
#include "Mouse.h"

extern Map Grasslands;											//Create Map 1
extern Map* location_addr;;										//Remember to set!
extern Monster Squidgee;										//Create Monster Squidgee
extern Window QW;
extern Window HM;
extern Window Menu;
extern Collection Pictures;
extern Rainbow Colors;
extern Mice Mouse;
extern SH Sprite;
extern Character Player;

Engine Game;

Engine::Engine()
{
}