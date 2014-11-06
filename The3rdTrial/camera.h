#pragma once


#include "GameObject.h"
#include "Character.h"


class Camera
{
private:
	float x;
	float y;
	float width;
	float height;

	Character *focusedChar;

	Rect position;
	Rect focus;

public:
	Camera(float x ,float y);
	Camera(void);
	~Camera(void);


	//void tick(Player *p);
	//void tick(Rect p1);
	//void update(Player &p1);
	void setSize(float width,float height);
	void setFocusedCharacter(Character* focusedChar);
	void setPosition(float x, float y);
    void setFocus(float fx, float fy);
	//void update(Player* p1);
	void update();
	float getX();
	float getY();
	Rect getPosition() const{return position;}

};

