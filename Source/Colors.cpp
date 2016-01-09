#include <d3d9.h>
#include <d3dx9.h>

#include "Colors.h"


Rainbow Colors;

Rainbow::Rainbow()
{
	black = D3DCOLOR_XRGB(0, 0, 0);

	white = D3DCOLOR_XRGB(255, 255, 255);

	pink = D3DCOLOR_XRGB(255, 0, 255);
}