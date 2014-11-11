#include "GameObject.h"


GameObject::GameObject(void)
{
	
}


GameObject::~GameObject(void)
{
}

void GameObject::init(float x ,float y ,float width, float height, float velX, float velY)
{
	this->x = x;
	this->y = y;
	this->height = height;
	this->width = width;
	this->velX = velX;
	this->velY = velY;
	dirX = 0;
	dirY = 0;

	boundingBox.init(x,y,width,height,velX,velY);
	//world.addEntity();

}


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

