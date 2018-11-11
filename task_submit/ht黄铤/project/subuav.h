#ifndef __SUB_TANK__
#define __SUB_TANK__

#include "Tank.h"

class subuav : public Tank
{
public:
	subuav() : Tank()
	{
		m_pos.Set(50,554);
	    m_dir = (Dir)(Dir::LEFT);
		this->CalculateSphere();
		m_color = RGB(100,90,200);;
		m_step = 2;
	}
	subuav(int x,int y)
	{
		m_pos.Set(x,y);
		m_color = RGB(100,90,200);
		m_dir = (Dir)(Dir::RIGHT);
		m_step = 2;
	}


	~subuav(){}

	Dir GetDir(){return m_dir;};
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