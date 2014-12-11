#include "Tile.h"


Tile::Tile(float x, float y, float w, float h, int id)
	:GameObject(x,y,w,h,0,0)
{
	tileId = id;
	//typeId = TILE_TYPE_NONE;
	Tile::init(x,y,w,h,0,0);
}

Tile::~Tile()
{
}

void Tile::drawBoundingBox() const {
	boundingBox.draw();
}