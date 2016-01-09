#include <d3d9.h>
#include <d3dx9.h>

#include "Monsters.h"
#include "SpriteHandler.h"
#include "Colors.h"
#include "Collection.h"
#include "Characters.h"
#include "Engine.h"

extern SH Sprite;
extern Rainbow Colors;
extern Collection Pictures;
extern Character Player;

extern short int MB1[8][8];
extern Monster* MB1x[8][8];

Monster Squidgee(1, 100, 0, 1, 0, "Squidgee", 1);

Monster::Monster(int Type, int Hp, int Mp, int Activity, int Aggressive, char* Name, int Number)
{
	ctype = Type;
	cHP = Hp;
	cMHP = Hp;
	cactivity = Activity;
	caggressive = Aggressive;
	cname = Name;
	cnumber = Number;

	chealth_count = 0;

	caggro = 0;

	cbmx = 0;
	cbmy = 0;

	calpha = 255;

	cmove_status = 0;
	cmove_count_keeper = 0;
	cmove_direction = 0;

	cattack_status = 0;
	cattack_delay = 0;

	cchar_status = (rand()%4)+1;

	crespawn_count = 0;

	climit = 0;
}

void Monster::CSet_Texture(LPDIRECT3DTEXTURE9 Texture)
{
	ctexture = Texture;
}

void Monster::CDraw()
{
	if (calive == 1)
	{
		if (cchar_status == 1)
		{
			RECT rect;
			rect.top = 0;
			rect.left = 0;
			rect.bottom = 50;
			rect.right = 50;

			Sprite.SpHd->Draw(ctexture,
				&rect,
				NULL,
				&cposition,
				Colors.white);
		}

		if (cchar_status == 2)
		{
			RECT rect;
			rect.top = 0;
			rect.left = 50;
			rect.bottom = 50;
			rect.right = 100;

			Sprite.SpHd->Draw(ctexture,
				&rect,
				NULL,
				&cposition,
				Colors.white);
		}

		if (cchar_status == 3)
		{
			RECT rect;
			rect.top = 0;
			rect.left = 100;
			rect.bottom = 50;
			rect.right = 150;

			Sprite.SpHd->Draw(ctexture,
				&rect,
				NULL,
				&cposition,
				Colors.white);
		}

		if (cchar_status == 4)
		{
			RECT rect;
			rect.top = 0;
			rect.left = 150;
			rect.bottom = 50;
			rect.right = 200;

			Sprite.SpHd->Draw(ctexture,
				&rect,
				NULL,
				&cposition,
				Colors.white);
		}

		if (cchar_status == 11)
		{
			RECT rect;
			rect.top = 50;
			rect.left = 0;
			rect.bottom = 100;
			rect.right = 50;

			Sprite.SpHd->Draw(ctexture,
				&rect,
				NULL,
				&cposition,
				Colors.white);
		}

		if (cchar_status == 21)
		{
			RECT rect;
			rect.top = 50;
			rect.left = 50;
			rect.bottom = 100;
			rect.right = 100;

			Sprite.SpHd->Draw(ctexture,
				&rect,
				NULL,
				&cposition,
				Colors.white);
		}

		if (cchar_status == 31)
		{
			RECT rect;
			rect.top = 50;
			rect.left = 100;
			rect.bottom = 100;
			rect.right = 150;

			Sprite.SpHd->Draw(ctexture,
				&rect,
				NULL,
				&cposition,
				Colors.white);
		}

		if (cchar_status == 41)
		{
			RECT rect;
			rect.top = 50;
			rect.left = 150;
			rect.bottom = 100;
			rect.right = 200;

			Sprite.SpHd->Draw(ctexture,
				&rect,
				NULL,
				&cposition,
				Colors.white);
		}

		if (cchar_status == 111)
		{
			RECT rect;
			rect.top = 100;
			rect.left = 0;
			rect.bottom = 150;
			rect.right = 50;

			Sprite.SpHd->Draw(ctexture,
				&rect,
				NULL,
				&cposition,
				Colors.white);
		}

		if (cchar_status == 211)
		{
			RECT rect;
			rect.top = 100;
			rect.left = 50;
			rect.bottom = 150;
			rect.right = 100;

			Sprite.SpHd->Draw(ctexture,
				&rect,
				NULL,
				&cposition,
				Colors.white);
		}

		if (cchar_status == 311)
		{
			RECT rect;
			rect.top = 100;
			rect.left = 100;
			rect.bottom = 150;
			rect.right = 150;

			Sprite.SpHd->Draw(ctexture,
				&rect,
				NULL,
				&cposition,
				Colors.white);
		}

		if (cchar_status == 411)
		{
			RECT rect;
			rect.top = 100;
			rect.left = 150;
			rect.bottom = 150;
			rect.right = 200;

			Sprite.SpHd->Draw(ctexture,
				&rect,
				NULL,
				&cposition,
				Colors.white);
		}
	}
}

