#include "Enemy.h"

#include "Bullet.h"

#include"Mainuav.h"

#include"Object.h"

void EnemyTank::RandomTank()
{
	m_pos.SetX(rand() % Graphic::GetBattleGround().GetWidth());
	m_pos.SetY(rand() % Graphic::GetBattleGround().GetHeight());
	m_color = RGB(0,200,20);
	m_dir = (Dir)(Dir::UP + (rand() % 4));
	m_step = 12;
	m_stepCnt = rand();
	m_crash=false;
}

void EnemyTank::RandomDir(int type)
{
	if (type == 1)
	{
		Dir dir;
		while ((dir = (Dir)(Dir::UP + (rand() % 4))) == m_dir)
		{
			// Do nothing
		}

		m_dir = dir;
	}
	else
	{
		m_dir = (Dir)(Dir::UP + (rand() % 4));
	}
}

void EnemyTank::Display()
{
	COLORREF fill_color_save = getfillcolor();
	COLORREF color_save = getcolor();

	setfillcolor(m_color);
	setcolor(m_color);
	
	fillrectangle(m_pos.GetX() - 3, m_pos.GetY() - 2.5, m_pos.GetX() + 3, m_pos.GetY() + 2.5);



	setcolor(color_save);
	setfillcolor(fill_color_save);
}

void EnemyTank::Move()
{
	switch (m_dir)
	{
	case UP:
		m_pos.SetY(m_pos.GetY() - m_step);
		if (m_rectSphere.GetStartPoint().GetY() < Graphic::GetBattleGround().GetStartPoint().GetY())
		{
			m_pos.SetY(m_pos.GetY() + m_step);
			//this->RandomDir(1);
		}
		break;
	case DOWN:
		m_pos.SetY(m_pos.GetY() + m_step);
		if (m_rectSphere.GetEndPoint().GetY() > Graphic::GetBattleGround().GetEndPoint().GetY())
		{
			m_pos.SetY(m_pos.GetY() - m_step);
			//this->RandomDir(1);
		}
		break;
	case LEFT:
		m_pos.SetX(m_pos.GetX() - m_step);
		if (m_rectSphere.GetStartPoint().GetX() < Graphic::GetBattleGround().GetStartPoint().GetX())
		{
			m_pos.SetX(m_pos.GetX() + m_step);
			//this->RandomDir(1);
		}
		break;
	case RIGHT:
		m_pos.SetX(m_pos.GetX() + m_step);
		if (m_rectSphere.GetEndPoint().GetX() > Graphic::GetBattleGround().GetEndPoint().GetX())
		{
			m_pos.SetX(m_pos.GetX() - m_step);
			//this->RandomDir(1);
		}
		break;
	default:
		break;
	}

	CalculateSphere();



	
}


void EnemyTank::CalculateSphere()
{
	switch (m_dir)
	{
	case UP:
	case DOWN:
		m_rectSphere.Set(m_pos.GetX() - 5, m_pos.GetY() - 5, m_pos.GetX() + 5, m_pos.GetY() + 5);
		break;
	case LEFT:
	case RIGHT:
		m_rectSphere.Set(m_pos.GetX() - 5, m_pos.GetY() - 5, m_pos.GetX() + 5, m_pos.GetY() + 5);
		break;
	default:
		break;
	}
}

void EnemyTank::Shoot(list<Object*>& lstBullets)
{
	Bullet* pBullet = new Bullet(m_pos, m_dir, m_color);

	lstBullets.push_back(pBullet);

	m_bNeedShoot = false;
}