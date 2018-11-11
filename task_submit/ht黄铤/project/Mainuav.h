#ifndef __MAIN_TANK__
#define __MAIN_TANK__

#include "Tank.h"

class MainTank : public Tank
{
public:
	MainTank() : Tank()
	{
		m_pos.Set((rand() % 600),550);
	    m_dir = (Dir)(Dir::UP + (rand() % 4));
		this->CalculateSphere();
		m_color = RGB(100,90,200);;
		m_step = 2;
	}

	~MainTank(){}

	void SetDir(Dir dir);
	void Display();
	void Move();
	void Shoot(list<Object*>& lstBullets);
	void Boom(list<Object*>& lstBombs);
    

protected:
	void CalculateSphere();

	// 绘制坦克主体
	void DrawTankBody();
};

#endif