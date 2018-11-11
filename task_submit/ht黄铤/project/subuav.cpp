#include "subuav.h"


		;

void subuav::SetDir(Dir dir)
{
	m_dir = dir;
}

void subuav::DrawTankBody()
{
	setfillcolor(RGB(50,90,50));
	fillrectangle(m_pos.GetX()-3, m_pos.GetY()-2.5, m_pos.GetX()+3,m_pos.GetY()+2.5);
}

	void subuav::Display()
{
	COLORREF fill_color_save = getfillcolor();
	COLORREF color_save = getcolor();

	setfillcolor(m_color);
	setcolor(m_color);

	DrawTankBody();
		setcolor(color_save);
	setfillcolor(fill_color_save);
}

	void subuav::Move()
{
	switch (m_dir)
	{
	case UP:
		m_pos.SetY(m_pos.GetY() - m_step);
		if (m_rectSphere.GetStartPoint().GetY() < Graphic::GetBattleGround().GetStartPoint().GetY())
			m_pos.SetY(m_pos.GetY() + m_step);
		break;
	case DOWN:
		m_pos.SetY(m_pos.GetY() + m_step);
		if (m_rectSphere.GetEndPoint().GetY() > Graphic::GetBattleGround().GetEndPoint().GetY())
			m_pos.SetY(m_pos.GetY() - m_step);
		break;
	case LEFT:
		m_pos.SetX(m_pos.GetX() - m_step);
		if (m_rectSphere.GetStartPoint().GetX() < Graphic::GetBattleGround().GetStartPoint().GetX())
			m_pos.SetX(m_pos.GetX() + m_step);
		break;
	case RIGHT:
		m_pos.SetX(m_pos.GetX() + m_step);
		if (m_rectSphere.GetEndPoint().GetX() > Graphic::GetBattleGround().GetEndPoint().GetX())
			m_pos.SetX(m_pos.GetX() - m_step);
		break;
	default:
		break;
	}

	CalculateSphere();
}

void subuav::CalculateSphere()
{
	switch (m_dir)
	{
	case UP:
	case DOWN:
		m_rectSphere.Set(m_pos.GetX() -3, m_pos.GetY() - 3, m_pos.GetX() + 3, m_pos.GetY() + 3);
		break;
	case LEFT:
	case RIGHT:
		m_rectSphere.Set(m_pos.GetX() - 3, m_pos.GetY() - 3, m_pos.GetX() + 3, m_pos.GetY() + 3);
		break;
	default:
		break;
	}
}


void subuav::Boom(list<Object*>& lstBombs)
{
	//lstBombs.push_back(new Bomb(m_pos, LARGE));
}
