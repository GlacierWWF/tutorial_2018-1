#pragma once

#include<list>
#include"Object.h"
#include"Graphic.h"
using namespace std;
class Lifefood:public Object
{
public:	
    Lifefood()
	{
		m_pos.Set(rand() %600,rand() %600+200);
		m_color = RGB((rand() %100),(rand() %200),(rand() %200));
		m_bDisappear = false;
	}
	Lifefood(int x,int y)
	{
		m_pos.Set(x,y);
		m_color = RGB((rand() %100),(rand() %200),(rand() %200));
		m_bDisappear = false;
	}

	void Display();
	void Boom(list<Object*>& lstBombs);
	void SetDisappear() { m_bDisappear = true; }
	bool IsDisappear() { return m_bDisappear; }
	Rect GetSphere() { return m_rectSphere; }
	void CalculateSphere();
	void Newfood();
	void Move();
};

//#endif




