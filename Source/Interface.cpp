#include <d3d9.h>
#include <d3dx9.h>
#include <vector>

#include "Interface.h"
#include "DXInput.h"
#include "Mouse.h"
#include "SpriteHandler.h"
#include "Collection.h"
#include "Characters.h"
#include "Engine.h"

extern Mice Mouse;
extern SH Sprite;
extern Collection Pictures;
extern Character Player;
	
extern vector<Window*> WVector;
extern vector<Window*>::iterator Wit;

Window QW(40, "Quit", 100, 50, 180, 255, 0, 200, 250, 0);

Window HM(2, "HP/MP", 150, 70, 180, 255, 230, 400, 400, 0);

Window Menu(0, "Main", 200, 70, 255, 255, 255, 400, 0, 0);

Window Stats(3, "Stats", 150, 180, 180, 250, 230, 50, 50, 0);

int Window::wlock = 0;
int Window::wlock_active = 0;

Window::Window(int Type,
			char* Name,
			int Width,
			int Height,
			int In_Alpha,
			int Out_Alpha,
			int Content_Alpha,
			int X,
			int Y,
			int Slider_On)
{
	wtype = Type;
	wname = Name;
	wwidth = Width;
	wheight = Height;
	wx = X;
	wy = Y;

	if (wtype != 0)														//WARNING : CHANGE IS NEEDED WHEN NEEDED
	{
		wstatus = 0;
	}
	else if (wtype == 0)
	{
		wstatus = 1;
	}

	if (wstatus == 1)
	{
		win_alpha = In_Alpha;
		wout_alpha = Out_Alpha;
		wcontent_alpha = Content_Alpha;
	}
	else 
	{
		win_alpha = 0;
		wout_alpha = 0;
		wcontent_alpha = 0;
	}

	wbin_alpha = In_Alpha;
	wbout_alpha = Out_Alpha;
	wbcontent_alpha = Content_Alpha;

	woin_alpha = In_Alpha;							//Set original alphas as the inserted alphas
	woout_alpha = Out_Alpha;
	wocontent_alpha = Content_Alpha;

	wbutton_status1 = 0;
	wbutton_status2 = 0;
	wbutton_status3 = 0;
	wbutton_status4 = 0;
	wbutton_status5 = 0;
	wbutton_status6 = 0;

	wdrag_tick = 0;

	wdet_tick = 0;

	wclose_status = 0;

	wactive = 0;

	wtop = 0;

	wmoving = 0;

	wclosing = 0;

	wslider = Slider_On;
}

void Window::WSet_Texture(LPDIRECT3DTEXTURE9 Texture1, LPDIRECT3DTEXTURE9 Texture2)
{
	wtexture_in = Texture1;

	wtexture_out = Texture2;
}

void Window::WDrag()
{
	if (b_mouse_state.lX > (wx) 
		&& b_mouse_state.lX < (wx + wwidth)
		&& b_mouse_state.lY < (wy + 21)
		&& b_mouse_state.lY > (wy)
		&& Mouse_Button(0)
		&& Mouse.Busy() == 0
		&& wclose_status == 0)
	{
		wdrag_tick = 1;

		wmoving = 1;

		wbusy = 2;
	}

	if (wdrag_tick == 1 && Mouse_Button(0) && wlock == 1)
	{
		wx = wx + mouse_state.lX;
		wy = wy + mouse_state.lY;

		wlock = 0;
	}
	else
	{
		wdrag_tick = 0;

		wmoving = 2;
	}
}

