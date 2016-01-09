#include "GameCode.h"
#include "gamescript.h"
#include "CString"
#include <cstdlib>
#include <stdio.h>
#include <string>
#include <vector>

using namespace std;

int sound_status = 1;

void Gameplay();												//Primary Loop for game calculations and gameplay
void Gamedraw();												//Primary Loop for drawing functions

void Interface();												//Draw Interface
void Map_Draw();												//Draw Map
void Objects();													//Draw Background Objects

void Draw_HP();
void Draw_Cursor();

void Drawing();
void Draw_Trans();

void Monster_Update();											//Update Monsters for FPS fixing. (Weird Dislocation Glitch)

void Windows();

void Monsters(Monster& Creep, Map& Habitat, int X);

int Wait(int time);

void Arrangement();

int draw_count;

Monster* Monster_Addr1[10];										//Hold Monster Addresses for Grasslands

short int MB1[8][8] = {	0, 0, 0, 0, 0, 0, 0, 0,
						0, 0, 0, 0, 0, 0, 0, 0,
						0, 0, 0, 0, 0, 1, 0, 0,
						0, 1, 1, 0, 0, 1, 1, 1,
						0, 0, 0, 0, 0, 0, 0, 0,
						0, 1, 1, 0, 0, 1, 1, 0,
						0, 0, 0, 0, 0, 0, 0, 0,
						0, 0, 0, 0, 0, 0, 0, 0};

Monster* MB1x[8][8] = {	0, 0, 0, 0, 0, 0, 0, 0,
						0, 0, 0, 0, 0, 0, 0, 0,
						0, 0, 0, 0, 0, 0, 0, 0,
						0, 0, 0, 0, 0, 0, 0, 0,
						0, 0, 0, 0, 0, 0, 0, 0,
						0, 0, 0, 0, 0, 0, 0, 0,
						0, 0, 0, 0, 0, 0, 0, 0,
						0, 0, 0, 0, 0, 0, 0, 0};

vector<Window*> WVector(10,0);
vector<Window*>::iterator Wit;

HRESULT result;													//Needed for Loading Sprite Handler

long int start = GetTickCount();								//Frames-Per-Second Controller
long int start2 = GetTickCount();

int Map1A[3][2] =  {150, 1,
					150, 1,
					150, 1};

extern Map Grasslands;											//Create Map 1

extern Map* location_addr;;										//Remember to set!

extern Monster Squidgee;										//Create Monster Squidgee

extern Window QW;

extern Window HM;

extern Window Menu;

extern Window Stats;

extern Collection Pictures;

extern Rainbow Colors;

extern Mice Mouse;

extern SH Sprite;

extern Character Player;

extern Font Main_Font;
extern Font HUD_Font;

