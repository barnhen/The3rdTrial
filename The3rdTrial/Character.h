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
	bool loaded;
	float imageW, imageH;
	float x, y;
	float collisionTime;
	float verticalSpeedLimit;
	float jumpingForce;
	Rect box;
	PhysicsComponent* charPhysics;
	int tileSize;
	Rect topTileRect; // the tile that's directly above the char
	Rect bottomTileRect; // the tile that's directly below the char
	Rect middleLeftTileRect; // the tile that's middle left of the char
	Rect middleRightTileRect; // the tile that's middle right of the char
	Rect collisionRect; // the tile that's middle right of the char
public:
	Character(float x, float y, float width, float height, float velX, float velY, float maxVelY, ALLEGRO_BITMAP *pImg);
	~Character(void);

	void update();
	void updatePhysics();

	//void init(float x, float y, float width, float height, float velX, float velY, float maxVelY);
	void init();
	void handleInput(const ALLEGRO_EVENT& ev); //will handle keyboard events

	float getWidth(){return box.w;}
	float getHeight(){return box.h;}
	//float getVelX(){return box.vX;}
	//float getVelY(){return box.vY;}
	float getSpeedX(){return box.x;}
	float getSpeedY(){return box.y;}


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