void Window::WDraw(int Top_Status)				//1 == Top, 0 == Not Top
{
	if (Top_Status == 0 || Top_Status == 1)		//Draw windows with their normal alpha. Opening functions handle the rest.
	{
		if (wstatus == 1)
		{
			D3DXVECTOR3 position((float)(wx), (float)(wy), 0);

			Sprite.SpHd->Draw(wtexture_in, NULL, NULL, &position, D3DCOLOR_ARGB(win_alpha, 255, 255, 255));

			Sprite.SpHd->Draw(wtexture_out, NULL, NULL, &position, D3DCOLOR_ARGB(wout_alpha, 255, 255, 255));
		}

		if (wtype == 0)
		{
			D3DXVECTOR3 window_position ((float)wx, (float)wy, 0);

			Sprite.SpHd->Draw(Pictures.main_button_HM, NULL, NULL, &window_position, D3DCOLOR_ARGB(wcontent_alpha, 255, 255, 255));

			Sprite.SpHd->Draw(Pictures.main_button_quit, NULL, NULL, &window_position, D3DCOLOR_ARGB(wcontent_alpha, 255, 255, 255));
		}

		if (wtype == 2)
		{
			if (wstatus == 1)
			{
				D3DXVECTOR3 window_position ((float)wx, (float)wy, 0);

				RECT rect1;
				rect1.top = 0;
				rect1.bottom = 70;
				rect1.left = 0;
				rect1.right = 150;

				RECT rect2;
				rect2.top = 0;
				rect2.bottom = 70;
				rect2.left = 0;

				if (Player.pHP > 0)
				{
					rect2.right = (12 + (float (Player.pHP) / Player.pMHP) * 125);
				}

				else
				{
					rect2.right = 0;
				}

				Sprite.SpHd->Draw(Pictures.HP_bar_in, &rect2, NULL, &window_position, D3DCOLOR_ARGB(wcontent_alpha, 255, 255, 255));

				Sprite.SpHd->Draw(Pictures.HP_bar_out, &rect1, NULL, &window_position, D3DCOLOR_ARGB(wout_alpha, 255, 255, 255));


				RECT rect3;
				rect3.top = 0;
				rect3.bottom = 70;
				rect3.left = 0;
				rect3.right = 150;

				RECT rect4;
				rect4.top = 0;
				rect4.bottom = 70;
				rect4.left = 0;

				if (Player.pMP > 0)
				{
					rect4.right = (12 + (float (Player.pMP) / Player.pMMP) * 125);
				}

				else
				{
					rect4.right = 0;
				}

				Sprite.SpHd->Draw(Pictures.MP_bar_in, &rect4, NULL, &window_position, D3DCOLOR_ARGB(wcontent_alpha, 255, 255, 255));

				Sprite.SpHd->Draw(Pictures.MP_bar_out, &rect3, NULL, &window_position, D3DCOLOR_ARGB(wout_alpha, 255, 255, 255));
			}
		}
	}
}

void Window::WBasic()
{
	if (Mouse.Button(wx + wwidth - 18, wx + wwidth - 5, wy + 5, wy + 18, wclose_status) == 2)
	{
		wclosing = 1;

		wbusy = 1;
	}
}

void Window::WStatic(int Alpha_Code)
{
	WAlpha_Sync(Alpha_Code);

	WOpen();

	if (wbusy == 0 && wtype != 0)
	{
		WBasic();										//0 for Normal Functions (Closing)
	}

	if (wbusy == 1)
	{
		WClose();
	}

	if (wbusy == 0 || wbusy == 2)						//2 For Moving
	{
		WDrag();										//0 for Normal Functions
	}

	if (wbusy == 0 || wbusy == 2)
	{
		WMove();
	}

	WPrimary();											//Always Perform Tasks. Further lockdown required.
}

void Window::WStatic_R(int Alpha_Code)
{
	WDraw(Alpha_Code);									//Always Draw
}


void Window::WReset()
{
	win_alpha = 0;
	wout_alpha = 0;
	wcontent_alpha = 0;

	wbusy = 0;
}

