#include "BoundingBox.h"


BoundingBox::BoundingBox(void)
{
}


BoundingBox::~BoundingBox(void)
{
}

void BoundingBox::init(float x,float y,float width,float height, float velX, float velY)
{

}

bool BoundingBox::overlapsWith(BoundingBox& OtherBox)
{
	//We don't intersect if...
	//our bottom is higher than their top
	if ( (upperLeftCornerY + height ) < OtherBox.upperLeftCornerY )
		return false;
	//our top is lower than their bottom
	else if ( (upperLeftCornerY) > (OtherBox.upperLeftCornerY + OtherBox.height) )
		return false;
	//our right is more left than their left
	else if ( (upperLeftCornerX + width) < OtherBox.upperLeftCornerX)
		return false;
	//our left is more right than their right 
	else if ( (upperLeftCornerX) > (OtherBox.upperLeftCornerX + OtherBox.width) )
		return false;

	//if we don't fail any of those tests then we're intersecting
	else 
		return true;

}


bool BoundingBox::valueInRange(int value, int min, int max)
{
	return (value >= min) && (value <= max);
}

bool BoundingBox::rectOverlap(Rect A , Rect B)
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

bool BoundingBox::rectTouch(Rect A , Rect B)
{
	bool xOverlap = valueInRange(A.x ,B.x ,B.x + B.w) ||
					valueInRange(B.x ,A.x  ,A.x + A.w);

	bool yOverlap = valueInRange(A.y ,B.y ,B.y + B.w) ||
					valueInRange(B.y ,A.y  ,A.y + A.w);

	return xOverlap && yOverlap;
}

bool BoundingBox::hasVerticalCollision(Rect A , Rect B)
{
	if ((A.y + A.h) >= B.y)
	{
		return true;
	}

}

bool BoundingBox::hasHorizontalCollision(Rect A , Rect B)
{

	if ((A.x + A.w) >= B.x)
	{
		return true;
	}

	if ((A.x + A.w) >= B.x)
	{
		return true;
	}
	return false;
	//for (int i = 0; i < world.getBlocks().size(); i++)
 //   {
 //       Block block = world.getBlocks().get(i);
 //       if (getRight().intersects(block.getRight()) && velX > 0)
 //       {
 //           return true;
 //       }
 //       if (getLeft().intersects(block.getLeft()) && velX < 0)
 //       {
 //           return true;
 //       }
 //   }
 //   return false;	
}
//
//Rect BoundingBox::getTop(){return false;}
//Rect BoundingBox::getBottom(){return false;}
//Rect BoundingBox::getLeft(){return false;}
//Rect BoundingBox::getRight(){return false;}


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
	