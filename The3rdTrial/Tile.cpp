#include "Tile.h"


Tile::Tile(float x, float y, float w, float h, int id)
{
	tileId = 0;
	typeId = TILE_TYPE_NONE;
	Tile::init(x,y,w,h,0,0);
}

Tile::~Tile()
{
}