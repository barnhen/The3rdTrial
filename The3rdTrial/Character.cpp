#include "Character.h"



// This way the Character constructor will also be used in GameObject' as we are defining it as superclass
Character::Character(float x, float y, float width, float height, float velX, float velY, float maxVelY, ALLEGRO_BITMAP *pImg) 
				    : GameObject(x ,y ,width, height, velX, velY)
{
	std::cout<<"MAX_ENUM_LENGHT is "<<MAX_ENUM_LENGHT<<std::endl;

	loaded = false;
	this->box.x=x;
	this->box.y=y;
	this->box.w=width;
	this->box.h=height;
	this->box.vX=velX;
	this->box.vY=velY;
	//keys[UP]=false;
	//keys[DOWN]=false;
	//keys[LEFT]=false;
	//keys[RIGHT]=false;
	//keys[SPACE]=false;
	//keys[LEFT]=false;
	//keys[C]=false;
	//keys[E]=false;
	//keys[P]=false;
	//int size = 	sizeof(keys);
	for (unsigned int i = 0; i < sizeof(keys); i++)
	{
		keys[i] = false;
	}
	visibleBoundingBox=false;
	//keys[] = {false, false, false, false, false, false,false,false};
}


Character::~Character(void)
{
}

//void Character::init(float x, float y, float width, float height, float velX, float velY, float maxVelY) {
void Character::init() 
	{
	loaded = true;
    //if (!loaded) {
    //    loaded = load_frames();
    //    update_bounding_boxes();
	//this->tileSize =50;
	//this->box.x = x;
	//this->box.y = y;
	//this->box.w = width;
	//this->box.h = height;
	//this->box.vX = velX;
	//this->box.vX = velY;
	collisionTime = 0.0f;
	//verticalSpeedLimit = maxVelY;
	//GameObject::init(x,y,imageW,imageH, velX, velY);
	//bb.set_w(al_get_bitmap_width(f->image));
 //   bb.set_h(al_get_bitmap_height(f->image));
    //}
}

void Character::setCollisionRect()
{
	if (box.vX > 0)
	{
		collisionRect.x = box.x + box.w / 4 + 5;
		collisionRect.w = box.w / 2;
		collisionRect.y = box.y + box.h / 3 + 5;
		collisionRect.h = box.h - box.h / 3 - 5;
	}
	else /*if (box.vX < 0)*/
	{
		collisionRect.x = box.x + box.w / 3;
		collisionRect.w = box.w / 2;
		collisionRect.y = box.y + box.h / 3 - 5;
		collisionRect.h = box.h - box.h / 3 + 5;
	}
}

void Character::setBoundingBoxes()
{
	Character::collisionRect = Character::box;
	
	Character::topTileRect.x = Character::box.x + Character::box.w/4;
	Character::topTileRect.y = Character::box.y - Character::box.h/6;
	Character::topTileRect.w = Character::box.w/2;
	Character::topTileRect.h = Character::box.h/2;

	Character::bottomTileRect.x = Character::box.x + Character::box.w/4;
	Character::bottomTileRect.y = Character::box.y + Character::box.h/1.5;
	Character::bottomTileRect.w = Character::box.w/2;
	Character::bottomTileRect.h = Character::box.h/2;

	Character::middleLeftTileRect.x = Character::box.x - Character::box.w/6;
	Character::middleLeftTileRect.y = Character::box.y + Character::box.h/4;
	Character::middleLeftTileRect.w = Character::box.w/1.5;
	Character::middleLeftTileRect.h = Character::box.h/2;

	Character::middleRightTileRect.x = Character::box.x + Character::box.w/2;
	Character::middleRightTileRect.y = Character::box.y + Character::box.h/4;
	Character::middleRightTileRect.w = Character::box.w/1.5;
	Character::middleRightTileRect.h = Character::box.h/2;
}

