#include "Graphic.h"
#include"Level.h"

Rect Graphic::m_rectScreen; 
Rect Graphic::m_rectBattleGround;
char Graphic::m_pArray[100];


void Graphic::Create()
{
	m_rectScreen.Set(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	initgraph(SCREEN_WIDTH, SCREEN_HEIGHT);
	setbkcolor(RGB(30,30,30));

	m_rectBattleGround.Set(BATTLE_GROUND_X1, BATTLE_GROUND_Y1, BATTLE_GROUND_X2, BATTLE_GROUND_Y2);
}

void Graphic::Destroy()
{
	closegraph();
}

void Graphic::DrawBattleGround()
{
	rectangle(m_rectBattleGround.GetStartPoint().GetX(), m_rectBattleGround.GetStartPoint().GetY(),
		m_rectBattleGround.GetEndPoint().GetX(), m_rectBattleGround.GetEndPoint().GetY());
}

int Graphic::GetScreenWidth()
{
	return SCREEN_WIDTH;
}

int Graphic::GetScreenHeight()
{
	return SCREEN_HEIGHT;
}

Rect Graphic::GetBattleGround()
{
	return m_rectBattleGround;
}

const int SCORE_LEFT=1 ;
const int SCORE_TOP=1;

/*void Graphic::Grade()
{
	COLORREF fill_color_save = getfillcolor();
    COLORREF color_save = getcolor();
	RECT rec = { SCORE_LEFT, SCORE_TOP, SCORE_LEFT +100, SCORE_TOP + 50 };
    wsprintf((LPWSTR)m_pArray, _T("MISSION %d "), Level::GetLevel());
    drawtext((LPCTSTR)m_pArray, &rec, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    rec.top += 25;
    rec.bottom += 25;
    wsprintf((LPWSTR)m_pArray, _T("SCORE  :  %d"), Level::GetScore());
    drawtext((LPCTSTR)m_pArray, &rec, DT_VCENTER | DT_SINGLELINE);
    rec.top += 25;
    rec.bottom += 25;
    wsprintf((LPWSTR)m_pArray, _T("LEVEL  :  %d"), Level::GetTankLevel());
    drawtext((LPCTSTR)m_pArray, &rec, DT_VCENTER | DT_SINGLELINE);
    rec.top += 25;
    rec.bottom += 25;
    wsprintf((LPWSTR)m_pArray, _T("LIFE  :  %d"), Level::GetLife());
    drawtext((LPCTSTR)m_pArray, &rec, DT_VCENTER | DT_SINGLELINE);
    rec.top += 25;
    rec.bottom += 25;
    wsprintf((LPWSTR)m_pArray, _T("ENEMY  :  %d"), Level::GetTankNum());
    drawtext((LPCTSTR)m_pArray, &rec, DT_VCENTER | DT_SINGLELINE);
    setcolor(color_save);
    setfillcolor(fill_color_save);
}
*/