#include "BoundingBox.h"


BoundingBox::BoundingBox(void)
{
}


BoundingBox::~BoundingBox(void)
{
}

void BoundingBox::init(float x,float y,float width,float height)
{

}

bool BoundingBox::OverlapsWith(BoundingBox& OtherBox)
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


//bool BoundingBox::valueInRange(int value, int min, int max)
//{
//	return (value >= min) && (value <= max);
//}
//
//bool BoundingBox::rectOverlap(Rect A , Rect B)
//{
//	bool xOverlap = valueInRange(A.x ,B.x ,B.x + B.w) ||
//					valueInRange(B.x ,A.x  ,A.x + A.w);
//
//	bool yOverlap = valueInRange(A.y ,B.y ,B.y + B.w) ||
//					valueInRange(B.y ,A.y  ,A.y + A.w);
//
//	return xOverlap && yOverlap;
//}