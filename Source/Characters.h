#ifndef _CHARACTERS_H
#define _CHARACTERS_H 1

#include "CString"
#include <cstdlib>
#include <stdio.h>
#include <string>

using namespace std;

class Character
{
	public:

	Character();

	~Character(){};

	int plocation;												//Character Map Location (Number)

	int px;														//Character Coordinates - Initiated
	int py;

	int dx;														//Coordinates For Drawing
	int dy;

	int bx;														//Background Drawing Coordinates
	int by;

	int bmx;													//Movement Change Holders
	int bmy;

	int move_status;											//Movement Lock
	int move_count_keeper;										//Movement Timer
	int move_direction;
	int move_instant_count;

	int attack_status;											//Attack and Movement Lock
	int attack_delay;											//Attack Speed Control

	int char_status;											//Character Sprite Sheet Controller

	int pHP;
	int pMHP;

	int pMP;
	int pMMP;

	int str;													//Strength
	int wis;													//Wisdom
	int dex;													//Dexterity
	int con;													//Constitution

	int attack_power;											//Remember to set!

	int combat_status;											//Combat marker

	char* pname;

	void Movement();												//Movement Engine
	void Movement_Sub(int Direction);								//Movement Engine Subsidiary
	void Movement_Sub_Sub();										//Repeated Code
	void Movement_Sub_Update();

	void Movement_Lock();											//Allows the Edge of Map
	void Movement_Lock_Sub();

	void Attack();

	void Draw_Character();											//Draw Character
	void Clothes();													//Draw Clothes
	void Shoes();													//Draw Shoes
	void Weapon();													//Draw Weapon

	void Combat();
};

#endif