void Monster::CUpdate()
{
	D3DXVECTOR3 DontCare((float)(-((Player.px * 28) + (Player.py * 28) + Player.bmx - cbmx) + (cx * 28) + (cy * 28)) + 375,
		(float)(-((Player.px * 14) - (Player.py * 14) + Player.bmy - cbmy)) + (cx * 14) - (cy * 14) + 205 + 50, 0);

	c_hp_position = D3DXVECTOR3((float)(-((Player.px * 28) + (Player.py * 28) + Player.bmx - cbmx) + (cx * 28) + (cy * 28)) + 375,
		(float)(-((Player.px * 14) - (Player.py * 14) + Player.bmy - cbmy)) + (cx * 14) - (cy * 14) + 196 + 50, 0);

	if (clocation == 1)
	{
		if (calive == 1)
		{
			MB1[cx - 1][cy - 1] = 1;
			MB1x[cx - 1][cy - 1] = this;
		}
	}

	cposition = DontCare;
}

void Monster::CSpawn()
{
	climit++;

	calive = 1;

	cx = 8;
	cy = 8;

	cdx = cx;
	cdy = Player.dy;

	calpha = 255;
}

void Monster::CMove()
{
	if (cattack_status != 1)
	{
		if (cmove_count_keeper >= 60 && cmove_status != 1)
		{
			cmove_count_keeper = 0;

			int n;
			int m;

			n = (rand()%4) + 1;
			m = (rand()%100) + 1;

			if (n == 1)
			{
				cmove_direction = 1;
				cchar_status = 1;

				if (m != 1 && m != 2)
				{
					CMove_Lock();
				}

				else if (m == 1 || m == 2)
				{
					cchar_status = 1;
				}
			}

			else if (n == 2)
			{
				cmove_direction = 2;
				cchar_status = 2;

				if (m != 1 && m != 2)
				{
					CMove_Lock();
				}

				else if (m == 1 || m == 2)
				{
					cchar_status = 1;
				}
			}

			else if (n == 3)
			{
				cmove_direction = 3;
				cchar_status = 3;

				if (m != 1 && m != 2)
				{
					CMove_Lock();
				}

				else if (m == 1 || m == 2)
				{
					cchar_status = 1;
				}
			}

			else if (n == 4)
			{
				cmove_direction = 4;
				cchar_status = 4;

				if (m != 1 && m != 2)
				{
					CMove_Lock();
				}

				else if (m == 1 || m == 2)
				{
					cchar_status = 1;
				}
			}

			else if (n == 5)
			{
				cmove_count_keeper = 10;
			}

			else if (n == 6)
			{
				cmove_count_keeper = 35;
			}

			else if (n == 7)
			{
				cmove_count_keeper = 46;
			}

			else if (n == 8)
			{
				cmove_count_keeper = 50;
			}

			else if (n == 9)
			{
				cmove_count_keeper = 25;

				int w;
				w = (rand()%4) + 1;

				cmove_direction = w;
				cchar_status = w;
			}

			else if (n == 10)
			{
				cmove_count_keeper = 20;

				int w;
				w = (rand()%4) + 1;

				cmove_direction = w;
				cchar_status = w;
			}
		}

		else
		{
			cmove_count_keeper++;
		}

		if (cmove_status == 1)
		{
			if (cmove_direction == 1)
			{
				cchar_status = 11;
				CMove_Sub(1);
			}

			else if (cmove_direction == 2)
			{
				cchar_status = 21;
				CMove_Sub(2);
			}

			else if (cmove_direction == 3)
			{
				cchar_status = 31;
				CMove_Sub(3);
			}

			else if (cmove_direction == 4)
			{
				cchar_status = 41;
				CMove_Sub(4);
			}
		}
	}
}

