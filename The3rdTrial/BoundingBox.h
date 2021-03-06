#pragma once
#include <cmath> // for SweptAABB
#include <algorithm> // for SweptAABB
#include <limits> // for SweptAABB
#include <iostream>
#include "Rect.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>


class BoundingBox
{
private:
	float upperLeftCornerX;
	float upperLeftCornerY;
	float height;
	float width;
	bool ignoreCollision;
	//Rect box;
	Rect position;
	ALLEGRO_COLOR color;
public:
	BoundingBox(float x,float y,float width,float height,bool ignoreCollision);
	~BoundingBox(void);

	//void init(float x,float y,float width,float height,float velX,float velY);

	bool overlapsWith(BoundingBox& OtherBox);
	bool rectTouch(Rect box1 , Rect box2);
	bool rectOverlap(Rect box1 , Rect box2);
	bool valueInRange(float value, float min, float max);

	bool hasVerticalCollision(Rect box1 , Rect box2);
	bool hasHorizontalCollision(Rect box1 , Rect box2);

	void setX(float x);
	void setY(float y); 

	//float getX() const {return position.x;}
	//float getY() const {return position.y;}
	//float getWidth() {return position.w;}
	//float getHeight() {return position.h;}

	float getX() const;
	float getY() const;
	float getWidth() const;
	float getHeight() const;


	// performs collision detection on moving box b1 and static box b2
	// returns the time that the collision occured (where 0 is the start of the movement and 1 is the destination)
	// getting the new position can be retrieved by box.x = box.x + box.vx * collisiontime
	// normalx and normaly return the normal of the collided surface (this can be used to do a response)
	//float sweptAABB(Rect box1, Rect box2, float& normalx, float& normaly);

	//will draw the grid of entire map if toggleGrid funciont is on
	void draw() const;

	Rect getTop();
	Rect getBottom();
	Rect getLeft();
	Rect getRight();

	
	Rect getSweptBroadPhaseBox(Rect box);



	//bool valueInRange(int value, int min, int max);
	//bool rectOverlap(Rect A , Rect B);
};

