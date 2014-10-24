#pragma once


#include "Player.h"


class Camera :public Player
{
private:
	float x;
	float y;
public:
	Camera(float x ,float y);
	~Camera(void);


	//void tick(Player *p);
	//void tick(Rect p1);
	//void update(Player &p1);
	void update();
	float getX();
	float getY();
};

