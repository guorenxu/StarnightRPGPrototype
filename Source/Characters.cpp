#include <d3d9.h>
#include <d3dx9.h>

#include "Characters.h"
#include "SpriteHandler.h"
#include "Colors.h"
#include "Collection.h"
#include "DXInput.h"
#include "Monsters.h"
#include "Maps.h"
#include "Engine.h"

extern SH Sprite; 
extern Rainbow Colors;
extern Collection Pictures;

extern short int MB1[8][8];
extern Monster* MB1x[8][8];

extern Map* location_addr;

Character Player;

Character::Character()
{
	plocation = 1;												//Character Map Location (Number)

	px = 1;														//Character Coordinates - Initiated
	py = 1;

	dx = 1;														//Coordinates For Drawing
	dy = 1;

	bx = 0;														//Background Drawing Coordinates
	by = 0;

	bmx = 0;													//Movement Change Holders
	bmy = 0;

	move_status = 0;											//Movement Lock
	move_count_keeper = 0;										//Movement Timer
	move_direction = 2;
	move_instant_count = 0;

	attack_status = 0;											//Attack and Movement Lock
	attack_delay = 0;											//Attack Speed Control

	char_status = 1;											//Character Sprite Sheet Controller

	pHP = 100;
	pMHP = 100;

	pMP = 100;
	pMMP = 100;

	str = 1;													//Set stats to 1
	dex = 1;
	con = 1;
	wis = 1;

	attack_power = 30;											//Remember to set!

	combat_status = 0;											//Combat marker
}

void Character::Draw_Character()
{
	D3DXVECTOR3 position ((float)375, (float)205 + 50, 0);

	if (char_status == 1)
	{
		RECT rect;
		rect.top = 0;
		rect.left = 0;
		rect.bottom = 50;
		rect.right = 50;

		Sprite.SpHd->Draw(Pictures.character,
			&rect,
			NULL,
			&position,
			Colors.white);
	}

	if (char_status == 2)
	{
		RECT rect;
		rect.top = 0;
		rect.left = 50;
		rect.bottom = 50;
		rect.right = 100;

		Sprite.SpHd->Draw(Pictures.character,
			&rect,
			NULL,
			&position,
			Colors.white);
	}

	if (char_status == 3)
	{
		RECT rect;
		rect.top = 0;
		rect.left = 100;
		rect.bottom = 50;
		rect.right = 150;

		Sprite.SpHd->Draw(Pictures.character,
			&rect,
			NULL,
			&position,
			Colors.white);
	}

	if (char_status == 4)
	{
		RECT rect;
		rect.top = 0;
		rect.left = 150;
		rect.bottom = 50;
		rect.right = 200;

		Sprite.SpHd->Draw(Pictures.character,
			&rect,
			NULL,
			&position,
			Colors.white);
	}

	if (char_status == 11)
	{
		RECT rect;
		rect.top = 50;
		rect.left = 0;
		rect.bottom = 100;
		rect.right = 50;

		Sprite.SpHd->Draw(Pictures.character,
			&rect,
			NULL,
			&position,
			Colors.white);
	}

	if (char_status == 21)
	{
		RECT rect;
		rect.top = 50;
		rect.left = 50;
		rect.bottom = 100;
		rect.right = 100;

		Sprite.SpHd->Draw(Pictures.character,
			&rect,
			NULL,
			&position,
			Colors.white);
	}

	if (char_status == 31)
	{
		RECT rect;
		rect.top = 50;
		rect.left = 100;
		rect.bottom = 100;
		rect.right = 150;

		Sprite.SpHd->Draw(Pictures.character,
			&rect,
			NULL,
			&position,
			Colors.white);
	}

	if (char_status == 41)
	{
		RECT rect;
		rect.top = 50;
		rect.left = 150;
		rect.bottom = 100;
		rect.right = 200;

		Sprite.SpHd->Draw(Pictures.character,
			&rect,
			NULL,
			&position,
			Colors.white);
	}

	if (char_status == 111)
	{
		RECT rect;
		rect.top = 100;
		rect.left = 0;
		rect.bottom = 150;
		rect.right = 50;

		Sprite.SpHd->Draw(Pictures.character,
			&rect,
			NULL,
			&position,
			Colors.white);
	}

	if (char_status == 211)
	{
		RECT rect;
		rect.top = 100;
		rect.left = 50;
		rect.bottom = 150;
		rect.right = 100;

		Sprite.SpHd->Draw(Pictures.character,
			&rect,
			NULL,
			&position,
			Colors.white);
	}

	if (char_status == 311)
	{
		RECT rect;
		rect.top = 100;
		rect.left = 100;
		rect.bottom = 150;
		rect.right = 150;

		Sprite.SpHd->Draw(Pictures.character,
			&rect,
			NULL,
			&position,
			Colors.white);
	}

	if (char_status == 411)
	{
		RECT rect;
		rect.top = 100;
		rect.left = 150;
		rect.bottom = 150;
		rect.right = 200;

		Sprite.SpHd->Draw(Pictures.character,
			&rect,
			NULL,
			&position,
			Colors.white);
	}
}

