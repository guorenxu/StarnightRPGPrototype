#ifndef _MAPS_H
#define _MAPS_H 1

#include "CString"
#include <cstdlib>
#include <stdio.h>
#include <string>

using namespace std;

class Map
{
	public:
		Map(int Size_x,											//Constructor Function
			int Size_y,
			int Start_x,
			int Start_y,
			int Number,
			int Array[3][2]);

		~Map(){};												//Destructor Function

		void Set_Texture(LPDIRECT3DTEXTURE9 Texture);			//Load the Texture

		void Draw();											//Draw the Map

		LPDIRECT3DTEXTURE9 texture;								//Map Image
		int size_x;												//X Size of Map
		int size_y;												//Y Size of Map
		int start_x;											//Initial X
		int start_y;											//Initial Y
		int number;												//Number Code of Map

		int Monster_Stats[3][2];								//Respawn Times / Max Monsters
};

#endif				//37