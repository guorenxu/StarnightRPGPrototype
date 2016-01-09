#include <d3d9.h>
#include <d3dx9.h>

#include "Maps.h"
#include "SpriteHandler.h"
#include "Colors.h"
#include "Characters.h"

extern Rainbow Colors;
extern SH Sprite;
extern Character Player;

extern int Map1A[3][2];

Map Grasslands(8, 8, 1, 1, 1, Map1A);							//Create Map 1

Map* location_addr = &Grasslands;								//Remember to set!

Map::Map(int Size_x, int Size_y, int Start_x, int Start_y, int Number, int Array[3][2])
{
	size_x = Size_x;
	size_y = Size_y;
	number = Number;
	start_x = Start_x;
	start_y = Start_y;

	Monster_Stats[0][0] = Array[0][0];
	Monster_Stats[0][1] = Array[0][1];
	Monster_Stats[1][0] = Array[1][0];
	Monster_Stats[1][1] = Array[1][1];
	Monster_Stats[2][0] = Array[2][0];
	Monster_Stats[2][1] = Array[2][1];
}

void Map::Set_Texture(LPDIRECT3DTEXTURE9 Texture)
{
	texture = Texture;
}

void Map::Draw()
{
	D3DXVECTOR3 position ((float)(-((Player.px * 28) + (Player.py * 28) + Player.bmx) + 290), 
		(float)(-((Player.px * 14) - (Player.py * 14) + Player.bmy) + 124), 0);

	Sprite.SpHd->Draw(texture,
		NULL,
		NULL,
		&position,
		Colors.white);
}					//50