void Character::handleInput(const ALLEGRO_EVENT& ev)
{
	//key pressed
	if ((ev.type == ALLEGRO_EVENT_KEY_DOWN) || (ev.type == ALLEGRO_EVENT_KEY_UP))
	{
		switch(ev.keyboard.keycode)
		{
			// The following statements will only be true if the key is pressed (ALLEGRO_EVENT_KEY_DOWN), 
			// not released (ALLEGRO_EVENT_KEY_UP)
			case ALLEGRO_KEY_LEFT: 
					keys[LEFT] = (ev.type == ALLEGRO_EVENT_KEY_DOWN); 
					break;
				case ALLEGRO_KEY_RIGHT: 
					keys[RIGHT] = (ev.type == ALLEGRO_EVENT_KEY_DOWN);
					break;
				case ALLEGRO_KEY_SPACE: 
					keys[SPACE] = (ev.type == ALLEGRO_EVENT_KEY_DOWN);
					break;
			   case ALLEGRO_KEY_P: 
					keys[P] = (ev.type == ALLEGRO_EVENT_KEY_DOWN);
					//if (isPaused)
					//{
					//	//al_start_timer(timer);
					//	//al_flip_display();
					//	isPaused = false;
					//}
					//else
					//{
					//	//al_stop_timer(timer);
					//	al_flip_display();
					//	isPaused = true;
					//}

					break;
				case ALLEGRO_KEY_V: 
					//keys[P] = (ev.type == ALLEGRO_EVENT_KEY_DOWN);
					if (!visibleBoundingBox)
						visibleBoundingBox=true;
					else 
						visibleBoundingBox=false;
					break;
		}
	}
}

void Character::update()
{
	implementUpdate();
	updateBoundingBoxes();
}

void Character::draw() const
{
	 if (loaded) {
        implementDraw();
    }
}

void Character::implementUpdate()
{
		//gravity action
	//box.vY += gravity;

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
		//moveLeft();
		box.x = -box.vX;

		//what if the Player wants to jump while moving?
		if(keys[SPACE])
		{
			//if (ground && !jump)
			{
				//letsJump();
			}
			//if (isJumpAllowed()){
			//}
			
		} //jumping
	}
	//or RIGHT
	else if(keys[RIGHT])
	{
		//dir = 1;
		//moveRight();
		box.x = box.vX;
				
		//what if the Player wants to jump while moving?
		if(keys[SPACE])
		{
		//if (isJumpAllowed()){
			//if (ground && !jump)
			{
				//letsJump();
			} //jumping
		}
	}
	//or jumping
	else if(keys[SPACE])
	{
		//if (isJumpAllowed())
		//if (ground)
		{
			//letsJump();
			//what if the Player wants move right while jumping?
			if(keys[RIGHT])
			{
				//dir = 1;
				//moveRight();
			}
			//what if the Player wants move left while jumping?
			else if(keys[LEFT])
			{
				//dir = -1;
				//moveLeft();
			}
		}
	}

	//or default position
	else
	{
		//dir = 0;
		resetAnimation();
	}


	
	//Character::updatePhysics();
	////##################Player MOVING#####################################END##################

	//	if (!nc && !jump) // not colliding nor jumping
	//{
	//	box.vY = 6.5; //will make gravity to fall the Player faster
	//	

	//}
	//
	//if(jump && box.vY < -7.5)
	//{
	//	box.vY += gravity;
	//}
	//else
	//{
	//	jump = false;
	//}

	//if (box.vY > 8)
	//{
	//	//box.vY = 15;
	//}


		

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
		//Character::box.x += box.vX;
		//Character::box.y += box.vY; //update makes the Player falling according to gravity speed
		//debugMsg = "moving int the air";
	}

	//Character::setBoundingBoxes();
	//std::cout<<"bb getX="<<boundingBox.getX()<<std::endl;
	//std::cout<<"bb getY="<<boundingBox.getY()<<std::endl;
	//std::cout<<"boxX="<<box.x<<std::endl;
	//std::cout<<"boxY="<<box.y<<std::endl;
	//boundingBox.setX(boundingBox.getX() + box.x);
	//boundingBox.setY(boundingBox.getY() + box.y);
	//std::cout<<"box.x"<<box.x<<std::endl;
	//std::cout<<"bb.get_x() + box.x = "<<boundingBox.getX()<<" + "<<box.x<<" = "<<boundingBox.getX() + box.x<<std::endl;
	boundingBox.setX(boundingBox.getX() + box.x);
	boundingBox.setY(boundingBox.getY() + box.y);


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

void Character::moveLeft()
{
	//Player::dirX = -1;
	this->box.x = -box.vX;
}

void Character::moveRight()
{
	//Player::dirX =1;
	this->box.x = box.vX;
}


void Character::resetAnimation()
{
	//Player::dirX = 0;
	//Player::box.vX = 0;
	this->box.x = 0;
	//Player::Move(themap);
}


void Character::updateBoundingBoxes()
{}

void Character::updatePhysics()
{
	charPhysics->update();
}
