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
	//keys[] = {false, false, false, false, false, false,false,false};
}


Character::~Character(void)
{
}

void Character::init() {
    //if (!loaded) {
    //    loaded = load_frames();
    //    update_bounding_boxes();
	imageW = 50;
	imageH = 50;
	//bb.set_w(al_get_bitmap_width(f->image));
 //   bb.set_h(al_get_bitmap_height(f->image));
    //}
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
