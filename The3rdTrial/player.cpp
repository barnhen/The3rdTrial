#include "Player.h"

int leftScrolled = 0;
//World *theBg;
bool isMoving = false;
//isScrolling = false;
//bool ground = false;
//bool jump = false;
//bool nc = false; // non collision


// This way the Player constructor will also be used in Characters' as we are defining it as superclass
Player::Player(float x, float y, float width, float height, float velX, float velY, float maxVelY, ALLEGRO_BITMAP *pImg) 
			   : Character (x, y, width, height, velX, velY, maxVelY, pImg)
{
	playerImg = pImg;
	/*Player::tileSize =50;*/
	isScrolling = 0; // false
	//coord.x = 80; // Player starting x position
	//coord.y = 0;
	//coord.w = Player::tileSize;
	//coord.h = Player::tileSize;

	destrect.x=0;
	destrect.y=0;
	destrect.w=50;
	destrect.h=50;

	//Character::box.x = 80; // Player starting x position
	//Character::box.y = 0;
	//Character::box.w = this->tileSize;
	//Character::box.h = this->tileSize;
	gravity = .775;

	camera.x = 80; // Player starting x position
	camera.y = 0;
	camera.w = this->tileSize;
	camera.h = this->tileSize;

	//pos.x = coord.x; // Player starting x position
	pos.x = box.x; // Player starting x position
	pos.y = 0;
	pos.w = Player::tileSize;
	pos.h = Player::tileSize;
	debugMsg = "default";
	debugCollisionMsg = "no collision";

	Character::verticalSpeedLimit = 8;
	Character::jumpingForce = 6;



	this->velX = 0;
	this->dirX = 0;
	this->velCamX = 0;

	ground = false;
	jump = false;
	nc = false; // non collision
	
}


//Player::Player(void)
//{
//}

// the trouble to return object instance
//static Player &getInstance()
//{
//	static Player instance;
//	return instance;
//}


Player::~Player(void)
{
}

//void Player::init(ALLEGRO_BITMAP *pImg)
//{
//}




void Player::render()
{
	al_draw_filled_rectangle(Character::box.x, Character::box.y,Character::box.x + Character::box.w ,Character::box.y + Character::box.h, al_map_rgba(255,0,255,100));
	//al_draw_filled_rectangle(GameObject::getCoord().x, GameObject::getCoord().y,GameObject::getCoord().x + Character::box.w ,GameObject::getCoord().y + Character::box.h, al_map_rgba(255,0,255,100));

}

void Player::setVel(int vel)
{
	velX = vel;
	velPosX = vel;
	velCoordX = vel;
}


void Player::setCoordXvel(int vel)
{
	velCoordX = vel;
}


void Player::setXvel(int vel)
{
	velX = vel;
}

void Player::setYvel(int vel)
{
	box.vY = vel;
}


void Player::setCamXvel(int cVel)
{
	velCamX = cVel;
}

void Player::setCamYvel(int cVel)
{
	velCamY = cVel;
}

void Player::setDestRect(Rect dest)
{
	dest = destrect;
}

void Player::setPosXvel(int cVel)
{
	velPosX = cVel;
}

void Player::setPosYvel(int cVel)
{
	velPosY = cVel;
}


