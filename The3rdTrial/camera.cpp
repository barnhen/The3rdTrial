#include "Camera.h"


Camera::Camera(float x ,float y)
{
	Camera::x = 0;
	Camera::y = 0;
}


Camera::~Camera(void)
{
}

/**
* Algorithm used: Tweaning -> <code>x += (target - value) * constant</code>
*/
void Camera::update()
//void Camera::update(Player &p1)

{
	Player p1;
	// set the Camera to make the Player at the center of screen and it follows with the Player with a delay
	//x += (( -p->GetPos().x + WIDTH / 2) - x) * 0.0875f; // original
	//Player::GetInstance();
	//x += (( -p1.GetPos().x + WIDTH / 2) - Camera::x) * 0.0875f;
	//Camera::x += (( -Player::coord.x + WIDTH / 2) - Camera::x) * 0.0875f;
	//Player::coord.x += Player::velCoordX * Player::dirX;
	Camera::x += (( -Player::coord.x + WIDTH / 2) - Camera::x) * 0.0875f;
	std::cout<<"cam x is="<<p1.getInstance().getCoordX()<<std::endl;

	//Player::coord.x += p1.getXVel() * p1.getDirX();
	//std::cout<<"coord.x is="<<coord.x<<std::endl;
	//std::cout<<"velCoordX is="<<p1.getXVel()<<std::endl;
	//std::cout<<"dirX is="<<p1.getDirX()<<std::endl;

	//################OLD Player BEGIN
	//p->box.x += Player::velX * Player::dirX;
	////jumping
	//Player::box.y += Player::velY; //update makes the Player falling according to gravity speed
		
	//if (!ground)
	//{
	//	//Player::box.y+=4;
	//	//Player::coord.y += Player::velY; // this point will scroll the map
	//	//Player::coord.y--; // this point will scroll the map
	//}
	//
	////####### WILL UPDATE ABSOLUTE MAP COORDINATES###############
	//if (isScrolling==1) //not scrolling
	//{
	//	Player::coord.x += Player::velCoordX * Player::dirX;
	//	//Player::coord.y += Player::velCoordY * Player::dirY;

	//}
	//if (!ground)
	//{
	//	//Player::coord.y += velCoordX;
	//	/*background bg*/;
	//	//int bgCoord = bg.GetDestRect().y;
	//	//bgCoord +=1;
	//	//int bgCoord = background::GetBlockRect().y;
	//	//base::coord.y += 1;
	//	//theBg->SetDestRectY(+1);
	//	//bgCoord +=1;

	//}

	//################OLD Player END
}

float Camera::getX()
{
	return x;
}

float Camera::getY()
{
	return y;
}