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
	float imageW, imageH;
	float x, y;
	Rect box;
	PhysicsComponent* charPhysics;
	int tileSize;
public:
	Character(ALLEGRO_BITMAP *pImg);
	~Character(void);

	void updatePhysics();

	void init(float x, float y, float width, float height);
	void handleInput(const ALLEGRO_EVENT& ev); //will handle keyboard events
	float getWidth(){return imageW;}
	float getHeight(){return imageH;}
	float getVelX(){return GameObject::velX;}
	float getVelY(){return GameObject::velY;}

};