void Window::WMove()
{
	if (wmoving == 1)
	{
		wbusy = 2;

		if (wbin_alpha > 90)
		{
			if (win_alpha > 90)
			{
				win_alpha = win_alpha - 12;
			}
			
			if (win_alpha <= 90)
			{
				win_alpha = 90;
			}
		}

		if (wbout_alpha > 150)
		{
			if (wout_alpha > 150)
			{
				wout_alpha = wout_alpha - 20;
			}
			
			if (wout_alpha <= 150)
			{
				wout_alpha = 150;
			}
		}

		if (wbcontent_alpha > 120)
		{
			if (wcontent_alpha > 120)
			{
				wcontent_alpha = wcontent_alpha - 12;
			}
			
			if (wcontent_alpha <= 120)
			{
				wcontent_alpha = 120;
			}
		}
	}
	else if (wmoving == 2)
	{
		wbusy = 2;

		if (win_alpha < wbin_alpha)
		{
			win_alpha = win_alpha + 30;
		}
		if (win_alpha >= wbin_alpha)
		{
			win_alpha = wbin_alpha;
		}

		if (wout_alpha < wbout_alpha)
		{
			wout_alpha = wout_alpha + 45;
		}
		if (wout_alpha >= wbout_alpha)
		{
			wout_alpha = wbout_alpha;
		}

		if (wcontent_alpha < wbcontent_alpha)
		{
			wcontent_alpha = wcontent_alpha + 28;
		}
		if (wcontent_alpha >= wbcontent_alpha)
		{
			wcontent_alpha = wbcontent_alpha;
		}

		if (win_alpha == wbin_alpha && 
			wout_alpha == wbout_alpha && 
			wcontent_alpha == wbcontent_alpha)
		{
			wbusy = 0;

			wmoving = 0;
		}
	}
	else if (wmoving == 0)
	{
	}
}

void Window::WClose()
{
	if (wclosing == 1)
	{
		wbusy = 1;										//1 is for closing

		if (wout_alpha > 0)
		{
			wout_alpha = wout_alpha - 12;
		}

		if (wout_alpha <= 0)
		{
			wout_alpha = 0;
		}

		if (win_alpha > 0)
		{
			win_alpha = win_alpha - 12;
		}

		if (win_alpha <= 0)
		{
			win_alpha = 0;
		}

		if (wcontent_alpha > 0)
		{
			wcontent_alpha = wcontent_alpha - 20;
		}

		if (wcontent_alpha <= 0)
		{
			wcontent_alpha = 0;
		}

		if (win_alpha == 0 && wout_alpha == 0 && wcontent_alpha == 0)
		{
			wclosing = 2;
		}
	}
	else if (wclosing == 2)
	{
		wstatus = 0;
		wbusy = 0;

		wclosing = 0;

		WReset();
	}
	else if (wclosing == 0)
	{
	}
}

void Window::WOpen()
{
	if (wopening == 1)
	{
		wbusy = 3;

		if (win_alpha < wbin_alpha)
		{
			win_alpha = win_alpha + 33;
		}
		if (win_alpha >= wbin_alpha)
		{
			win_alpha = wbin_alpha;
		}

		if (wout_alpha < wbout_alpha)
		{
			wout_alpha = wout_alpha + 40;
		}
		if (wout_alpha >= wbout_alpha)
		{
			wout_alpha = wbout_alpha;
		}

		if (wcontent_alpha < wbcontent_alpha)
		{
			wcontent_alpha = wcontent_alpha + 24;
		}
		if (wcontent_alpha >= wbcontent_alpha)
		{
			wcontent_alpha = wbcontent_alpha;
		}

		if (win_alpha == wbin_alpha && 
			wout_alpha == wbout_alpha && 
			wcontent_alpha == wbcontent_alpha)
		{
			wbusy = 0;

			wopening = 0;
		}
	}
	else if (wopening == 2)
	{
	}
	else if (wopening == 0)
	{
	}
}

void Window::WVector_Check()
{
	if (wstatus == 1 && wactive == 1)
	{
		Wit = WVector.begin();
		WVector.insert(Wit, this);

		wactive = 0;
	}
}