void Monster::CMove_Lock()
{
	if (cmove_direction == 1)
	{
		if (cy > 1)
		{
			CMove_Lock_Sub();
		}

		else
		{
			cmove_count_keeper = 40;
			cmove_status = 0;
		}
	}

	else if (cmove_direction == 2)
	{
		if (cx < 8)
		{
			CMove_Lock_Sub();
		}

		else
		{
			cmove_count_keeper = 40;
			cmove_status = 0;
		}
	}

	else if (cmove_direction == 3)
	{
		if (cx > 1)
		{
			CMove_Lock_Sub();
		}

		else
		{
			cmove_count_keeper = 40;
			cmove_status = 0;
		}
	}

	else if (cmove_direction == 4)
	{
		if (cy < 8)
		{
			CMove_Lock_Sub();
		}

		else
		{
			cmove_count_keeper = 40;
			cmove_status = 0;
		}
	}
}

void Monster::CMove_Lock_Sub()
{
	if (clocation == 1)
	{
		if (cmove_direction == 1)
		{
			if (MB1[cx - 1][cy - 2] != 1)
			{
				cmove_status = 1;
			}

			else
			{
				cmove_count_keeper = 40;
				cmove_status = 0;
			}
		}

		else if (cmove_direction == 2)
		{
			if (MB1[cx][cy - 1] != 1)
			{
				cmove_status = 1;
			}

			else
			{
				cmove_count_keeper = 40;
				cmove_status = 0;
			}
		}

		else if (cmove_direction == 3)
		{
			if (MB1[cx - 2][cy - 1] != 1)
			{
				cmove_status = 1;
			}

			else
			{
				cmove_count_keeper = 40;
				cmove_status = 0;
			}
		}

		else if (cmove_direction == 4)
		{
			if (MB1[cx - 1][cy] != 1)
			{
				cmove_status = 1;
			}

			else
			{
				cmove_count_keeper = 40;
				cmove_status = 0;
			}
		}
	}
}

void Monster::CDie()
{
	if (calpha != 0)
	{
		calpha = calpha - 5;
	}

	if (calpha == 0)
	{
		MB1[cx - 1][cx - 1] = 0;
		MB1x[cx - 1][cy - 1] = 0;

		calive = 0;
	}

	if (cmove_direction == 1)
	{
		cchar_status = 1;
	}

	else if (cmove_direction == 2)
	{
		cchar_status = 2;
	}

	else if (cmove_direction == 3)
	{
		cchar_status = 3;
	}

	else if (cmove_direction == 4)
	{
		cchar_status = 4;
	}

	if (cchar_status == 1)
	{
		RECT rect;
		rect.top = 0;
		rect.left = 0;
		rect.bottom = 50;
		rect.right = 50;

		Sprite.SpHd->Draw(ctexture,
			&rect,
			NULL,
			&cposition,
			D3DCOLOR_ARGB(calpha, 255, 255, 255));
	}

	if (cchar_status == 2)
	{
		RECT rect;
		rect.top = 0;
		rect.left = 50;
		rect.bottom = 50;
		rect.right = 100;

		Sprite.SpHd->Draw(ctexture,
			&rect,
			NULL,
			&cposition,
			D3DCOLOR_ARGB(calpha, 255, 255, 255));
	}

	if (cchar_status == 3)
	{
		RECT rect;
		rect.top = 0;
		rect.left = 100;
		rect.bottom = 50;
		rect.right = 150;

		Sprite.SpHd->Draw(ctexture,
			&rect,
			NULL,
			&cposition,
			D3DCOLOR_ARGB(calpha, 255, 255, 255));
	}

	if (cchar_status == 4)
	{
		RECT rect;
		rect.top = 0;
		rect.left = 150;
		rect.bottom = 50;
		rect.right = 200;

		Sprite.SpHd->Draw(ctexture,
			&rect,
			NULL,
			&cposition,
			D3DCOLOR_ARGB(calpha, 255, 255, 255));
	}
}

