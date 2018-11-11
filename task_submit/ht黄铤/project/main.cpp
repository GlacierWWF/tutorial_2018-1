#pragma warning(disable:4996)

#include <iostream>
#include <conio.h>
#include <time.h>

#include <list>

#include "Graphic.h"
#include "Mainuav.h"
#include "Enemy.h"
#include "Utils/Shape.h"
#include"subuav.h"
#include"Level.h"
#include"EnemyQueue.h"
#include"Lifefood.h"
#include"arf_model.h"
using namespace std;

#define MAX_TANKS 3
    //list<Object*> lstMainTankBullets;// Bullet list
    list<Object*> lstBombs;// Bomb List
    list<Tank*> lstTanks;// Tank list
   // list<Object*>lstBullets;
//    list<EnemyTank*>lstEnemyTanks;
	Lifefood lifefood;	//道具1
    MainTank mainTank;//,mainTank2;//两个主坦克;//主飞机
	subuav sub1,sub2(10,554),sub3(200,554);//初始化子飞机位置
	Lifefood lifefood1(30,40),lifefood2(110,40),lifefood3(190,40),lifefood4(270,40);//4个密码箱
	EnemyTank enemy1(3,360),enemy2(3,260),enemy3(296,260),enemy4(296,360);//初始化敌人位置
//static int m_Life=3;

void CheckCrash()
{
			if (Shape::CheckIntersect(sub1.GetSphere(),enemy1.GetSphere())||
				Shape::CheckIntersect(sub1.GetSphere(),enemy2.GetSphere())||
				Shape::CheckIntersect(sub1.GetSphere(),enemy3.GetSphere())||
				Shape::CheckIntersect(sub1.GetSphere(),enemy3.GetSphere())
				)
				sub1.SetDir(DOWN);
			if (Shape::CheckIntersect(sub2.GetSphere(),enemy1.GetSphere())||
				Shape::CheckIntersect(sub2.GetSphere(),enemy2.GetSphere())||
				Shape::CheckIntersect(sub2.GetSphere(),enemy3.GetSphere())||
				Shape::CheckIntersect(sub2.GetSphere(),enemy3.GetSphere())
				)
				sub2.SetDir(DOWN);
			if (Shape::CheckIntersect(sub3.GetSphere(),enemy1.GetSphere())||
				Shape::CheckIntersect(sub3.GetSphere(),enemy2.GetSphere())||
				Shape::CheckIntersect(sub3.GetSphere(),enemy3.GetSphere())||
				Shape::CheckIntersect(sub3.GetSphere(),enemy3.GetSphere())
				)
				sub3.SetDir(DOWN);
}



//xin
void Begin()
{
	srand((unsigned)time(NULL));
	Graphic::Create();
	lstTanks.clear();

}

void End()
{
	for (list<Tank*>::iterator it = lstTanks.begin(); it != lstTanks.end(); it++)
	{
		delete *it;
	}
	lstTanks.clear();

	

	for (list<Object*>::iterator it = lstBombs.begin(); it != lstBombs.end(); it++)
	{
		delete *it;
	}
	lstBombs.clear();

	Graphic::Destroy();
}

void Draw()
{
//使用display替代
		}

void Approch1()
{
	if(enemy1.GetSphere().GetStartPoint().GetX()>=sub1.GetSphere().GetEndPoint().GetX())
		enemy1.SetDir(LEFT);
	if(enemy1.GetSphere().GetEndPoint().GetX()<=sub1.GetSphere().GetStartPoint().GetX())
		enemy1.SetDir(RIGHT);
	if(enemy2.GetSphere().GetStartPoint().GetX()>=sub2.GetSphere().GetEndPoint().GetX())
		enemy2.SetDir(LEFT);
	if(enemy2.GetSphere().GetEndPoint().GetX()<=sub2.GetSphere().GetStartPoint().GetX())
		enemy2.SetDir(RIGHT);
	if(enemy3.GetSphere().GetStartPoint().GetX()>=sub3.GetSphere().GetEndPoint().GetX())
		enemy3.SetDir(LEFT);
	if(enemy3.GetSphere().GetEndPoint().GetX()<=sub3.GetSphere().GetStartPoint().GetX())
		enemy3.SetDir(RIGHT);
	if(enemy4.GetSphere().GetStartPoint().GetX()>=mainTank.GetSphere().GetEndPoint().GetX())
		enemy4.SetDir(LEFT);
	if(enemy4.GetSphere().GetEndPoint().GetX()<=mainTank.GetSphere().GetStartPoint().GetX())
		enemy4.SetDir(RIGHT);
}
void Approch2()
{
	if(enemy1.GetSphere().GetStartPoint().GetY()>=sub1.GetSphere().GetEndPoint().GetY())
		enemy1.SetDir(UP);
	if(enemy1.GetSphere().GetEndPoint().GetY()<=sub1.GetSphere().GetStartPoint().GetY())
		enemy1.SetDir(DOWN);
	if(enemy2.GetSphere().GetStartPoint().GetY()>=sub2.GetSphere().GetEndPoint().GetY())
		enemy2.SetDir(UP);
	if(enemy2.GetSphere().GetEndPoint().GetY()<=sub2.GetSphere().GetStartPoint().GetY())
		enemy2.SetDir(DOWN);
	if(enemy3.GetSphere().GetStartPoint().GetY()>=sub3.GetSphere().GetEndPoint().GetY())
		enemy3.SetDir(UP);
	if(enemy3.GetSphere().GetEndPoint().GetY()<=sub3.GetSphere().GetStartPoint().GetY())
		enemy3.SetDir(DOWN);
	if(enemy4.GetSphere().GetStartPoint().GetY()>=mainTank.GetSphere().GetEndPoint().GetY())
		enemy4.SetDir(UP);
	if(enemy4.GetSphere().GetEndPoint().GetY()<=mainTank.GetSphere().GetStartPoint().GetY())
		enemy4.SetDir(DOWN);
}

