#ifndef _COLLECTION_H
#define _COLLECTION_H 1

#include "CString"
#include <cstdlib>
#include <stdio.h>
#include <string>

using namespace std;

class Collection
{
	public:

	LPDIRECT3DSURFACE9 back;										//Secondary Surface

	LPDIRECT3DTEXTURE9 IF;											//Interface Blocker
	LPDIRECT3DTEXTURE9 character;									//Character Sprite Sheet
	LPDIRECT3DTEXTURE9 clothes;										//Clothes Sprite Sheet
	LPDIRECT3DTEXTURE9 shoes;										//Shoes Sprite Sheet
	LPDIRECT3DTEXTURE9 weapon;										//Weapon Sprite Sheet

	LPDIRECT3DTEXTURE9 grassland;									//Background Image
	LPDIRECT3DTEXTURE9 objects;										//Background Objects

	LPDIRECT3DTEXTURE9 HP_in;
	LPDIRECT3DTEXTURE9 HP_out;

	LPDIRECT3DTEXTURE9 HM_window_in;
	LPDIRECT3DTEXTURE9 HM_window_out;

	LPDIRECT3DTEXTURE9 HP_bar_in;
	LPDIRECT3DTEXTURE9 HP_bar_out;

	LPDIRECT3DTEXTURE9 MP_bar_in;
	LPDIRECT3DTEXTURE9 MP_bar_out;

	LPDIRECT3DTEXTURE9 cursor1;

	LPDIRECT3DTEXTURE9 quit_window_out;
	LPDIRECT3DTEXTURE9 quit_window_in;

	LPDIRECT3DTEXTURE9 stats_window_in;
	LPDIRECT3DTEXTURE9 stats_window_out;
	LPDIRECT3DTEXTURE9 stats_window_content;

	LPDIRECT3DTEXTURE9 main_window_in;
	LPDIRECT3DTEXTURE9 main_window_out;

	LPDIRECT3DTEXTURE9 main_button_quit;
	LPDIRECT3DTEXTURE9 main_button_HM;

	~Collection(){}
};

#endif