int Game_Init(HWND hwnd)
{
	srand((unsigned)time(0)); 

	result = D3DXCreateSprite(d3ddev, &Sprite.SpHd);				//Create Sprite Handler
	if (result != D3D_OK)
	{
		return 0;
	}

	Main_Font.Prepare();
	HUD_Font.Prepare();

	Pictures.back = LoadSurface("back.bmp", NULL);			//Create Surfaces

	Pictures.IF = LoadTexture("Interface.bmp", Colors.white);					//Create Textures

	Pictures.grassland = LoadTexture("Demo Map.tga", Colors.black);

	Pictures.objects = LoadTexture("Demo Objects.tga", Colors.black);

	Pictures.character = LoadTexture("Character.tga", Colors.pink);

	Pictures.HP_out = LoadTexture("HP_Out.bmp", Colors.white);

	Pictures.HP_in = LoadTexture("HP_in.bmp", Colors.white);

	Pictures.cursor1 = LoadTexture("Cursor.tga", Colors.white);

	Pictures.quit_window_out = LoadTexture("Quit Window.bmp", Colors.white);

	Pictures.quit_window_in = LoadTexture("Quit Window.bmp", D3DCOLOR_XRGB(64, 96, 192));

	Pictures.HM_window_in = LoadTexture("HM Window In.bmp", D3DCOLOR_XRGB(64, 96, 192));

	Pictures.HM_window_out = LoadTexture("HM Window Out.bmp", Colors.white);

	Pictures.HP_bar_in = LoadTexture("HP In.bmp", Colors.white);

	Pictures.HP_bar_out = LoadTexture("HP Out.bmp", Colors.white);

	Pictures.MP_bar_in = LoadTexture("MP In.bmp", Colors.white);

	Pictures.MP_bar_out = LoadTexture("MP Out.bmp", Colors.white);

	Pictures.stats_window_in = LoadTexture("ST Window In", D3DCOLOR_XRGB(34, 177, 76));

	Pictures.stats_window_out = LoadTexture("ST Window Out", Colors.white);

	Pictures.stats_window_content = LoadTexture("ST Window CT", Colors.white);

	Pictures.main_window_in = LoadTexture("Main In.bmp", D3DCOLOR_XRGB(34, 177, 76));

	Pictures.main_window_out = LoadTexture("Main Out.bmp", Colors.white);

	Pictures.main_button_quit = LoadTexture("QB.bmp", Colors.white);

	Pictures.main_button_HM = LoadTexture("HMB.bmp", Colors.white);

	if (!Init_DirectInput(hwnd))								//Load DirectInput
	{
		MessageBox(hwnd, "Error", "Error", MB_OK);
		return 0;
	}

	if (!Init_Mouse(hwnd))										//Load Mouse
	{
		return 0;
	}

	if (!Init_Keyboard(hwnd))									//Load Keyboard
	{
		return 0;
	}

	Grasslands.Set_Texture(Pictures.grassland);

	Squidgee.CSet_Texture(Pictures.character);

	QW.WSet_Texture(Pictures.quit_window_in, Pictures.quit_window_out);

	HM.WSet_Texture(Pictures.HM_window_in, Pictures.HM_window_out);

	Menu.WSet_Texture(Pictures.main_window_in, Pictures.main_window_out);

	Wit = WVector.begin();
	WVector.insert(Wit, &HM);
	Wit = WVector.begin();
	WVector.insert(Wit, &QW);
	Wit = WVector.begin();
	WVector.insert(Wit, &Menu);

	return 1;
}

void Monsters(Monster& Creep, Map& Habitat, int X)
{
	if (Creep.calive == 1)
	{
		Creep.CDamage();
	}

	if (Creep.calive == 2)
	{
		Creep.CDie();
	}

	if (Creep.calive == 0)
	{
		if (Creep.climit < Habitat.Monster_Stats[X - 1][1])
		{
			Creep.CSpawn();

			Creep.clocation = Habitat.number;
		}
	}

	if (Creep.calive == 0 && Creep.crespawn_count == 0)
	{
		Creep.crespawn_count = Habitat.Monster_Stats[X - 1][0];
	}

	if (Creep.calive == 0)
	{
		if (Creep.crespawn_count == 1)
		{
			Creep.climit--;

			Creep.crespawn_count = 0;
		}

		else
		{
			Creep.crespawn_count--;
		}
	}

	if (Creep.calive == 1)
	{
		Creep.CMove();
	}
}

void Map_Draw()
{
	if (Player.plocation == Grasslands.number)
	{
		Grasslands.Draw();
	}
}

void Objects()
{
	if (Player.plocation == Grasslands.number)
	{
		D3DXVECTOR3 position ((float)(-((Player.px * 28) + (Player.py * 28) + Player.bmx) + 290), 
			(float)(-((Player.px * 14) - (Player.py * 14) + Player.bmy) + 124), 0);

		Sprite.SpHd->Draw(Pictures.objects,
			NULL,
			NULL,
			&position,
			Colors.white);
	}
}

