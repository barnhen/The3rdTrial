#pragma once

#include "GameObject.h"
#include "PhysicsComponent.h"

/*
##########################################################################################################
	This last value will be used only to set the enum max lenght when creating the array and nothing else.
##########################################################################################################
*/
enum KEYS{UP, DOWN, LEFT, RIGHT, SPACE, C,E,P,MAX_ENUM_LENGHT};

class Character : public GameObject
{
protected:
	bool keys[MAX_ENUM_LENGHT];
	bool visibleBoundingBox;
	float imageW, imageH;
	float x, y;
	float collisionTime;
	Rect box;
	PhysicsComponent* charPhysics;
	int tileSize;
	Rect topTileRect; // the tile that's directly above the char
	Rect bottomTileRect; // the tile that's directly below the char
	Rect middleLeftTileRect; // the tile that's middle left of the char
	Rect middleRightTileRect; // the tile that's middle right of the char
	Rect collisionRect; // the tile that's middle right of the char
public:
	Character(ALLEGRO_BITMAP *pImg);
	~Character(void);

	void updatePhysics();

	void init(float x, float y, float width, float height, float velX, float velY);
	void handleInput(const ALLEGRO_EVENT& ev); //will handle keyboard events

	float getWidth(){return imageW;}
	float getHeight(){return imageH;}
	float getVelX(){return GameObject::velX;}
	float getVelY(){return GameObject::velY;}

	float getCollisionTime(){return collisionTime;}

	bool isCharBoundingBoxVisible() {return visibleBoundingBox;}

	void setCollisionRect();
	void setBoundingBoxes();

	Rect getBottomTileRect() {return bottomTileRect;}
	Rect getTopTileRect() {return topTileRect;}
	Rect getMiddleLeftTileRect() {return middleLeftTileRect;}
	Rect getMiddleRightTileRect() {return middleRightTileRect;}
	Rect getCollisionRect() {return collisionRect;}
	

};

