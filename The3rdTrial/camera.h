#pragma once
#include "player.h"
class camera :
	public base
{
//private:
//	float x;
//	float y;
public:
	camera(void);
	~camera(void);
	void tick(player *p);
	float GetX();
	float GetY();
};