void Drawing()
{
	int bbx = Squidgee.cx - Player.px;
	int bby = Squidgee.cy - Player.py;

	if (bbx - bby >= 0)
	{
		if (bbx == bby && bby <= 0 && bbx <= 0)
		{
			if (Squidgee.calive == 1)
			{
				Squidgee.CDraw();
			}

			else if (Squidgee.calive == 2)
			{
				Squidgee.CDie();
			}

			Player.Draw_Character();
		}
		else
		{
			Player.Draw_Character();

			if (Squidgee.calive == 1)
			{
				Squidgee.CDraw();
			}

			else if (Squidgee.calive == 2)
			{
				Squidgee.CDie();
			}
		}
	}
	else
	{

		if (Squidgee.calive == 1)
		{
			Squidgee.CDraw();
		}

		else if (Squidgee.calive == 2)
		{
			Squidgee.CDie();
		}

		Player.Draw_Character();
	}
}

void Draw_Trans()
{
}

void Draw_HP()
{
	if (Player.plocation == 1)
	{
		Squidgee.CShow_HP();
	}
}

void Draw_Cursor()
{
	D3DXVECTOR3 position ((float)b_mouse_state.lX, (float)b_mouse_state.lY, 0);

	Sprite.SpHd->Draw(Pictures.cursor1, NULL, NULL, &position, Colors.white);
}

void Interface()
{
}