void Monster::CMove_Sub(int Direction)
{
	if (Direction == 1)
	{
		if (cbmx == 0 && cbmy == 0)
		{
			cy = cy - 1;

			CMove_Sub_Update();

			cbmx = 28;
			cbmy = -14;
		}

		if (cbmx > 2)
		{
			cbmx = cbmx - 2;
		}
		else
		{
			cbmx = 0;

			cmove_status = 0;
			cchar_status = 1;

			cdx = cx;
		}

		if (cbmy < -1)
		{
			cbmy = cbmy + 1;
		}
		else
		{
			cbmy = 0;

			cmove_status = 0;
			cchar_status = 1;

			cdy = cy;
		}
	}

	else if (Direction == 2)
	{
		if (cbmx == 0 && cbmy == 0)
		{
			cx = cx + 1;

			CMove_Sub_Update();

			cbmx = -28;
			cbmy = -14;
		}

		if (cbmx < -2)
		{
			cbmx = cbmx + 2;
		}
		else
		{
			cbmx = 0;

			cmove_status = 0;
			cchar_status = 2;

			cdx = cx;
		}

		if (cbmy < -1)
		{
			cbmy = cbmy + 1;
		}
		else
		{
			cbmy = 0;

			cmove_status = 0;
			cchar_status = 2;

			cdy = cy;
		}
	}

	else if (Direction == 3)
	{
		if (cbmx == 0 && cbmy == 0)
		{
			cx = cx - 1;

			CMove_Sub_Update();

			cbmx = 28;
			cbmy = 14;
		}

		if (cbmx > 2)
		{
			cbmx = cbmx - 2;
		}
		else
		{
			cbmx = 0;

			cmove_status = 0;
			cchar_status = 3;

			cdx = cx;
		}

		if (cbmy > 1)
		{
			cbmy = cbmy - 1;
		}
		else
		{
			cbmy = 0;

			cmove_status = 0;
			cchar_status = 3;

			cdy = cy;
		}
	}

	else if (Direction == 4)
	{
		if (cbmx == 0 && cbmy == 0)
		{
			cy = cy + 1;

			CMove_Sub_Update();

			cbmx = -28;
			cbmy = 14;
		}

		if (cbmx < -2)
		{
			cbmx = cbmx + 2;
		}
		else
		{
			cbmx = 0;

			cmove_status = 0;
			cchar_status = 4;

			cdx = cx;
		}

		if (cbmy > 1)
		{
			cbmy = cbmy - 1;
		}
		else
		{
			cbmy = 0;

			cmove_status = 0;
			cchar_status = 4;

			cdy = cy;
		}
	}
}

void Monster::CMove_Sub_Update()
{
	if (clocation == 1)
	{
		if (calive == 1)
		{
			MB1[cx - 1][cy - 1] = 1;
			MB1x[cx - 1][cy - 1] = this;
		}

		if (cmove_direction == 1)
		{
			MB1[cx - 1][cy] = 0;
			MB1x[cx - 1][cy] = 0;
		}

		else if (cmove_direction == 2)
		{
			MB1[cx - 2][cy - 1] = 0;
			MB1x[cx - 2][cy - 1] = 0;
		}

		else if (cmove_direction == 3)
		{
			MB1[cx][cy - 1] = 0;
			MB1x[cx][cy - 1] = 0;
		}

		else if (cmove_direction == 4)
		{
			MB1[cx - 1][cy - 2] = 0;
			MB1x[cx - 1][cy - 2] = 0;
		}
	}

	if (calive == 0)
	{
		MB1x[cx - 1][cy - 1] = 0;
	}
}

void Monster::CDamage()
{
	if (clocation == 1)
	{
		if (chealth_count > 0)
		{
			chealth_count--;
		}

		if (cHP <= 0 && calive != 2)
		{
			calive = 2;
			CReset();

			MB1x[cx - 1][cy - 1] = 0;
		}
	}
}

void Monster::CShow_HP()
{
	if (chealth_count > 0)
	{
		RECT rect1;
		rect1.top = 0;
		rect1.bottom = 6;
		rect1.left = 0;
		rect1.right = 46;

		RECT rect2;
		rect2.top = 0;
		rect2.bottom = 6;
		rect2.left = 0;

		if (cHP > 0)
		{
			rect2.right = ((float (cHP) / cMHP) * 46);
		}

		else
		{
			rect2.right = 0;
		}

		Sprite.SpHd->Draw(Pictures.HP_in, &rect2, NULL, &c_hp_position, Colors.white);

		Sprite.SpHd->Draw(Pictures.HP_out, &rect1, NULL, &c_hp_position, Colors.white);
	}
}

void Monster::CReset()
{
	cHP = cMHP;
	chealth_count = 0;

	caggro = 0;

	cbmx = 0;
	cbmy = 0;

	cmove_status = 0;
	cmove_count_keeper = 0;
	cmove_direction = 0;

	cattack_status = 0;
	cattack_delay = 0;

	cchar_status = (rand()%4)+1;

	calpha = 255;

	MB1x[cx - 1][cy - 1] = 0;
}					//933