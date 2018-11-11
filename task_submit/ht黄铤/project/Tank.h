#ifndef __TANK_H__
#define __TANK_H__

#include "Object.h"
#include "Bomb.h"

#include <list>

using namespace std;

class Tank : public Object
{
public:
	Tank()
	{
		//m_pos.Set(300, 300);

		this->CalculateSphere();

		m_color = YELLOW;
		m_dir = Dir::UP;
		m_step ;

		m_bDisappear = false;
		m_bNeedShoot = false;
	}
	//xin

	void Fire(Rect &a,Rect &b)
{
	if((((a.GetStartPoint().GetX())<=((b.GetStartPoint().GetX()+b.GetEndPoint().GetX())/2.0))&&
		(((b.GetStartPoint().GetX()+b.GetEndPoint().GetX())/2.0)<=(a.GetEndPoint().GetX())))||
		((a.GetStartPoint().GetY())<=((b.GetStartPoint().GetY()+b.GetEndPoint().GetY())/2.0)&&
		(((b.GetStartPoint().GetY()+b.GetEndPoint().GetY())/2.0)<=(a.GetEndPoint().GetY()))))
		m_bNeedShoot=true;
}

	~Tank(){}

	void Display()
	{
		// Display
	}
	
	void Move()
	{
		// Move
	}

	void Boom(list<Object*>& lstBombs)
	{
		lstBombs.push_back(new Bomb(m_pos, LARGE));
	}

	// 射击
	void Shoot(list<Object*>& lstBullets)
	{
		// Shoot
	}

	void SetDisappear()
	{
		m_bDisappear = true;

	}

	bool IsDisappear()
	{
		return m_bDisappear;
	}
	
	Rect GetSphere()
	{
		return m_rectSphere;
	}

	bool NeedShoot()
	{
		return m_bNeedShoot;
	}

protected:
	void CalculateSphere()
	{
		// Calculate Sphere
	}

	bool m_bNeedShoot;
};

#endif