void Window::WMove_To_Front()
{
	if (WVector[0] == this)
	{
		WVector.erase(WVector.begin() + 0);
		Wit = WVector.begin();
		WVector.insert(Wit, this);
	}

	else if (WVector[1] == this)
	{
		WVector.erase(WVector.begin() + 1);
		Wit = WVector.begin();
		WVector.insert(Wit, this);
	}

	else if (WVector[2] == this)
	{
		WVector.erase(WVector.begin() + 2);
		Wit = WVector.begin();
		WVector.insert(Wit, this);
	}

	else if (WVector[3] == this)
	{
		WVector.erase(WVector.begin() + 2);
		Wit = WVector.begin();
		WVector.insert(Wit, this);
	}

	else if (WVector[4] == this)
	{
		WVector.erase(WVector.begin() + 2);
		Wit = WVector.begin();
		WVector.insert(Wit, this);
	}

	else if (WVector[5] == this)
	{
		WVector.erase(WVector.begin() + 2);
		Wit = WVector.begin();
		WVector.insert(Wit, this);
	}

	else if (WVector[6] == this)
	{
		WVector.erase(WVector.begin() + 2);
		Wit = WVector.begin();
		WVector.insert(Wit, this);
	}

	else if (WVector[7] == this)
	{
		WVector.erase(WVector.begin() + 2);
		Wit = WVector.begin();
		WVector.insert(Wit, this);
	}

	else if (WVector[8] == this)
	{
		WVector.erase(WVector.begin() + 2);
		Wit = WVector.begin();
		WVector.insert(Wit, this);
	}

	else if (WVector[9] == this)
	{
		WVector.erase(WVector.begin() + 2);
		Wit = WVector.begin();
		WVector.insert(Wit, this);
	}
}

void Window::WMouse_Check()
{
	if (b_mouse_state.lX > (wx) 
		&& b_mouse_state.lX < (wx + wwidth)
		&& b_mouse_state.lY < (wy + wheight)
		&& b_mouse_state.lY > (wy)
		&& Mouse_Button(0)
		&& Mouse.Busy() == 0
		&& wclose_status == 0)
	{
		wdet_tick = 1;
	}

	if (wdet_tick == 1 && Mouse_Button(0) && wlock_active == 1)
	{
		if (wtop == 0)
		{
			WMove_To_Front();
			wtop = 1;
			wlock_active = 0;
		}
	}
	else
	{
		wdet_tick = 0;
		wtop = 0;
	}
}

void Window::WPrimary()									//To lock something, please use wclosing/wopening/etc
{
	if (wtype == 0)
	{
		if (Mouse.Button(wx + 16, wx + 38, wy + 35, wy + 55, wbutton_status1) == 2 && wlock == 1 && QW.wstatus == 0)
		{
			QW.wopening = 1;

			QW.wstatus = 1;

			QW.wactive = 1;

			wlock = 0;				//Lock Windows
		}

		if (Mouse.Button(wx + 54, wx + 76, wy + 35, wy + 55, wbutton_status2) == 2 && wlock == 1 && HM.wstatus == 0)
		{
			HM.wopening = 1;

			HM.wstatus = 1;

			HM.wactive = 1;

			wlock = 0;				//Lock Windows
		}
	}

	if (wtype == 2)
	{
		if (wstatus == 1)
		{
		}
	}
}

void Window::WAlpha_Sync(int Alpha_Code)					//1 == Top, 2 == Not Top
{
	short int alpha_add = 20;								//Robust adding variable. Change freely.

	if (Alpha_Code == 1)									//Increase the maximum alpha of windows
	{
		if (woin_alpha + alpha_add > 255)
		{
			wbin_alpha = 255;
		}
		else if (woin_alpha + alpha_add < 255)
		{
			wbin_alpha = woin_alpha + alpha_add;
		}

		if (woout_alpha + alpha_add > 255)
		{
			wbout_alpha = 255;
		}
		else if (woout_alpha + alpha_add < 255)
		{
			wbout_alpha = woout_alpha + alpha_add;
		}

		if (wocontent_alpha + alpha_add > 255)
		{
			wbcontent_alpha = 255;
		}
		else if (wocontent_alpha + alpha_add < 255)
		{
			wbcontent_alpha = wocontent_alpha + alpha_add;
		}
	}

	else if (Alpha_Code == 0)										//Keep original alpha
	{
		wbin_alpha = woin_alpha;

		wbout_alpha = woout_alpha;

		wbcontent_alpha = wocontent_alpha;
	}
}