void Action()
{


	mainTank.Move();
	sub1.Move();
	sub2.Move();
	sub3.Move();
	mainTank.Display();
	sub1.Display();
	sub2.Display();
	sub3.Display();
	lifefood1.Display();
	lifefood2.Display();
	lifefood3.Display();
	lifefood4.Display();
	enemy1.Move();
	enemy2.Move();
	enemy3.Move();
	enemy4.Move();
	enemy1.Display();
        enemy2.Display();
	enemy3.Display();
	enemy4.Display();
	lifefood.CalculateSphere();
	lifefood2.CalculateSphere();

	if(Shape::CheckIntersect(lifefood.GetSphere(),mainTank.GetSphere()))
	{
		Level::Lifebuff();
		lifefood.Newfood();
	}

	if(Shape::CheckIntersect(lifefood2.GetSphere(),mainTank.GetSphere()))
	{
		for (list<Tank*>::iterator it = lstTanks.begin(); it != lstTanks.end(); it++)
		{
           // (*it)->SetDisappear();
		}
		//lifefood2.Newfood();
	}
		for (list<Tank*>::iterator it = lstTanks.begin(); it != lstTanks.end();)
			{
				(*it)->Move();
				(*it)->Fire((*it)->GetSphere(),mainTank.GetSphere());
//				(*it)->Fire((*it)->GetSphere(),mainTank2.GetSphere());

				if((*it)->NeedShoot()==true)
				{
					EnemyTank*p=(EnemyTank*)*it;
//					p->Shoot(lstBullets);
				}

				if ((*it)->IsDisappear())
				{
					// Add a bomb
					(*it)->Boom(lstBombs);

					// Delete the tank
					delete *it;
					it = lstTanks.erase(it);
					continue;
				}

				(*it)->Display();

				it++;
			}
	
}

void KeyEvent()
{


	}
			 
bool loop = true;
bool skip = false;
bool ii=true;
void main()
{

	Begin();  
	enemy1.SetDir(RIGHT);
	enemy2.SetDir(DOWN);
	enemy3.SetDir(LEFT);
	enemy4.SetDir(UP);
	while (loop)
	{
		if (kbhit())  // 检测是否有按键按下
		{
			int key = getch();
			switch (key)
			{
			
			// Up
			case 72:
				mainTank.SetDir(Dir::UP);
				sub1.SetDir(Dir::UP);
				sub2.SetDir(Dir::UP);
				sub3.SetDir(Dir::UP);
				break;
			// Down
			case 80: 
				mainTank.SetDir(Dir::DOWN);
				sub1.SetDir(Dir::DOWN);
				sub2.SetDir(Dir::DOWN);
				sub3.SetDir(Dir::DOWN);
				break;
			// Left
			case 75: 
				mainTank.SetDir(Dir::LEFT);
				sub1.SetDir(Dir::LEFT);
				sub2.SetDir(Dir::LEFT);
				sub3.SetDir(Dir::LEFT);
				break;
			// Right
			case 77: 
				mainTank.SetDir(Dir::RIGHT);
				sub1.SetDir(Dir::RIGHT);
				sub2.SetDir(Dir::RIGHT);
				sub3.SetDir(Dir::RIGHT);
				break;
			case 224: // 方向键高8位
				break;
			// Esc
			case 27:
				loop = false;
				break;
	
			case 13:
				if (skip)
					skip = false;
				else
					skip = true;
				break;
			default: 
				break;
			}
		}
		if (!skip)
		{
			cleardevice();
//			CheckCrash();
			Graphic::DrawBattleGround();
			
	        Action();
			Draw();
			}
		if(ii)
		{
			Approch1();
			ii=false;
		}
		else 
		{
			ii=true;
			Approch2();
		}
		CheckCrash();
		Sleep(100);
	}	
	End();
}
