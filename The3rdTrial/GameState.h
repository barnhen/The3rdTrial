#pragma once

class GameState
{
public:
	GameState(void);
	~GameState(void);
	enum state { TITLE, MENU ,PLAYING ,LOST,OPTIONS ,PAUSE ,LOADING, CREDITS };	

};