#include "GameObject.h"


GameObject::GameObject(void)
{
}


GameObject::~GameObject(void)
{
}

void GameObject::init(float x ,float y ,float width, float height)
{
	x = 0;
	y = 0;
	height = 0;
	width = 0;
	dirX = 0;
	dirY = 0;
	boundingBox.init(x,y,width,height);

}


void GameObject::update()
{
	//rectangle.x += velX * dirX;
	//rectangle.y += velY * dirY;

}

void GameObject::render()
{

}


/**
 *Depreceated
 *
 *
 */
bool GameObject::collision (Rect* rec1, Rect* rec2)
{
	if (rec1->y >= rec2->y + rec2->h)
	{
		return false;
	}

	if (rec1->x >= rec2->x + rec2->w)
	{
		//std::cout<<"Right Collision"<<std::endl;
		return false;
	}
	
	if (rec1->y + rec1->h <= rec2->y)
	{
		return false;
	}

	if (rec1->x + rec1->w <= rec2->x)
	{
		//std::cout<<"Left Collision"<<std::endl;
		return false;
	}
	return true;
}

bool GameObject::valueInRange(int value, int min, int max)
{
	return (value >= min) && (value <= max);
}

bool GameObject::rectOverlap(Rect A , Rect B)
{
	if(A.x < B.x + B.w && 
	   A.x + A.w > B.x &&
	   A.y < B.y + B.h &&
	   A.y + A.h > B.y)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool GameObject::rectTouch(Rect A , Rect B)
{
	bool xOverlap = valueInRange(A.x ,B.x ,B.x + B.w) ||
					valueInRange(B.x ,A.x  ,A.x + A.w);

	bool yOverlap = valueInRange(A.y ,B.y ,B.y + B.w) ||
					valueInRange(B.y ,A.y  ,A.y + A.w);

	return xOverlap && yOverlap;
}

/**
* Determines whether or not this <code>Rectangle</code> and the specified
* <code>Rectangle</code> intersect. Two rectangles intersect if
* their intersection is nonempty.
*
* @param r the specified <code>Rectangle</code>
* @return    <code>true</code> if the specified <code>Rectangle</code>
*            and this <code>Rectangle</code> intersect;
*            <code>false</code> otherwise.
*/
//bool intersects(rectangle* s) 
//{
//	int tw = this.w;
//	int th = this.h;
//	int rw = s.w;
//	int rh = s.h;
//        
//	if (rw <= 0 || rh <= 0 || tw <= 0 || th <= 0) 
//	{
//		return false;
//	}
//	int tx = this.x;
//	int ty = this.y;
//	int rx = s.x;
//	int ry = s.y;
//	rw += rx;
//	rh += ry;
//	tw += tx;
//	th += ty;
//	//      overflow || intersect
//	return ((rw < rx || rw > tx) &&
//			(rh < ry || rh > ty) &&
//			(tw < tx || tw > rx) &&
//			(th < ty || th > ry));
//} //end boolean intersects
//
//
//
	