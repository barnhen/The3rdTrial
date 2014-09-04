#pragma once
#include "base.h"
#include "background.h"
#include "player.h"
class game
{
public:
	game(void);
	~game(void);
	void ShowDebugMode(void);
	void initializeGameEngine();
	void shutdownGameEngine();
	void processGameEngine();

};

