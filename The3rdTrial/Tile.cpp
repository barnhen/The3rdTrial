#include "Tile.h"


Tile::Tile(float x, float y, float w, float h, int id)
	:GameObject(x,y,w,h,0,0)
{
	tileId = id;
	//typeId = TILE_TYPE_NONE;
	//Tile::init(x,y,w,h,0,0);
}

Tile::~Tile()
{
}

void Tile::drawBoundingBox() const {
	boundingBox.draw();
}

//###############################################################################################################################
//###########################################2ND MAP STRATEGY BEGIN##############################################################
//###############################################################################################################################

//void Tile::isPassable(bool passable) 
//{ 
//	this->boundingBox.setIgnoreCollision(passable); 
//}
//bool Tile::isPassable() 
//{ 
//	return this->boundingBox.getIgnoreCollision(); 
//}
//###############################################################################################################################
//###########################################2ND MAP STRATEGY END##############################################################
//###############################################################################################################################