void Character::Clothes()
{
	D3DXVECTOR3 position ((float)375, (float)205, 0);
}

void Character::Shoes()
{
	D3DXVECTOR3 position ((float)375, (float)205, 0);
}

void Character::Weapon()
{
	D3DXVECTOR3 position ((float)375, (float)205, 0);
}

void Character::Movement()
{	
	if (attack_status != 1)
	{
		if (move_status == 1)
		{
			if (move_direction == 1)
			{
				char_status = 11;
				Movement_Sub(1);
			}

			else if (move_direction == 2)
			{
				char_status = 21;
				Movement_Sub(2);
			}

			else if (move_direction == 3)
			{
				char_status = 31;
				Movement_Sub(3);
			}

			else if (move_direction == 4)
			{
				char_status = 41;
				Movement_Sub(4);
			}
		}

		if (move_status == 0)
		{
			if (move_direction == 1)
			{
				char_status = 1;
			}

			else if (move_direction == 2)
			{
				char_status = 2;
			}

			else if (move_direction == 3)
			{
				char_status = 3;
			}

			else if (move_direction == 4)
			{
				char_status = 4;
			}

			if (Key_Down(DIK_DOWN))
			{
				char_status = 1;

				if (move_direction == 1)
				{
					move_count_keeper++;
				}
				else
				{
					move_count_keeper = 0;
				}

				move_direction = 1;

				if (move_direction == 1)
				{
					move_instant_count++;
				}
			}

			else if (Key_Down(DIK_RIGHT))
			{
				char_status = 2;

				if (move_direction == 2)
				{
					move_count_keeper++;
				}
				else
				{
					move_count_keeper = 0;
				}

				move_direction = 2;

				if (move_direction == 2)
				{
					move_instant_count++;
				}
			}

			else if (Key_Down(DIK_LEFT))
			{
				char_status = 3;

				if (move_direction == 3)
				{
					move_count_keeper++;
				}
				else
				{
					move_count_keeper = 0;
				}

				move_direction = 3;

				if (move_direction == 3)
				{
					move_instant_count++;
				}
			}

			else if (Key_Down(DIK_UP))
			{
				char_status = 4;

				if (move_direction == 4)
				{
					move_count_keeper++;
				}
				else
				{
					move_count_keeper = 0;
				}

				move_direction = 4;

				if (move_direction == 4)
				{
					move_instant_count++;
				}
			}
			else
			{
				move_count_keeper = 0;
				move_instant_count = 0;
			}
		}

		if (move_count_keeper >= 10 && move_status == 0)
		{
			Movement_Lock();
		}

		if (move_instant_count == 2 && move_count_keeper == 2)
		{
			Movement_Lock();
		}
	}
}

