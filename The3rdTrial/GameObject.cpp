#include "GameObject.h"


GameObject::GameObject(void)
{
}


GameObject::~GameObject(void)
{
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
	