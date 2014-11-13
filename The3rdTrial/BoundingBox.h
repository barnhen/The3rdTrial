#pragma once
#include <cmath> // for SweptAABB
#include <algorithm> // for SweptAABB
#include <limits> // for SweptAABB
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
	bool rectTouch(Rect box1 , Rect box2);
	bool rectOverlap(Rect box1 , Rect box2);
	bool valueInRange(int value, int min, int max);

	bool hasVerticalCollision(Rect box1 , Rect box2);
	bool hasHorizontalCollision(Rect box1 , Rect box2);

	// performs collision detection on moving box b1 and static box b2
	// returns the time that the collision occured (where 0 is the start of the movement and 1 is the destination)
	// getting the new position can be retrieved by box.x = box.x + box.vx * collisiontime
	// normalx and normaly return the normal of the collided surface (this can be used to do a response)
	float sweptAABB(Rect box1, Rect box2, float& normalx, float& normaly);

	Rect getTop();
	Rect getBottom();
	Rect getLeft();
	Rect getRight();

	
	Rect getSweptBroadPhaseBox(Rect box);



	//bool valueInRange(int value, int min, int max);
	//bool rectOverlap(Rect A , Rect B);
};

