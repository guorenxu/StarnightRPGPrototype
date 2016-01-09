#include <d3d9.h>
#include <d3dx9.h>

#include "Support.h"

string Support::String_Combine(char* string1, char* string2)
{
    string first(string1);
	string second(string2);
    string combined = first + second;

	return combined;
}

char* Support::String_Convert(string str)
{
	char *buf;
	buf = (char*)GlobalAlloc(GPTR, str.size());

	strcpy(buf, str.c_str());

	return buf;
}