#ifndef _WINDOW_H
#define _WINDOW_H 1

#include "CString"
#include <cstdlib>
#include <stdio.h>
#include <string>

using namespace std;

class Window
{
	public:
		Window(int Type,
			char* Name,
			int Width,
			int Height,
			int In_Alpha,
			int Out_Alpha,
			int Content_Alpha,
			int X,
			int Y,
			int Slider_On);

		~Window(){};

		static int wlock;								//For locking movement etc
		static int wlock_active;						//For locking bring fronts

		int wtype;

		char* wname;

		int wwidth;
		int wheight;

		int wstatus;

		int wmoving;
		int wclosing;
		int wopening;

		int win_alpha;									//Current Alpha
		int wout_alpha;
		int wcontent_alpha;

		int wbin_alpha;									//Maximun Alpha
		int wbout_alpha;
		int wbcontent_alpha;

		int woin_alpha;									//Original Unchangable Alpha
		int woout_alpha;
		int wocontent_alpha;

		int wbutton_status1;							//Universal button variables. 0 == Off, 1 == On
		int wbutton_status2;
		int wbutton_status3;
		int wbutton_status4;
		int wbutton_status5;
		int wbutton_status6;

		int wx;
		int wy;

		int wdrag_tick;

		int wdet_tick;									//For safety check of Window if the mouse button has not already been pressed

		int wclose_status;

		int wslider;

		int wbusy;

		int wactive;									//If the window has already been opened...

		int wtop;										//Is the window on the top?

		LPDIRECT3DTEXTURE9 wtexture_in;
		LPDIRECT3DTEXTURE9 wtexture_out;

		void WSet_Texture(LPDIRECT3DTEXTURE9 Texture1, LPDIRECT3DTEXTURE9 Texture2);

		void WDraw(int Top_Status);				//1 == Top, 0 == Not Top

		void WDrag();

		void WPrimary();

		void WStatic(int Alpha_Code);			//1 == Top, 0 == Not Top
		void WStatic_R(int Alpha_Code);			//1 == Top, 0 == Not Top

		void WBasic();

		void WReset();

		void WClose();

		void WMove();

		void WOpen();

		void WMouse_Check();					//Checks if the mouse has clicked a Window

		void WVector_Check();					//Checks wstatus and inserts to vector if opened if opened

		void WMove_To_Front();					//Deletes part in vector and inserts to top

		void WAlpha_Sync(int Alpha_Code);		//Make sure the maximum alpha is right according to position in the vector
												//1 == Top, 0 == Not Top
};

#endif			//90