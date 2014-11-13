#include "Character.h"



// This way the Character constructor will also be used in GameObject' as we are defining it as superclass
Character::Character(ALLEGRO_BITMAP *pImg) : GameObject()
{
	std::cout<<"MAX_ENUM_LENGHT is "<<MAX_ENUM_LENGHT<<std::endl;
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

void Character::init(float x, float y, float width, float height, float velX, float velY) {
    //if (!loaded) {
    //    loaded = load_frames();
    //    update_bounding_boxes();
	this->tileSize =50;
	this->box.x = x;
	this->box.y = y;
	this->box.w = width;
	this->box.h = height;
	this->box.vX = velX;
	this->box.vX = velY;
	collisionTime = 0.0f;
	GameObject::init(x,y,imageW,imageH, velX, velY);
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
		if (ev.type==ALLEGRO_EVENT_KEY_DOWN)
		{
			switch(ev.keyboard.keycode)
			{
				case ALLEGRO_KEY_LEFT: 
					keys[LEFT]=true;
					break;
				case ALLEGRO_KEY_RIGHT: 
					keys[RIGHT]=true;
					break;
				case ALLEGRO_KEY_SPACE: 
					keys[SPACE]=true;
					break;
			   case ALLEGRO_KEY_P: 
					keys[P]=true;
					break;
				case ALLEGRO_KEY_V: 
					if (!visibleBoundingBox)
						visibleBoundingBox=true;
					else 
						visibleBoundingBox=false;
					break;
			}
		} // if (ev.type==ALLEGRO_EVENT_KEY_DOWN)

		//key released
		else if(ev.type == ALLEGRO_EVENT_KEY_UP)
		{
			switch(ev.keyboard.keycode)
			{
				case ALLEGRO_KEY_LEFT: 
					keys[LEFT]=false;
					break;
				case ALLEGRO_KEY_RIGHT: 
					keys[RIGHT]=false;
					break;
				case ALLEGRO_KEY_SPACE: 
					keys[SPACE]=false;
					break;
				case ALLEGRO_KEY_P: 
					keys[P]=true;
				
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
				//break;

			} // switch

		} // else if(ev.type == ALLEGRO_EVENT_KEY_UP)

}

void Character::updatePhysics()
{
	charPhysics->update();
}
