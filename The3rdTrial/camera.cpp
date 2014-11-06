#include "Camera.h"


Camera::Camera(float x ,float y)
{
	Camera::x = 0;
	Camera::y = 0;
}

Camera::Camera(void)
{

}


Camera::~Camera(void)
{
}


void Camera::setSize(float width,float height)
{
	this->width  = width;
    this->height = height;
}

void Camera::setFocusedCharacter(Character* focusedChar)
{
	if (focusedChar) 
	{
        this->focusedChar = focusedChar;
        
        focus.x = this->focusedChar->getX();
        focus.y = this->focusedChar->getY();
    }
}


/**
* Algorithm used: Tweaning -> <code>x += (target - value) * constant</code>
*/
void Camera::update()
//void Camera::update(Player* p1)
{
    int posX = focusedChar->getX() + focusedChar->getWidth() / 2;
    int posY = focusedChar->getY() + focusedChar->getHeight() / 2;

	//int posX = GameObject::coord.x + focusedChar->getWidth() / 2;
 //   int posY = GameObject::coord.y + focusedChar->getHeight() / 2;


	//std::cout<<"posX x is="<<posX<<std::endl;
	//std::cout<<"posY y is="<<posY<<std::endl;
    
	int spdX = focusedChar->getVelX();
    int spdY = focusedChar->getVelY();

	//std::cout<<"spdX x is="<<spdX<<std::endl;
	//std::cout<<"spdY y is="<<spdY<<std::endl;


	if (spdY > 0) {
        if (posY > focus.y) {
            position.y += spdY;
            focus.y    += spdY;
        }
    } else {
        if (posY < focus.y) {
            position.y += spdY;
            focus.y    += spdY;
        }
    }
    
    if (spdX > 0) {
        if (posX > focus.x) {
            position.x += spdX;
            focus.x    += spdX;
        }
    } else {
        if (posX < focus.x) {
            position.x += spdX;
            focus.x    += spdX;
        }
    }

	//Player p1;
	//p1 = Player::getInstance();
	// set the Camera to make the Player at the center of screen and it follows with the Player with a delay
	//x += (( -p->GetPos().x + WIDTH / 2) - x) * 0.0875f; // original
	//Player::GetInstance();
	//Camera::x += (( p1->getPos().x + WIDTH / 2) - Camera::x) * 0.0875f; // set
	//Camera::x += (( -Player::coord.x + WIDTH / 2) - Camera::x) * 0.0875f;
	//Camera::x += (( -p1->getPos().x + WIDTH / 2) - Camera::x) * 0.0875f;
	//Player::coord.x += 4 + (( -Player::coord.x + WIDTH / 2) - Player::coord.x) * 0.0875f;
	//Player::coord.x = Camera::x;
	//Player::coord.x += 4 * 1;
	//Camera::x += (( -Player::coord.x + WIDTH / 2) - Camera::x) * 0.0875f;
	//Player::coord.x += (( -Player::coord.x + WIDTH / 2) - Player::coord.x) * 0.0875f;
	//std::cout<<"cam x is="<<p1->getInstance().getCoordX()<<std::endl;
	//Player::coord.x = Camera::x;
	//std::cout<<"cam x is="<<Player::coord.x<<std::endl;

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

void Camera::setPosition(float x, float y)
{
	position.x = x;
    position.y = y;
}

void Camera::setFocus(float fx, float fy)
{
	focus.x = fx;
    focus.y = fy;
}

float Camera::getX()
{
	return this->x;
}

float Camera::getY()
{
	return this->y;
}