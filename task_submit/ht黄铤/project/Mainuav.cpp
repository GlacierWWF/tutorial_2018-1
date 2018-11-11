#include "Mainuav.h"

#include "Bullet.h"


		;

void MainTank::SetDir(Dir dir)
{
	m_dir = dir;
}

void MainTank::DrawTankBody()
{
	setfillcolor(RGB(200,100,100));
	fillrectangle(m_pos.GetX()-9, m_pos.GetY()-9, m_pos.GetX()+9,m_pos.GetY()+9);

/*	switch (m_dir)
	{
		case UP:
			//setfillcolor(RGB(100,100,0));
			fillrectangle(m_pos.GetX()-16,m_pos.GetY()-16,m_pos.GetX()-12,m_pos.GetY()+16);
			fillrectangle(m_pos.GetX()+12,m_pos.GetY()-16,m_pos.GetX()+16,m_pos.GetY()+16);
			
			//fillrectangle(m_pos.Getx()-3,m_pos.Gety()-18,m_pos.Getx()+3,m_pos.Gety());
			break;
		case DOWN:
			//setfillcolor(RGB(100,100,0));
			fillrectangle(m_pos.GetX()-16,m_pos.GetY()-16,m_pos.GetX()-12,m_pos.GetY()+16);
			fillrectangle(m_pos.GetX()+12,m_pos.GetY()-16,m_pos.GetX()+16,m_pos.GetY()+16);
			
			//fillrectangle(m_pos.Getx()-3,m_pos.Gety(),m_pos.Getx()+3,m_pos.Gety()+18);
			break;
		case RIGHT:
			//setfillcolor(RGB(100,100,0));
			fillrectangle(m_pos.GetX()-16,m_pos.GetY()-16,m_pos.GetX()+16,m_pos.GetY()-12);
			fillrectangle(m_pos.GetX()-16,m_pos.GetY()+12,m_pos.GetX()+16,m_pos.GetY()+16);
			
			//fillrectangle(m_pos.Getx(),m_pos.Gety()-3,m_pos.Getx()+18,m_pos.Gety()+3);
			break;
		case LEFT:
			//setfillcolor(RGB(100,100,0));
			fillrectangle(m_pos.GetX()-16,m_pos.GetY()-16,m_pos.GetX()+16,m_pos.GetY()-12);
			fillrectangle(m_pos.GetX()-16,m_pos.GetY()+12,m_pos.GetX()+16,m_pos.GetY()+16);
			
			//fillrectangle(m_pos.Getx()-18,m_pos.Gety()-3,m_pos.Getx(),m_pos.Gety()+3);
			break;
		default:
			break;
		/*case UP:
	case DOWN:
		setfillcolor(RGB(100,100,0));
		fillrectangle(m_rectSphere.GetStartPoint().GetX(), m_rectSphere.GetStartPoint().GetY(),
			m_rectSphere.GetStartPoint().GetX() + 4, m_rectSphere.GetEndPoint().GetY());
		fillrectangle(m_rectSphere.GetEndPoint().GetX() - 4, m_rectSphere.GetStartPoint().GetY(),
			m_rectSphere.GetEndPoint().GetX(), m_rectSphere.GetEndPoint().GetY());
		break;
	case LEFT:
	case RIGHT:
		setfillcolor(RGB(100,100,0));
		fillrectangle(m_rectSphere.GetStartPoint().GetX(), m_rectSphere.GetStartPoint().GetY(),
			m_rectSphere.GetEndPoint().GetX(), m_rectSphere.GetStartPoint().GetY() + 4);
		fillrectangle(m_rectSphere.GetStartPoint().GetX(), m_rectSphere.GetEndPoint().GetY() - 4,
			m_rectSphere.GetEndPoint().GetX(), m_rectSphere.GetEndPoint().GetY());
		break;
	default:
		break;
	}*/
}

void MainTank::Display()
{
	COLORREF fill_color_save = getfillcolor();
	COLORREF color_save = getcolor();

	setfillcolor(m_color);
	setcolor(m_color);

	DrawTankBody();

/*	switch (m_dir)
	{
	case UP:
		setfillcolor(RGB(0,200,200));
		fillrectangle(m_pos.GetX()-3,m_pos.GetY()-18,m_pos.GetX()+3,m_pos.GetY());
		//line(m_pos.GetX(), m_pos.GetY(), m_pos.GetX(), m_pos.GetY() - 15);
		break;
	case DOWN:
		setfillcolor(RGB(0,200,200));
		fillrectangle(m_pos.GetX()-3,m_pos.GetY(),m_pos.GetX()+3,m_pos.GetY()+18);
		//line(m_pos.GetX(), m_pos.GetY(), m_pos.GetX(), m_pos.GetY() + 15);
		break;
	case LEFT:
		setfillcolor(RGB(0,200,200));
		fillrectangle(m_pos.GetX()-18,m_pos.GetY()-3,m_pos.GetX(),m_pos.GetY()+3);
		//line(m_pos.GetX(), m_pos.GetY(), m_pos.GetX() - 15, m_pos.GetY());
		break;
	case RIGHT:
		setfillcolor(RGB(0,200,200));
		fillrectangle(m_pos.GetX(),m_pos.GetY()-3,m_pos.GetX()+18,m_pos.GetY()+3);
		//line(m_pos.GetX(), m_pos.GetY(), m_pos.GetX() + 15, m_pos.GetY());
		break;
	default:
		break;
	}*/

	setcolor(color_save);
	setfillcolor(fill_color_save);
}

void MainTank::Move()
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

void MainTank::CalculateSphere()
{
	switch (m_dir)
	{
	case UP:
	case DOWN:
		m_rectSphere.Set(m_pos.GetX() - 9, m_pos.GetY() - 9, m_pos.GetX() + 9, m_pos.GetY() + 9);
		break;
	case LEFT:
	case RIGHT:
		m_rectSphere.Set(m_pos.GetX()-9, m_pos.GetY()-9, m_pos.GetX()+9, m_pos.GetY()+9);
		break;
	default:
		break;
	}
}

void MainTank::Shoot(list<Object*>& lstBullets)
{
	Bullet* pBullet = new Bullet(m_pos, m_dir, m_color);

	lstBullets.push_back(pBullet);
}

void MainTank::Boom(list<Object*>& lstBombs)
{
	//lstBombs.push_back(new Bomb(m_pos, LARGE));
}