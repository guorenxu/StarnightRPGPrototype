#include <d3d9.h>
#include <d3dx9.h>

#include "Mouse.h"

Mice::Mice()
{
	mouse_busy = 0;
}

void Mice::Mouse_Loop()
{
	if (Mouse_Button(0))
	{
		mouse_busy = 1;
	}
	else
	{
		mouse_busy = 0;
	}
}

int Mice::Button(int XL, int XR, int YU, int YD, int& Status)
{
	if (b_mouse_state.lX >= XL &&
		b_mouse_state.lX <= XR &&
		b_mouse_state.lY >= YU &&
		b_mouse_state.lY <= YD)
	{
		if (Mouse_Button(0) && mouse_busy == 0)
		{
			Status = 1;
		}

		if (!Mouse_Button(0) && mouse_busy == 0 && Status == 1)		//The user lets go in target location
		{
			return 2;
		}
		else
		{
			return 1;
		}
	}
	else
	{
		Status = 0;

		return 0;
	}
}

int Mice::Busy()
{
	return mouse_busy;
}

void Mice::Mouse_Detect(int Left, int Top, int Right, int Bottom)
{
}

Mice Mouse;					//61