#include "base.h"


base::base(void)
{
}


base::~base(void)
{
}

void base::Update(std::vector<std::vector<int> >& map)
{
	//sprite.x += velX * dirX;
	//sprite.y += velY * dirY;

}

void base::Render()
{

}


bool base::collision (sprite* rec1, sprite* rec2)
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

