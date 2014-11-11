#include "Player.h"

int leftScrolled = 0;
World *theBg;
bool isMoving = false;
//isScrolling = false;
//bool ground = false;
//bool jump = false;
//bool nc = false; // non collision


// This way the Player constructor will also be used in Characters' as we are defining it as superclass
Player::Player(ALLEGRO_BITMAP *pImg) : Character (pImg)
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
	gravity = .175;

	camera.x = 80; // Player starting x position
	camera.y = 0;
	camera.w = this->tileSize;
	camera.h = this->tileSize;

	pos.x = coord.x; // Player starting x position
	pos.y = 0;
	pos.w = Player::tileSize;
	pos.h = Player::tileSize;
	debugMsg = "default";
	debugCollisionMsg = "no collision";



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
		if (isJumpAllowed()){
			letsJump();
			}
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
		if (isJumpAllowed()){
			letsJump();
			} //jumping
		}
	}
	//or jumping
	else if(keys[SPACE])
	{
		if (isJumpAllowed()){
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
	//##################Player MOVING#####################################BEGIN##################
	//if (Player::dirX == 1) // move right
	//{
	//	// Player will move from most left part (scenario beginning)) untill the midle of screen
	//	if (Player::getPos().x <= WIDTH/2 -Character::box.w) // middle of screen minus the frame width to center it -> 640/2 - 50 = 270
	//	{
	//		//isScrolling = 0;
			Player::setVel(4);
	//		//std::cout<<"Player::GetPos().x < WIDTH/2 -Character::box.w"<<std::endl;
	//		debugMsg = "moving from most left part (scenario beginning)) untill the midle of screen";
	//	}
	//	// if Player is in the most right side of scenario limit and wants to walk left untill the mmiddle of screen
	//	// because we are skipping n x camera vel to scroll left we have to include the velCamX to condition
	//	else if(Player::getPos().x >= (900 - WIDTH/2) -Character::box.w)
	//	{
	//		//isScrolling = 0;
	//		//std::cout<<"limit right border"<<900 - WIDTH/2<<std::endl;
	//		Player::setVel(4);
	//		//std::cout<<"Player::GetPos().x > (900 - WIDTH/2) -Character::box.w"<<std::endl;
	//		debugMsg = "if Player is in the most right side of scenario limit and wants to walk left untill the mmiddle of screen";
	//	}
	//	// in the middle the Player will scroll right
	//	else
	//	{
	//		if (Player::getPos().x > (900 - WIDTH/2 -Character::box.w))
	//		{
	//			Player::setVel(4);
	//			//std::cout<<"if Player::GetPos().x > (900 - WIDTH/2 -Character::box.w)"<<std::endl;
	//			debugMsg = "in the middle the Player will scroll right 1";
	//		}
	//		else
	//		{
	//			//isScrolling = 1; //true
	//			Player::setXvel(0); //old 0
	//			Player::setCoordXvel(4);
	//			//std::cout<<"else Player::GetPos().x > (900 - WIDTH/2 -Character::box.w)"<<std::endl;
	//			debugMsg = "Player moving right while camera is scrolling";
	//		}
	//	}
	//}

	//else if(Player::dirX == -1) // move left
	//{
	//	// if Player is in the most right side of scenario limit and wants to walk left untill the mmiddle of screen
	//	// because we are skippn n x camera vel to scroll left we have to include the velCamX to condition
	//	if(Player::getPos().x - Player::velPosX > (900 - WIDTH/2) -Character::box.w)
	//	{
	//		//isScrolling = 0;
	//		//std::cout<<"limit right <left> border"<<900 - WIDTH/2<<std::endl;
	//		Player::setVel(4);
	//		debugMsg = "Player moving from right border to left where camera is not scrolling";
	//	}
	//	// because we are skippn n x camera vel to scroll left we have to include the velCamX to condition
	//	else if (Player::getPos().x - Player::velPosX > WIDTH/2 -Character::box.w)
	//	{
	//		//isScrolling = 1;
	//		Player::setXvel(0); //old 0
	//		Player::setCoordXvel(4);
	//		debugMsg = "Player moving from the center camera to the left border";
	//		//below lies the problem when colling to the left the camera scrolls to right when it is suppoesed to stop

	//	}
	//	// if Player is in the most left side of scenario limit and wants to walk right untill the mmiddle of screen
	//	// because we are skipping n x camera vel to scroll left we have to include the velCamX to condition
	//	else
	//	{
	//		//isScrolling = 0;
	//		Player::setVel(4);
	//		debugMsg = "Player moving left to border left where camera is not scrolling";

	//	}
	//}

	//if (Player::getPos().x - Player::velPosX < 0)
	//{
	//	Player::pos.x=0; // 0 to absolute pos.
	//	//Character::box.x=0; // 0 to relative pos.
	//}
	////##################Player MOVING#####################################END##################

	////####################GRAVITY AND COLICION WITH BG TILES#################BEGIN###################
	int start = ( GameObject::coord.x - ((int)GameObject::coord.x % theBg->getTileSize())) / theBg->getTileSize();
	int end = (GameObject::coord.x + GameObject::coord.w + (theBg->getTileSize() - (int)(GameObject::coord.x + GameObject::coord.w) % theBg->getTileSize())) / 50;

	////int start = ( World::getInstance()->getBox().x - (World::getInstance()->getBox().x % World::getInstance()->getTileSize())) / World::getInstance()->getTileSize();
	////int end = (World::getInstance()->getBox().x + World::getInstance()->getBox().w + (World::getInstance()->getTileSize() - (World::getInstance()->getBox().x + World::getInstance()->getBox().w) % World::getInstance()->getTileSize())) / 50;
	////World* theBg = World::getInstance();
	////int start = theBg->getStartMapBoundaries();
	////int end = theBg->getStartMapBoundaries();

	////int start = (World::getInstance()->getStartMapBoundaries());
	////int end = (World::getInstance()->getEndMapBoundaries());

	////int *start = World::getInstance()->getStartMapBoundaries();
	////int *end = World::getInstance()->getEndMapBoundaries();



	////std::cout<<"start: "<<*start<<std::endl;
	////std::cout<<"end: "<<*end<<std::endl;

	////std::cout<<"start: "<<start<<std::endl;
	////std::cout<<"end: "<<end<<std::endl;


	if (start < 0)
	{
		start=0;
	}
	if (end > map[0].size())
	{
		end = map[0].size();
	}
	nc = false; // non collision

	for (int i = 0; i < map.size(); i++)
	{
		for (int j = start; j < end; j++)
		{
			if(map[i][j] == 0)
				continue;
			destrect.x=j * 50 - GameObject::coord.x;
			destrect.y=i * 50; //original
			BoundingBox bb;
			//if (collision(&box, &destrect))
			if (bb.rectOverlap(box, destrect))
			{
				nc = true;
				setDestRect(destrect);
				//below condition make the Player hit the ground when he falls by gravity
				//if(destrect.y <= Character::box.y + Character::box.h)
				if(bb.hasVerticalCollision(box, destrect))
				{
					ground = true;
					box.vY= 0 ;
					debugCollisionMsg = "ground";

										//horizontalCharacter::box collision check begin
					//will stop the Player the pass throughCharacter::box on x direction
					//pushing to left
					if (Character::box.x + Character::box.w >= destrect.x - 5 && 
						//Character::box.y + Character::box.h >= destrect.y + 6 && 
						bb.hasVerticalCollision(box, destrect) &&
						Character::box.x + Character::box.w <= destrect.x +20)
					{
						//Character::box.x = Character::box.x - GameObject::velX; // we stop the Player from moving to right
						//Player::pos.x = Player::pos.x - Player::velPosX; // we stop the posx of Player from increasing

						//if (isScrolling == 1) {Player::coord.x = Player::coord.x - Player::velPosX;std::cout<<"pushing left col"<<std::endl;}
					
						//std::cout<<"pushing left|X coord="<<pos.x<<"|y coord="<<box.y<<"|destrect x="<<destrect.x<<"|destrect.y="<<destrect.y<<std::endl;
						debugCollisionMsg = "pushing left";
						//std::cout<<"destrect push right if is "<<destrect.x<<std::endl;

					}
					//pushing to right
					else if (Character::box.x -Character::box.w <= destrect.x + destrect.w
							//&& Character::box.y +Character::box.h >= destrect.y + 6
							&& bb.hasVerticalCollision(box, destrect)
							)
					{
						//Character::box.x = Character::box.x + GameObject::velX; // we stop the Player from moving to left
						//Player::pos.x = Player::pos.x + Player::velPosX; // we stop the poskx of Player from decreasing

						//if (isScrolling == 1) 
						//{Player::coord.x = Player::coord.x + Player::velCoordX;std::cout<<"pushing right col"<<std::endl;}// we stop the posx of Player from increasing


					
						//std::cout<<"pushing right|X coord="<<pos.x<<"|y coord="<<box.y<<"|destrect x="<<destrect.x<<"|destrect.y="<<destrect.y<<std::endl;
						debugCollisionMsg = "pushing right";
					}
						//horizontalCharacter::box collision check end

				}
				//else if (destrect.y + destrect.h <=Character::box.y + 150)
				//{
				//	box.vY = 10; // this will be gravity
				//}

				//} // end if isScrolling
			}// end if collision(&box, &destrect)
		} //end for j < end
	}// end for map.size()
	//below will make the gravity work on the Player. he will fall
	//if (!nc && !jump) // not colliding nor jumping

	// means he is either falling or started falling
	if (!nc && !jump) // not colliding nor jumping
	{
		box.vY = 6.5; //will make gravity to fall the Player faster
		//std::cout<<"not coliding or jumping"<<std::endl;
		//box.y -= 5;

		//if(box.vY>=0)
		//{
		//	Player::coord.y++;
		//}
	}
	else
	{
		jump = false;
	}


	//below will make the Player start falling after jumping and hit the ground again
	//if (!jump && box.vY < 6.5)
	//{
	//	//SetYvel(velY++);
	//	//box.vY+=1; //will make the jump last
	//	box.vY = 6.5;
	//}
	if (!ground)
	{
		box.vY+=gravity; //will make the jump last
	}


	//max vel downword
	//if(box.vY > 15)
	//{
	//	box.vY = 15;
	//}

	////####################GRAVITY AND COLICION WITH BG TILES#################END###################
	//
	//####### WILL UPDATECharacter::box MOVEMENT###############
	Character::box.x += GameObject::velX * Player::dirX;
	//box.x += 4 * Player::dirX;
	//////jumping
	Character::box.y += box.vY; //update makes the Player falling according to gravity speed
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


}
void Player::moveLeft()
{
	Player::dirX = -1;
}

void Player::moveRight()
{
	Player::dirX =1;
}

void Player::letsJump()
{
	if (ground && !jump)
	{
		box.vY = -13.00; //velocity from jumping from ground to mid-air until reaches 0 and it increase from 0 to more until reaches the ground
		jump = true;
		ground = false;
		
		box.y -= 5;
	}
	
}

void Player::move()
{
}

void Player::resetAnimation()
{
	Player::dirX = 0;
	//Player::Move(themap);
}

