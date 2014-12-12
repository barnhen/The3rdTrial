#include "GameObject.h"

////instantianting super class with default values
//GameObject::GameObject(void) : boundingBox(0,0,0,0,true){};
//
////instantianting super class
//GameObject::GameObject(float x ,float y ,float width, float height, float velX, float velY, bool ignoreCollision = true) 
//			: boundingBox(x,y,width,height,ignoreCollision){};


GameObject::~GameObject(void)
{

}

//void GameObject::init(float x ,float y ,float width, float height, float velX, float velY)
//{
//	this->coord.x = x;
//	this->coord.y = y;
//	this->coord.h = height;
//	this->coord.w = width;
//	this->coord.vX = velX;
//	this->coord.vY = velY;
//	dirX = 0;
//	dirY = 0;
//
//	//boundingBox.init(coord.x,coord.y,coord.w,coord.h,coord.vX,coord.vY);
//	//world.addEntity();
//
//}


void GameObject::update()
{
	//rectangle.x += velX * dirX;
	//rectangle.y += velY * dirY;

}

void GameObject::render()
{

}


/**
 *Depreceated
 *
 *
 */
bool GameObject::collision (Rect* rec1, Rect* rec2)
{
	if (rec1->y >= rec2->y + rec2->h)
	{
		return false;
	}

	if (rec1->x >= rec2->x + rec2->w)
	{
		//std::cout<<"Right Collision"<<std::endl;
		return false;
	}
	
	if (rec1->y + rec1->h <= rec2->y)
	{
		return false;
	}

	if (rec1->x + rec1->w <= rec2->x)
	{
		//std::cout<<"Left Collision"<<std::endl;
		return false;
	}
	return true;
}

