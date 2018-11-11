#ifndef __GRAPHIC_H__
#define __GRAPHIC_H__

#include <graphics.h>

#include "model/Rect.h"

#define SCREEN_WIDTH	310
#define SCREEN_HEIGHT	570

#define BATTLE_GROUND_X1 0
#define BATTLE_GROUND_Y1 0
#define BATTLE_GROUND_X2 300
#define BATTLE_GROUND_Y2 560//(SCREEN_HEIGHT - BATTLE_GROUND_Y1)
//#define SCORE_LEFT 1;
//#define SCORE_TOP 1;



class Graphic
{
public:
	
	static void Create();
	static void Destroy();

	static void DrawBattleGround();

	static int GetScreenWidth();
	static int GetScreenHeight();

	static Rect GetBattleGround();

	//static void Grade();
	static void ShowLevel(int nLevel){
	COLORREF fill_color_save = getfillcolor();
	COLORREF color_save = getcolor();
	LOGFONT fontBak;
	gettextstyle(&fontBak);           
	LOGFONT f = fontBak;
	f.lfHeight = 20;                  
	settextstyle(&f);                 
	wsprintf((LPWSTR)m_pArray, _T("MISSION %d "), nLevel);
	outtextxy(BATTLE_GROUND_X1 + 30, BATTLE_GROUND_Y1 + 250, (LPCTSTR)m_pArray);
	settextstyle(&fontBak);
	setcolor(color_save);
	setfillcolor(fill_color_save);
}

	

private:
	static Rect m_rectScreen;
	static Rect m_rectBattleGround;
	static char m_pArray[100];
};

#endif