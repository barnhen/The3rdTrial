#pragma once
#include "GameObject.h"
#include <vector>
#include <fstream>

class World : public GameObject
{
	static const int tileSize = 50;
	std::vector<std::vector<int> > map;
	ALLEGRO_BITMAP *bgImg;
	ALLEGRO_BITMAP *tileImg;
	Rect camera;
	Rect blockrect;
	Rect destrect;
	World(World const&); // the trouble to return object instance	
	int inteiro;

public:
	World(ALLEGRO_BITMAP *bgSheet, char* filename, ALLEGRO_BITMAP *bgImage);
	World(void);
	~World(void);

	void showmap();
	void loadmap(const char* filename);
	//void Update(std::vector<std::vector<int> >& map);
	void update();
	void render();
	int getMapSize(){return tileSize * map[0].size();}
	int getTileSize(){return World::tileSize;}
	int getXVel(){return World::velX;}
	int getCoordX(){return World::coord.x;}
	int getDirX(){return World::dirX;}

	Rect getBlockRect(){return World::blockrect;}
	Rect getDestRect(){return World::destrect;}
	void setBlockRectY(int y);
	void setDestRectY(int y);

	//std::vector<std::vector<int> >& GetMap(){return map;}
	std::vector<std::vector<int> >& getMap() {return map;}
	int  getInt() {return inteiro;}

	//static background& GetInstance(){}; // the trouble to return object instance
	//rectangle GetRect(){return background::box;}

	// the trouble to return object instance
	static World& getInstance()
	{
		static World instance;
		return instance;
	}


};

