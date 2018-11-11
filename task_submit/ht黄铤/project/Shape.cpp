#include "Shape.h"

bool Shape::CheckIntersect(Rect&r1,Rect&r2)
{
	if(((r1.GetStartPoint().GetX()>=r2.GetStartPoint().GetX())&&
		(r1.GetStartPoint().GetX()<=r2.GetEndPoint().GetX()))||
		((r1.GetEndPoint().GetX()>=r2.GetStartPoint().GetX())&&
		(r1.GetEndPoint().GetX()<=r2.GetEndPoint().GetX())))
	{
		if(((r1.GetStartPoint().GetY()>=r2.GetStartPoint().GetY())&&
			(r1.GetStartPoint().GetY()<=r2.GetEndPoint().GetY()))||
		    ((r1.GetEndPoint().GetY()>=r2.GetStartPoint().GetY())&&
		    (r1.GetEndPoint().GetY()<=r2.GetEndPoint().GetY()))
		)
		
		return true;
	else
		return false;
	}
}

/*&&(r1.GetStartPoint().GetY()>=r2.GetEndPoint().GetY())&&(r1.GetStartPoint().GetY()<=r2.GetStartPoint().GetY()))
		||
		((r1.GetEndPoint().GetX()>=r2.GetStartPoint().GetX())&&(r1.GetEndPoint().GetX()<=r2.GetEndPoint().GetX())
		&&(r1.GetEndPoint().GetY()>=r2.GetEndPoint().GetY())&&(r1.GetEndPoint().GetY()<=r2.GetStartPoint().GetY()))
	  )*/

/*bool Shape::CheckPointInRect(Point& point, Rect& rect)
{
	if (point.GetX() < rect.GetStartPoint().GetX() || point.GetX() > rect.GetEndPoint().GetX() ||
		point.GetY() < rect.GetStartPoint().GetY() || point.GetY() > rect.GetEndPoint().GetY())
	{
		return false;
	}
	else
	{
		return true;
	}
}

bool Shape::CheckIntersect(Rect& rectA, Rect& rectB)
{
	if (CheckPointInRect(rectA.GetStartPoint(), rectB) ||
		CheckPointInRect(rectA.GetEndPoint(), rectB) ||
		CheckPointInRect(rectA.GetTRPoint(), rectB) ||
		CheckPointInRect(rectA.GetBLPoint(), rectB))
	{
		return true;
	}
	else
	{
		return false;
	}

}*/
