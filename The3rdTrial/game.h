#pragma once
#include "GameObject.h"
#include "World.h"
#include "Player.h"
#include "Camera.h"

class Game
{
public:
	Game(void);
	~Game(void);
	void showDebugMode(void);
	void initializeGameEngine();
	void shutdownGameEngine();
	void processGameEngine();

};

