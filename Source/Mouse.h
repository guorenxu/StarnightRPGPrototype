#ifndef _MOUSE_H
#define _MOUSE_H 1

#include "CString"
#include <cstdlib>
#include <stdio.h>
#include <string>

#include "DXInput.h"

using namespace std;

class Mice
{
	public:

	Mice();

	int mouse_busy;

	void Mouse_Loop();												//Mouse Loop

	int Busy();

	void Mouse_Detect(int Left,										//Detection of Correct Rectangles
				  int Top, 
				  int Right, 
				  int Bottom);

	int Button(int XL, int XR, int YU, int YD, int& Status);

	~Mice(){};
};

#endif					//35