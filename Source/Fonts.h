#ifndef _FONTS_H
#define _FONTS_H 1

#include "CString"
#include <cstdlib>
#include <stdio.h>
#include <string>

using namespace std;

class Font
{
	public:

	Font(int Size, int Alpha, int Type);

	~Font(){};

	void Prepare();								//Initialize Font

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
					int Style);

	LPD3DXFONT ffont;							//Font Holders

	int ftype;									//Font type, eg. Arial

	int fb_alpha;
	int f_alpha;
	int fo_alpha;

	int fsize;
};

#endif