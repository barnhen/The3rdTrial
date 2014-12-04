#pragma once
#include "Rect.h"
#include "GameObject.h"

//struct tile
//{
//	int ID;
//	float x;
//	float y;
//	int size;
//	int timer;
//	float xStart;
//	float yStart;
//	int level;
//};

enum
{
	TILE_TYPE_NONE = 0
	,TILE_TYPE_NORMAL
	,TILE_TYPE_BLOCK
};

class Tile : public GameObject
{
private:
	int tileId;
	unsigned int typeId;
	//Tiles(int id int x, int y);
public :
	//int typeId;
	Tile(float x, float y, float w, float h, int id);
	~Tile();

	//Tiles(int id, int x, int y);
	//inline Rect getBounds(){return Rect(x,y,50,50);}
	//inline Rect getTop(){return Rect(x +4,y,24,4);}
};

