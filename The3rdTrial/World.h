#pragma once
#include "GameObject.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <map>

enum COLLISION_TYPE{COLLIDE_NONE, COLLIDE_SOLID, COLLIDE_PLATFORM, COLLIDE_SLOPE};

class World : public GameObject
{
private:
	//static World* instance;
	//World(void);
	//Rect GameObject::coord;
	std::vector<std::vector<int> > map;
	ALLEGRO_BITMAP *bgImg;
	ALLEGRO_BITMAP *tileImg;
	ALLEGRO_BITMAP *tileSheet;

	Rect blockrect;
	Rect destrect;
	//World(World const&); // the trouble to return object instance	
	Rect tile;
	Rect posMap;
	//int mapX;
	//int mapY;
	static int start;
	static unsigned int end;
	//maping of the tiles and their collision type
	std::map<int,std::string> m_CollisionMap;
	std::vector<GameObject*> entities;

protected:
		static const int tileSize = 50;
public:
	//World(ALLEGRO_BITMAP *bgSheet, char* filename, ALLEGRO_BITMAP *bgImage);
	World(void);
	~World(void);
	
	void showmap();
	bool loadmap(const char* filename);
	//void Update(std::vector<std::vector<int> >& map);
	void update();
	void render();
	//int setStartMapBoundaries(Rect coordBox);
	//int setEndMapBoundaries(Rect coordBox);

	COLLISION_TYPE collisionLookup(int TileNum); //looks up the COLLISION_TYPE enum using the tile's number

	void setStartMapBoundaries(Rect coordinate);
	void setEndMapBoundaries(Rect coordinate);

	void addEntity(GameObject gameObject);

	int getStartMapBoundaries();
	int getEndMapBoundaries();
	int getMapSize(){return tileSize * map[0].size();}
	static int getTileSize(){return World::tileSize;}
	float getXVel(){return World::velX;}
	float getCoordX(){return coord.x;}
	int getDirX(){return World::dirX;}

	Rect getBlockRect(){return World::blockrect;}
	Rect getDestRect(){return World::destrect;}
	void setBlockRectY(int y);
	void setDestRectY(int y);
	void setMapPos(float& x, float& y);
	// will modify xVal and yVal variabes from PhysicsComponents
	void GetCurrentTileValues(float xPos, float yPos, int& xVal, int& yVal);

	//std::vector<std::vector<int> >& GetMap(){return map;}
	std::vector<std::vector<int> >& getMap() {return map;}

	Rect getTile(){return tile;}

	//static background& GetInstance(){}; // the trouble to return object instance
	//rectangle GetRect(){return background::box;}

	// the trouble to return object instance
	//static World& getInstance()
	//{
	//	static World instance;
	//	return instance;
	//}

	static World* getInstance();

};

