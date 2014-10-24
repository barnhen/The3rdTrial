#pragma once
#include "GameObject.h"

class Mobile : public GameObject
{
public:
	Mobile(void);
	~Mobile(void);

	void update();
};