void Windows()
{
	Arrangement();

	if (WVector[0] != 0)
	{
		if (WVector[0]->wstatus == 1)
		{
			WVector[0]->WMouse_Check();
		}
		else
		{
			WVector.erase(WVector.begin() + 0);
		}
	}

	if (WVector[1] != 0)
	{
		if (WVector[1]->wstatus == 1)
		{
			WVector[1]->WMouse_Check();
		}
		else
		{
			WVector.erase(WVector.begin() + 1);
		}
	}

	if (WVector[2] != 0)
	{
		if (WVector[2]->wstatus == 1)
		{
			WVector[2]->WMouse_Check();
		}
		else
		{
			WVector.erase(WVector.begin() + 2);
		}
	}

	if (WVector[3] != 0)
	{
		if (WVector[3]->wstatus == 1)
		{
			WVector[3]->WMouse_Check();
		}
		else
		{
			WVector.erase(WVector.begin() + 3);
		}
	}

	if (WVector[4] != 0)
	{
		if (WVector[4]->wstatus == 1)
		{
			WVector[4]->WMouse_Check();
		}
		else
		{
			WVector.erase(WVector.begin() + 4);
		}
	}

	if (WVector[5] != 0)
	{
		if (WVector[5]->wstatus == 1)
		{
			WVector[5]->WMouse_Check();
		}
		else
		{
			WVector.erase(WVector.begin() + 5);
		}
	}

	if (WVector[6] != 0)
	{
		if (WVector[6]->wstatus == 1)
		{
			WVector[6]->WMouse_Check();
		}
		else
		{
			WVector.erase(WVector.begin() + 6);
		}
	}

	if (WVector[7] != 0)
	{
		if (WVector[7]->wstatus == 1)
		{
			WVector[7]->WMouse_Check();
		}
		else
		{
			WVector.erase(WVector.begin() + 7);
		}
	}

	if (WVector[8] != 0)
	{
		if (WVector[8]->wstatus == 1)
		{
			WVector[8]->WMouse_Check();
		}
		else
		{
			WVector.erase(WVector.begin() + 8);
		}
	}

	if (WVector[9] != 0)
	{
		if (WVector[9]->wstatus == 1)
		{
			WVector[9]->WMouse_Check();
		}
		else
		{
			WVector.erase(WVector.begin() + 9);
		}
	}

	if (WVector[0] != 0)
	{
		if (WVector[0]->wstatus == 1)
		{
			WVector[0]->WStatic(1);
		}
		else
		{
			WVector.erase(WVector.begin() + 0);
		}
	}

	if (WVector[1] != 0)
	{
		if (WVector[1]->wstatus == 1)
		{
			WVector[1]->WStatic(0);
		}
		else
		{
			WVector.erase(WVector.begin() + 1);
		}
	}

	if (WVector[2] != 0)
	{
		if (WVector[2]->wstatus == 1)
		{
			WVector[2]->WStatic(0);
		}
		else
		{
			WVector.erase(WVector.begin() + 2);
		}
	}

	if (WVector[3] != 0)
	{
		if (WVector[3]->wstatus == 1)
		{
			WVector[3]->WStatic(0);
		}
		else
		{
			WVector.erase(WVector.begin() + 3);
		}
	}

	if (WVector[4] != 0)
	{
		if (WVector[4]->wstatus == 1)
		{
			WVector[4]->WStatic(0);
		}
		else
		{
			WVector.erase(WVector.begin() + 4);
		}
	}

	if (WVector[5] != 0)
	{
		if (WVector[5]->wstatus == 1)
		{
			WVector[5]->WStatic(0);
		}
		else
		{
			WVector.erase(WVector.begin() + 5);
		}
	}

	if (WVector[6] != 0)
	{
		if (WVector[6]->wstatus == 1)
		{
			WVector[6]->WStatic(0);
		}
		else
		{
			WVector.erase(WVector.begin() + 6);
		}
	}

	if (WVector[7] != 0)
	{
		if (WVector[7]->wstatus == 1)
		{
			WVector[7]->WStatic(0);
		}
		else
		{
			WVector.erase(WVector.begin() + 7);
		}
	}

	if (WVector[8] != 0)
	{
		if (WVector[8]->wstatus == 1)
		{
			WVector[8]->WStatic(0);
		}
		else
		{
			WVector.erase(WVector.begin() + 8);
		}
	}

	if (WVector[9] != 0)
	{
		if (WVector[9]->wstatus == 1)
		{
			WVector[9]->WStatic(0);
		}
		else
		{
			WVector.erase(WVector.begin() + 9);
		}
	}


	if (WVector[9] != 0)
	{
		if (WVector[9]->wstatus == 1)
		{
			WVector[9]->WStatic_R(0);
		}
	}

	if (WVector[8] != 0)
	{
		if (WVector[8]->wstatus == 1)
		{
			WVector[8]->WStatic_R(0);
		}
	}

	if (WVector[7] != 0)
	{
		if (WVector[7]->wstatus == 1)
		{
			WVector[7]->WStatic_R(0);
		}
	}

	if (WVector[6] != 0)
	{
		if (WVector[6]->wstatus == 1)
		{
			WVector[6]->WStatic_R(0);
		}
	}

	if (WVector[5] != 0)
	{
		if (WVector[5]->wstatus == 1)
		{
			WVector[5]->WStatic_R(0);
		}
	}

	if (WVector[4] != 0)
	{
		if (WVector[4]->wstatus == 1)
		{
			WVector[4]->WStatic_R(0);
		}
	}

	if (WVector[3] != 0)
	{
		if (WVector[3]->wstatus == 1)
		{
			WVector[3]->WStatic_R(0);
		}
	}

	if (WVector[2] != 0)
	{
		if (WVector[2]->wstatus == 1)
		{
			WVector[2]->WStatic_R(0);
		}
	}

	if (WVector[1] != 0)
	{
		if (WVector[1]->wstatus == 1)
		{
			WVector[1]->WStatic_R(0);
		}
	}

	if (WVector[0] != 0)
	{
		if (WVector[0]->wstatus == 1)
		{
			WVector[0]->WStatic_R(1);
		}
	}

	QW.WVector_Check();						//If the window has been opened, add it to the front of the vector

	HM.WVector_Check();

	Window::wlock = 1;						//Unlock at the end of frame (You can only make one opening per frame)
	Window::wlock_active = 1;				//...
}

void Arrangement()
{
}

void Gameplay()
{
	Monsters(Squidgee, Grasslands, 1);
	Player.Attack();
	Player.Combat();
	Player.Movement();
}

void Gamedraw()
{
	Monster_Update();
	Map_Draw();
	Objects();
	Drawing();
	Draw_Trans();
	Draw_HP();
}

void Monster_Update()
{
	Squidgee.CUpdate();
}

