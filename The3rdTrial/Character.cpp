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
