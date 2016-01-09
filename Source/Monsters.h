#ifndef _MONSTER_H
#define _MONSTER_H 1

#include "CString"
#include <cstdlib>
#include <stdio.h>
#include <string>

using namespace std;

class Monster
{
	public:
		Monster(int Type,										//Constructor Function
			int Hp,
			int Mp,
			int Activity,
			int Aggressive,
			char* Name,
			int Number);

		~Monster(){};											//Destructor Function

		void CSet_Texture(LPDIRECT3DTEXTURE9 Texture);			//Load the Texture

		void CDraw();

		void CSpawn();

		void CMove();											//Allows Movement

		void CMove_Lock();										//Returns 1 For Allow, 0 For Disallow

		void CMove_Lock_Sub();

		void CMove_Sub(int Direction);

		void CMove_Sub_Update();

		void CUpdate();											//Updates Position

		void CDamage();

		void CShow_HP();

		void CDie();

		void CReset();

		LPDIRECT3DTEXTURE9 ctexture;							//Monster Image
		int ctype;
		int cHP;
		int cMHP;
		int cMP;
		int cMMP;
		int cactivity;
		int caggressive;
		char* cname;
		int cnumber;
		int cx;
		int cy;
		int cdx;
		int cdy;
		int cbmx;
		int cbmy;

		int calpha;

		int cmove_status;
		int cmove_count_keeper;
		int cmove_direction;

		int cattack_status;
		int cattack_delay;

		int cchar_status;

		int climit;												//Monster Limit

		int clocation;

		int calive;
		int chealth_count;
		int caggro;

		int crespawn_count;

		D3DXVECTOR3 c_hp_position;

		D3DXVECTOR3 cposition;
};

#endif					//93