void Character::Movement_Sub(int Direction)
{
	if (Direction == 1)
	{
		if (bmx == 0 && bmy == 0)
		{
			py = py - 1;

			Movement_Sub_Update();

			bmx = 28;
			bmy = -14;
		}

		if (bmx > 2)
		{
			bmx = bmx - 2;
		}
		else
		{
			bmx = 0;

			Movement_Sub_Sub();

			dx = px;
		}

		if (bmy < -1)
		{
			bmy = bmy + 1;
		}
		else
		{
			bmy = 0;

			Movement_Sub_Sub();

			dy = py;
		}
	}

	else if (Direction == 2)
	{
		if (bmx == 0 && bmy == 0)
		{
			px = px + 1;

			Movement_Sub_Update();

			bmx = -28;
			bmy = -14;
		}

		if (bmx < -2)
		{
			bmx = bmx + 2;
		}
		else
		{
			bmx = 0;

			Movement_Sub_Sub();

			dx = px;
		}

		if (bmy < -1)
		{
			bmy = bmy + 1;
		}
		else
		{
			bmy = 0;

			Movement_Sub_Sub();

			dy = py;
		}
	}

	else if (Direction == 3)
	{
		if (bmx == 0 && bmy == 0)
		{
			px = px - 1;

			Movement_Sub_Update();

			bmx = 28;
			bmy = 14;
		}

		if (bmx > 2)
		{
			bmx = bmx - 2;
		}
		else
		{
			bmx = 0;

			Movement_Sub_Sub();

			dx = px;
		}

		if (bmy > 1)
		{
			bmy = bmy - 1;
		}
		else
		{
			bmy = 0;

			Movement_Sub_Sub();

			dy = py;
		}
	}

	else if (Direction == 4)
	{
		if (bmx == 0 && bmy == 0)
		{
			py = py + 1;

			Movement_Sub_Update();

			bmx = -28;
			bmy = 14;
		}

		if (bmx < -2)
		{
			bmx = bmx + 2;
		}
		else
		{
			bmx = 0;

			Movement_Sub_Sub();

			dx = px;
		}

		if (bmy > 1)
		{
			bmy = bmy - 1;
		}
		else
		{
			bmy = 0;

			Movement_Sub_Sub();

			dy = py;
		}
	}
}

void Character::Movement_Sub_Update()
{
	if (plocation == 1)
	{
		MB1[px - 1][py - 1] = 1;

		if (move_direction == 1)
		{
			MB1[px - 1][py] = 0;
		}

		else if (move_direction == 2)
		{
			MB1[px - 2][py - 1] = 0;
		}

		else if (move_direction == 3)
		{
			MB1[px][py - 1] = 0;
		}

		else if (move_direction == 4)
		{
			MB1[px - 1][py - 2] = 0;
		}
	}
}

void Character::Movement_Sub_Sub()
{
	if (Key_Down(DIK_DOWN))
	{
		char_status = 11;

		Movement_Lock();

		move_direction = 1;
	}
	else if (Key_Down(DIK_RIGHT))
	{
		char_status = 21;

		Movement_Lock();

		move_direction = 2;
	}
	else if (Key_Down(DIK_LEFT))
	{
		char_status = 31;

		Movement_Lock();

		move_direction = 3;
	}
	else if (Key_Down(DIK_UP))
	{
		char_status = 41;

		Movement_Lock();

		move_direction = 4;
	}
	else
	{
		move_status = 0;
	}
}

void Character::Movement_Lock()
{
	if (move_direction == 1)
	{
		if (py > 1)
		{	
			Movement_Lock_Sub();
		}

		else
		{
			move_count_keeper = 0;
			move_instant_count = 0;

			move_status = 0;
		}
	}

	else if (move_direction == 2)
	{
		if (px < 8)
		{
			Movement_Lock_Sub();
		}

		else
		{
			move_count_keeper = 0;
			move_instant_count = 0;

			move_status = 0;
		}
	}

	else if (move_direction == 3)
	{
		if (px > 1)
		{
			Movement_Lock_Sub();
		}

		else
		{
			move_count_keeper = 0;
			move_instant_count = 0;

			move_status = 0;
		}
	}

	else if (move_direction == 4)
	{
		if (py < 8)
		{
			Movement_Lock_Sub();
		}

		else
		{
			move_count_keeper = 0;
			move_instant_count = 0;

			move_status = 0;
		}
	}
}

