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

	void init(float x,float y,float width,float height);

	bool OverlapsWith(BoundingBox& OtherBox);

	//bool valueInRange(int value, int min, int max);
	//bool rectOverlap(Rect A , Rect B);
};

