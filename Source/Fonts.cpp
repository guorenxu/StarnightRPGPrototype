#include <d3d9.h>
#include <d3dx9.h>
#include "DXGraphics.h"

#include "Fonts.h"

Font Main_Font(48, 255, 1);
Font HUD_Font(32, 255, 1);

Font::Font(int Size, int Alpha, int Type)
{
	fb_alpha = Alpha;
	f_alpha = Alpha;
	fo_alpha = Alpha;

	fsize = Size;

	ftype = Type;
}

void Font::Prepare()
{
	if (ftype == 1)
	{
		D3DXCreateFont(											//Create Font
			d3ddev,
			fsize,
			0, 
			FW_BOLD,
			0, 
			FALSE, 
			DEFAULT_CHARSET,
			OUT_DEFAULT_PRECIS, 
			DEFAULT_QUALITY,
			DEFAULT_PITCH | FF_DONTCARE,
			TEXT("Arial"),
			&ffont);
	}
}

void Font::Draw(int Alpha,
				int R,
				int G,
				int B,
				int LF,
				int TP,
				int BM,
				int RT,
				char* String,
				int Draw_Number,
				int Style)
{
	RECT rect;

	rect.top = TP;
	rect.bottom = BM;
	rect.right = RT;
	rect.bottom = LF;

	if (Style == 1)
	{
		ffont->DrawText(
			NULL, 
			String, 
			Draw_Number, 
			&rect, 
			DT_CENTER, 
			D3DCOLOR_ARGB(Alpha, R, G, B));
	}
	else if (Style == 2)
	{
		ffont->DrawText(
			NULL, 
			String, 
			Draw_Number, 
			&rect, 
			DT_LEFT, 
			D3DCOLOR_ARGB(Alpha, R, G, B));
	}
}