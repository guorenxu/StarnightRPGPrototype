#ifndef _COLORS_H
#define _COLORS_H 1

#include "CString"
#include <cstdlib>
#include <stdio.h>
#include <string>

using namespace std;

class Rainbow
{
	public:

	D3DCOLOR white;										//Colors
	D3DCOLOR black;
	D3DCOLOR pink;

	Rainbow();

	~Rainbow(){};
};

#endif