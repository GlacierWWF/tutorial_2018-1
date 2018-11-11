#include "Lifefood.h"

void Lifefood::Display()  
{  
	
    COLORREF fill_color_save = getfillcolor();  
    COLORREF color_save = getcolor(); 
	setfillcolor(m_color);  
    setcolor(m_color);  

	fillrectangle(m_pos.GetX()-5,m_pos.GetY()-5,m_pos.GetX()+5,m_pos.GetY()+5);

    setcolor(color_save);  
    setfillcolor(fill_color_save);  
}  
void Lifefood::CalculateSphere()  
{  
	m_rectSphere.Set(m_pos.GetX()-20,m_pos.GetY()-20,m_pos.GetX()+20,m_pos.GetY()+20); 
}  
void Lifefood::Newfood() {  
    m_pos.Set((rand() % Graphic::GetBattleGround().GetWidth()),
			((rand() % Graphic::GetBattleGround().GetHeight())+200));  
    CalculateSphere();
}
void Lifefood::Boom(list<Object*>& lstBombs){}
void Lifefood::Move(){}