#pragma once
#include "GameObject.h"
#include "World.h"
#include "Player.h"
#include "Camera.h"
#include "Timer.h"
#include "GameState.h"

class Game
{
	//Timer               gameTimer;
	bool	isPaused;
protected:
	int state;

public:
	Game(void);
	~Game(void);
	double calcFPS();
	void showDebugMode(void);
	void initializeGameEngine();
	void shutdownGameEngine();
	void processGameEngine();
	void changeState(int &state, int newState);

};

