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
	PhysicsComponent* charPhysics;
public:
	Character(ALLEGRO_BITMAP *pImg);
	~Character(void);

	void updatePhysics();

	void init();
	void handleInput(const ALLEGRO_EVENT& ev); //will handle keyboard events
	float getWidth(){return imageW;}
	float getHeight(){return imageH;}
	float getVelX(){return GameObject::velX;}
	float getVelY(){return GameObject::velY;}

};

