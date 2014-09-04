#pragma once
#include "base.h"
#include <vector>
#include <fstream>
class background:public base
{
	static const int tileSize = 50;
	std::vector<std::vector<int> > map;
	ALLEGRO_BITMAP *bgImg;
	ALLEGRO_BITMAP *tileImg;
	sprite camera;
	sprite blockrect;
	sprite destrect;


public:
	//static box coord;//coord variable, store the absolute coordinate of the screen, so if I go a 1000px it will be a 1000px
	background(ALLEGRO_BITMAP *bgSheet, char* filename, ALLEGRO_BITMAP *bgImage);
	~background(void);
	void showmap();
	void loadmap(const char* filename);
	void Update(std::vector<std::vector<int> >& map);
	void Render();
	int GetMapSize(){return tileSize * map[0].size();}
	int GetTileSize(){return background::tileSize;}
	int GetXVel(){return background::velX;}
	int GetCoordX(){return background::coord.x;}
	int GetDirX(){return background::dirX;}

	sprite GetBlockRect(){return background::blockrect;}
	sprite GetDestRect(){return background::destrect;}
	void SetBlockRectY(int y);
	void SetDestRectY(int y);

	std::vector<std::vector<int> > GetMap(){return map;};
	//sprite GetRect(){return background::box;}




};

