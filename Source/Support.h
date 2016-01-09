#ifndef _SUPPORT_H
#define _SUPPORT_H 1

#include "CString"
#include <cstdlib>
#include <stdio.h>
#include <string>

using namespace std;

class Support
{
	public:

	char* String_Convert(string str);								//Convert string to char*
	string String_Combine(char* string1, char* string2);			//Convert char* to string and combine

	~Support(){};
};

#endif