void Character::Movement_Lock_Sub()
{
	if (plocation == 1)
	{
		if (move_direction == 1)
		{
			if (MB1[px - 1][py - 2] != 1)
			{
				move_status = 1;

				move_count_keeper = 0;
				move_instant_count = 0;
			}

			else
			{
				move_count_keeper = 0;
				move_instant_count = 0;

				move_status = 0;
			}
		}

		else if (move_direction == 2)
		{
			if (MB1[px][py - 1] != 1)
			{
				move_status = 1;

				move_count_keeper = 0;
				move_instant_count = 0;
			}

			else
			{
				move_count_keeper = 0;
				move_instant_count = 0;

				move_status = 0;
			}
		}

		else if (move_direction == 3)
		{
			if (MB1[px - 2][py - 1] != 1)
			{
				move_status = 1;

				move_count_keeper = 0;
				move_instant_count = 0;
			}

			else
			{
				move_count_keeper = 0;
				move_instant_count = 0;

				move_status = 0;
			}
		}

		else if (move_direction == 4)
		{
			if (MB1[px - 1][py] != 1)
			{
				move_status = 1;

				move_count_keeper = 0;
				move_instant_count = 0;
			}

			else
			{
				move_count_keeper = 0;
				move_instant_count = 0;

				move_status = 0;
			}
		}
	}
}

void Character::Attack()
{
	if (move_status == 0)
	{
		if (Key_Down(DIK_SPACE))
		{
			if (attack_delay == 0)
			{
				attack_delay = 1;
				attack_status = 1;
				combat_status = 1;
			}
		}

		if (attack_delay >= 1)
		{
			attack_delay++;

			if (attack_delay == 30)
			{
				attack_delay = 0;
				attack_status = 0;
			}
		}

		if (attack_delay <= 15 && attack_delay >= 3)
		{
			if (move_direction == 1)
			{
				char_status = 111;
			}

			else if (move_direction == 2)
			{
				char_status = 211;
			}

			else if (move_direction == 3)
			{
				char_status = 311;
			}

			else if (move_direction == 4)
			{
				char_status = 411;
			}
		}

		else
		{
			if (move_direction == 1)
			{
				char_status = 1;
			}

			else if (move_direction == 2)
			{
				char_status = 2;
			}

			else if (move_direction == 3)
			{
				char_status = 3;
			}

			else if (move_direction == 4)
			{
				char_status = 4;
			}
		}

		if (attack_delay == 15)
		{
			attack_status = 2;
		}
	}

	if (move_status == 1)
	{
		attack_delay = 0;
		attack_status = 0;
	}
}

void Character::Combat()
{
	if (combat_status == 1)
	{
		combat_status = 0;

		if (move_direction == 1)
		{
			if (py > 1)
			{
				if (MB1x[px - 1][py - 2] != 0)
				{
					MB1x[px - 1][py - 2]->cHP = MB1x[px - 1][py - 2]->cHP - (attack_power + (rand()%5 - 2));

					MB1x[px - 1][py - 2]->chealth_count = 150;
				}
			}
		}

		if (move_direction == 2)
		{
			if (px < (location_addr->size_x))
			{
				if (MB1x[px][py - 1] != 0)
				{
					MB1x[px][py - 1]->cHP = MB1x[px][py - 1]->cHP - (attack_power + (rand()%5 - 2));

					MB1x[px][py - 1]->chealth_count = 150;
				}
			}
		}

		if (move_direction == 3)
		{
			if (px > 1)
			{
				if (MB1x[px - 2][py - 1] != 0)
				{
					MB1x[px - 2][py - 1]->cHP = MB1x[px - 2][py - 1]->cHP - (attack_power + (rand()%5 - 2));

					MB1x[px - 2][py - 1]->chealth_count = 150;
				}
			}
		}

		if (move_direction == 4)
		{
			if (py < (location_addr->size_y))
			{
				if (MB1x[px - 1][py] != 0)
				{
					MB1x[px - 1][py]->cHP = MB1x[px - 1][py]->cHP - (attack_power + (rand()%5 - 2));

					MB1x[px - 1][py]->chealth_count = 150;
				}
			}
		}
	}
}					//934