#ifndef __ENEMY_TANK__
#define __ENEMY_TANK__

#include "Tank.h"

#define MAX_STEP_TURN	15
#define MAX_STEP_SHOOT	8
//const int maxqueue = 10;

//enum Error_code{success,underflow,overflow};

class EnemyTank : public Tank
{
public:
	EnemyTank()
	{
		RandomTank();
	}
	EnemyTank(int x,int y)
	{
		m_pos.Set(x,y);
		m_color = RGB(255,0,0);
		//m_dir = (Dir)(Dir::UP + (rand() % 4));
		m_step = 1.2;
		m_stepCnt = rand();
		m_crash=false;
	}

	~EnemyTank(){}

	void EnemyTank::SetDir(Dir dir)
{
	m_dir = dir;
}

	void Fire(Point &a,Point&b);

	void Display();
	void Move();
	void Shoot(list<Object*>& lstBullets);
	// Queue();    
    //  bool empty() const;    
    //  Error_code serve();    
    //  Error_code append(const EnemyTank &item);   
    //  Error_code retrieve(EnemyTank &item) const; 
	bool Crashed(){
		m_crash=true;return m_crash;
	}
	bool noCrash(){
		m_crash=false;return m_crash;
	}
	

protected:
	  

	void CalculateSphere();
	void RandomTank();
	// 随机产生坦克方向 type： 1, 新方向必须与之前方向不同 2, 任意一个新方向
	void RandomDir(int type);
    int m_stepCnt;
	bool m_crash;
};

#endif