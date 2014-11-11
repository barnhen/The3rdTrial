#pragma once
#include "Rect.h"

class BoundingBox
{
private:
	float upperLeftCornerX;
	float upperLeftCornerY;
	float height;
	float width;
public:
	BoundingBox(void);
	~BoundingBox(void);

	void init(float x,float y,float width,float height,float velX,float velY);

	bool overlapsWith(BoundingBox& OtherBox);
	bool rectTouch(Rect A , Rect B);
	bool rectOverlap(Rect A , Rect B);
	bool valueInRange(int value, int min, int max);

	bool hasVerticalCollision(Rect A , Rect B);
	bool hasHorizontalCollision(Rect A , Rect B);

	Rect getTop();
	Rect getBottom();
	Rect getLeft();
	Rect getRight();


	//bool valueInRange(int value, int min, int max);
	//bool rectOverlap(Rect A , Rect B);
};