//void Player::update()
void Player::update(std::vector<std::vector<int> >& map)
{
	//gravity action
	box.vY += gravity;

	if (box.vY > Character::verticalSpeedLimit){
		box.vY = Character::verticalSpeedLimit;
	}

	//background bg;
	//const std::vector<std::vector<int> > map = background::GetInstance().GetMap();
	//int test = background::GetInstance().GetInt();
	//theBg->GetMap();

	//std::vector<std::vector<int> > map =  World::getInstance().getMap();
	
	//##############################key handling ################################################
	//LEFT 
	if(keys[LEFT])
	{
		//dir = -1;
		//World::coord.x= World::velX * World::dirX;
		moveLeft();

		//what if the Player wants to jump while moving?
		if(keys[SPACE])
		{
			//if (ground && !jump)
			{
				letsJump();
			}
			//if (isJumpAllowed()){
			//}
			
		} //jumping
	}
	//or RIGHT
	else if(keys[RIGHT])
	{
		//dir = 1;
		moveRight();
				
		//what if the Player wants to jump while moving?
		if(keys[SPACE])
		{
		//if (isJumpAllowed()){
			//if (ground && !jump)
			{
				letsJump();
			} //jumping
		}
	}
	//or jumping
	else if(keys[SPACE])
	{
		//if (isJumpAllowed())
		if (ground)
		{
			letsJump();
			//what if the Player wants move right while jumping?
			if(keys[RIGHT])
			{
				//dir = 1;
				moveRight();
			}
			//what if the Player wants move left while jumping?
			else if(keys[LEFT])
			{
				//dir = -1;
				moveLeft();
			}
		}
	}

	//or default position
	else
	{
		//dir = 0;
		resetAnimation();
	}


	
	Character::updatePhysics();
	////##################Player MOVING#####################################END##################

		if (!nc && !jump) // not colliding nor jumping
	{
		box.vY = 6.5; //will make gravity to fall the Player faster
		

	}
	
	if(jump && box.vY < -7.5)
	{
		box.vY += gravity;
	}
	else
	{
		jump = false;
	}

	if (box.vY > 8)
	{
		//box.vY = 15;
	}

		

	////####################GRAVITY AND COLICION WITH BG TILES#################BEGIN###################
	//BoundingBox bb;

	//int start = ( GameObject::coord.x - ((int)GameObject::coord.x % theBg->getTileSize())) / theBg->getTileSize();
	//int end = (GameObject::coord.x + GameObject::coord.w + (theBg->getTileSize() - (int)(GameObject::coord.x + GameObject::coord.w) % theBg->getTileSize())) / 50;


	//if (start < 0)
	//{
	//	start=0;
	//}
	//if (end > map[0].size())
	//{
	//	end = map[0].size();
	//}
				////####### WILL UPDATECharacter::box MOVEMENT###############
	//// means he is either falling or started falling
	//if (nc && jump)	jump=false;

	//if(box.vY < -17)
	//{
	//	box.vY = -17;
	//}

	//if (!ground)
	//{
	//	box.vY+=gravity; //will make the jump last
	//}

	//if (!nc)
	{
		Character::box.x += box.vX;
		//Character::box.y += box.vY; //update makes the Player falling according to gravity speed
		//debugMsg = "moving int the air";
	}

	//Character::setBoundingBoxes();
	//std::cout<<"bb getX="<<boundingBox.getX()<<std::endl;
	//std::cout<<"bb getY="<<boundingBox.getY()<<std::endl;
	//std::cout<<"boxX="<<box.x<<std::endl;
	//std::cout<<"boxY="<<box.y<<std::endl;
	boundingBox.setX(boundingBox.getX() + box.x);
	boundingBox.setX(boundingBox.getY() + box.y);

	//below will make the Player start falling after jumping and hit the ground again
	//if (!jump && box.vY < 6.5)
	//{
	//	//SetYvel(velY++);
	//	//box.vY+=1; //will make the jump last
	//	box.vY = 6.5;
	//}
	//if (!ground)
	//{
	//	box.vY+=gravity; //will make the jump last
	//}


	//max vel downword
	//if(box.vY > 15)
	//{
	//	box.vY = 15;
	//}

	////####################GRAVITY AND COLICION WITH BG TILES#################END###################
	//
	////####### WILL UPDATECharacter::box MOVEMENT###############
	//Character::box.x += GameObject::velX * Player::dirX;
	////box.x += 4 * Player::dirX;
	////////jumping
	//Character::box.x += box.vX;

	//Character::box.y += box.vY; //update makes the Player falling according to gravity speed
	//	
	//if (!ground)
	//{
	//	//Character::box.y+=4;
		//Player::coord.y += box.vY; // this point will scroll the map
	//	//Player::coord.y--; // this point will scroll the map
	//}
	//
	////####### WILL UPDATE ABSOLUTE MAP COORDINATES###############
	////if (isScrolling==1) //not scrolling
	//{
		//Player::coord.x += Player::velCoordX * Player::dirX;
		//Player::coord.x += 4 * Player::dirX;
		//std::cout<<"coord.x is "<<coord.x<<std::endl;
	//	//std::cout<<"velCoordX is "<<velCoordX<<std::endl;
	//	//Player::coord.y += Player::velCoordY * Player::dirY;

	//}
	//if (!ground)
	//{
	//	//Player::coord.y += velCoordX;
	//	/*background bg*/;
	//	//int bgCoord = bg.GetDestRect().y;
	//	//bgCoord +=1;
	//	//int bgCoord = background::GetBlockRect().y;
	//	//GameObject::coord.y += 1;
	//	//theBg->SetDestRectY(+1);
	//	//bgCoord +=1;

	//}
	////####### WILL UPDATE ABSOLUTE POSITION COORDINATES###############
	//Player::pos.x += Player::velPosX * Player::dirX;
	////Player::camera.x += Player::velCamX * Player::dirX;
	////Player::camera.y += Player::velCamY;
	////Player::camera.y += Player::velY;

	//Character::setCollisionRect();

	// Get the tiles that're directly above and beneath the robot's feet
	//int tileWidth = Character::box.w;
 //   int tileHeight = Character::box.h;
	//Character::bottomTileRect.w = Character::topTileRect.w = tileWidth;
	//Character::bottomTileRect.h = Character::topTileRect.h = tileHeight;
	//// Get the bottom tile
	////int row = (Character::getCollisionRect().y + Character::getCollisionRect().h)/tileHeight;
	////int column = (Character::getCollisionRect().x + Character::getCollisionRect().w/2)/tileWidth;
	////
	////Character::bottomTileRect.x = column*tileWidth;
	////Character::bottomTileRect.y = row*tileHeight;
	//Character::bottomTileRect.x = Character::box.x;
	//Character::bottomTileRect.y = Character::box.y;

	//// Get the top tile
	////row = (Character::getCollisionRect().y)/tileHeight;
	////column = (Character::getCollisionRect().x + Character::getCollisionRect().w/2)/tileWidth;

	////Character::topTileRect.x = column*tileWidth;
	////Character::topTileRect.y = row*tileHeight;

	//Character::topTileRect.x = Character::box.x;
	//Character::topTileRect.y = Character::box.y;

	





}

bool Player::isJumpAllowed()
{
	if(jump)
	{
		return false;
	}
	return true;;
}


void Player::moveLeft()
{
	//Player::dirX = -1;
	Player::box.vX = -4;
}

void Player::moveRight()
{
	//Player::dirX =1;
	Player::box.vX = 4;
}

void Player::letsJump()
{
	//if(!jump)
	//	box.vY = -17.00; //velocity from jumping from ground to mid-air until reaches 0 and it increase from 0 to more until reaches the ground
	//else
	//	box.y += box.vY;
	box.vY = -jumpingForce;

	//jump = true;
	//ground = false;
		
		//box.y += box.vY;
}

void Player::move()
{
}

void Player::resetAnimation()
{
	//Player::dirX = 0;
	Player::box.vX = 0;
	//Player::Move(themap);
}