void Game_Run(HWND hwnd)
{
	Poll_Keyboard();

	if (d3ddev == NULL)
	{
		return;
	}

	if (d3ddev->BeginScene())
	{
		Sprite.SpHd->Begin(D3DXSPRITE_ALPHABLEND);

		if ((GetTickCount() - 15) >= start2)
		{
			start2 = GetTickCount();

			d3ddev->StretchRect(
				Pictures.back,
				NULL, 
				backbuffer,
				NULL, 
				D3DTEXF_NONE);

			Gamedraw();

			Poll_Mouse();

			Update_BM();

			Windows();

			Draw_Cursor();

			Mouse.Mouse_Loop();
		}

		if ((GetTickCount() - 30)  >= start)
		{
			if (Key_Down(DIK_ESCAPE))
			{
				PostMessage(hwnd, WM_DESTROY, 0, 0); 
			}

			start = GetTickCount();

			Gameplay();
		}

		Sprite.SpHd->End();
		d3ddev->EndScene();
	}

	d3ddev->Present(NULL, NULL, NULL, NULL);
}

void Game_End(HWND hwnd)
{
	if (Sprite.SpHd != NULL)
	{
		Sprite.SpHd->Release();
	}

	if (Pictures.back != NULL)
	{
		Pictures.back->Release();
	}

	if (Main_Font.ffont != NULL)
	{
		Main_Font.ffont->Release();
	}

	if (HUD_Font.ffont != NULL)
	{
		HUD_Font.ffont->Release();
	}

	if (Pictures.IF != NULL)
	{
		Pictures.IF->Release();
	}

	if (Pictures.character != NULL)
	{
		Pictures.character->Release();
	}

	if (Pictures.clothes != NULL)
	{
		Pictures.clothes->Release();
	}

	if (Pictures.shoes != NULL)
	{
		Pictures.shoes->Release();
	}

	if (Pictures.weapon != NULL)
	{
		Pictures.weapon->Release();
	}

	if (Pictures.grassland != NULL)
	{
		Pictures.grassland->Release();
	}

	if (Pictures.objects != NULL)
	{
		Pictures.objects->Release();
	}

	if (Pictures.HP_in != NULL)
	{
		Pictures.HP_in->Release();
	}

	if (Pictures.HP_out != NULL)
	{
		Pictures.HP_out->Release();
	}

	if (Pictures.HM_window_in != NULL)
	{
		Pictures.HM_window_in->Release();
	}

	if (Pictures.HM_window_out != NULL)
	{
		Pictures.HM_window_out->Release();
	}
	
	if (Pictures.HP_bar_in != NULL)
	{
		Pictures.HP_bar_in->Release();
	}

	if (Pictures.HP_bar_out != NULL)
	{
		Pictures.HP_bar_out->Release();
	}

	if (Pictures.MP_bar_in != NULL)
	{
		Pictures.MP_bar_in->Release();
	}

	if (Pictures.MP_bar_out != NULL)
	{
		Pictures.MP_bar_out->Release();
	}

	if (Pictures.main_window_in != NULL)
	{
		Pictures.main_window_in->Release();
	}

	if (Pictures.main_window_out != NULL)
	{
		Pictures.main_window_out->Release();
	}

	if (Pictures.main_button_quit != NULL)
	{
		Pictures.main_button_quit->Release();
	}

	if (Pictures.main_button_HM != NULL)
	{
		Pictures.main_button_HM->Release();
	}

	if (Pictures.cursor1 != NULL)
	{
		Pictures.cursor1->Release();
	}

	if (Pictures.quit_window_out != NULL)
	{
		Pictures.quit_window_out->Release();
	}

	if (Pictures.quit_window_in != NULL)
	{
		Pictures.quit_window_in->Release();
	}

	if (Pictures.stats_window_in != NULL)
	{
		Pictures.stats_window_in->Release();
	}

	if (Pictures.stats_window_out != NULL)
	{
		Pictures.stats_window_out->Release();
	}

	if (Pictures.stats_window_content != NULL)
	{
		Pictures.stats_window_content->Release();
	}
}