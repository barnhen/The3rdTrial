#include "Game.h"


std::list<GameObject *> objects;
std::list<GameObject *>::iterator iter;
Rect GameObject::coord;
bool keys[] = {false, false, false, false, false, false,false};
enum KEYS{UP, DOWN, LEFT, RIGHT, SPACE, C,E};
//bool keyHold = false;
//int dir = 0;


// don't forget to put allegro-5.0.10-monolith-md-debug.lib
//==============================================
//SHELL VARIABLES
//==============================================
bool done = false;
bool render = false;

float GameTime = 0;
int frames = 0;
int gameFPS = 0;
const int FPS = 60;
bool debug = true;

//==============================================
//ALLEGRO VARIABLES
//==============================================
ALLEGRO_DISPLAY *display = NULL;
ALLEGRO_EVENT_QUEUE *eventQueue = NULL;
ALLEGRO_TIMER *timer;
ALLEGRO_BITMAP *image = NULL;
ALLEGRO_FONT *font18 = NULL;
ALLEGRO_FONT *font11 = NULL;
ALLEGRO_BITMAP *bgImage = NULL;
ALLEGRO_BITMAP *PlayerImage = NULL;
ALLEGRO_BITMAP *tileSheet=NULL;
ALLEGRO_EVENT ev;


//==============================================
//PROJECT VARIABLES
//==============================================
World *bg;
Player *player1; 
Camera *cam;

Game::Game(void)
{
}


Game::~Game(void)
{

}

void Game::showDebugMode(void)
{
	//al_init_font_addon();
	//al_init_ttf_addon();
	al_draw_textf(font18, al_map_rgb(255, 255, 0), 5, 5, 0, "FPS: %i", gameFPS); // display Game FPS on screen
	al_draw_textf(font11, al_map_rgb(255, 255, 0), 5, 25, 0, "Player x vel: %i", player1->getXVel()); 
	al_draw_textf(font11, al_map_rgb(255, 255, 0), 100, 25, 0, "Player dirX: %i", player1->getDirX()); 
	al_draw_textf(font11, al_map_rgb(255, 255, 0), 5, 35, 0, "Player posX: %i", player1->getPos().x); 
	al_draw_textf(font11, al_map_rgb(255, 255, 0), 100, 35, 0, "Player posY: %i", player1->getPos().y); 
	al_draw_textf(font11, al_map_rgb(255, 255, 0), 200, 35, 0, "Player box x: %i", player1->getRect().x);
	al_draw_textf(font11, al_map_rgb(255, 255, 0), 300, 35, 0, "Player box y: %i", player1->getRect().y);
	al_draw_textf(font11, al_map_rgb(255, 255, 0), 400, 35, 0, "Player cam x: %i", player1->getCamera().x);
	al_draw_textf(font11, al_map_rgb(255, 255, 0), 500, 35, 0, "Player y vel: %i", player1->getYVel());
	al_draw_textf(font11, al_map_rgb(255, 255, 0), 600, 35, 0, "Player y vel: %i", player1->getYVel());

	al_draw_textf(font11, al_map_rgb(255, 255, 0), 5, 45, 0, "Player desX: %i", player1->getDestRect().x); 
	al_draw_textf(font11, al_map_rgb(255, 255, 0), 100, 45, 0, "Player desY: %i", player1->getDestRect().y);
	al_draw_textf(font11, al_map_rgb(255, 255, 0), 300, 45, 0, "Player desW: %i", player1->getDestRect().w);
	al_draw_textf(font11, al_map_rgb(255, 255, 0), 400, 45, 0, "Player desH: %i", player1->getDestRect().h);


	al_draw_textf(font11, al_map_rgb(255, 255, 0), 5, 55, 0, "bg coord x: %i", bg->getCoordX()); 
	al_draw_textf(font11, al_map_rgb(255, 255, 0), 100, 55, 0, "bg bomapx x: %i", bg->getMapSize()); 
	al_draw_textf(font11, al_map_rgb(255, 255, 0), 200, 55, 0, "bg blockrect y: %i", bg->getBlockRect().y); 
	al_draw_textf(font11, al_map_rgb(255, 255, 0), 300, 55, 0, "bg blockrect y: %i", bg->getDestRect().y); 

	al_draw_textf(font11, al_map_rgb(255, 255, 0), 5, 65, 0, "Scrolling: %s\n", player1->getIsScrolling()?"true":"false"); 
	al_draw_textf(font11, al_map_rgb(255, 255, 0), 100, 65, 0, "Camera X: %f\n", cam->getX()); 
	al_draw_textf(font11, al_map_rgb(255, 255, 0), 300, 65, 0, "Player coord X: %f\n", player1->getPos()); 
	//al_draw_textf(font11, al_map_rgb(255, 255, 0), 80, 5, 0, player1->getDebugPlayerMov()); 



}


void Game::initializeGameEngine ()
{
	//==============================================
	//ALLEGRO INIT FUNCTIONS
	//==============================================
	//check if allegro is initialised <allegro_native_dialog.h>
	if(!al_init()){ 
		std::cout<<"Could not load allegro"<<std::endl;
	}
	else
	{
		std::cout<<"loaded allegro"<<std::endl;
	}
	
	al_install_keyboard();// will initialize keyboard events
	al_init_image_addon();
	al_init_font_addon();
	al_init_ttf_addon();
	if (!al_init_primitives_addon())
	{
		std::cout<<"Could not init primitives"<<std::endl;
	}
	else
	{
		std::cout<<"allegro primitives loaded"<<std::endl;
	}


	display = al_create_display(WIDTH,HEIGHT);

	//==============================================
	//PROJECT INIT
	//==============================================
	font18 = al_load_font("font\\arial.ttf", 18, 0);
	font11 = al_load_font("font\\arial.ttf", 11, 0);
	if(!font18 || !font11)
	{
		std::cout<<"failed to load font 18"<<std::endl;
	}
	else
	{
		std::cout<<"loaded font 18"<<std::endl;
	}



	bgImage = al_load_bitmap("image\\background.png");
	if(!bgImage){
		std::cout<<"Couldn't load tile image"<<std::endl;
	}
	else
	{
		std::cout<<"loaded bg image"<<std::endl;
	}

	PlayerImage = NULL;

	tileSheet = al_load_bitmap("image\\TileSet-1.fw.png");//World.png TileSet-1.fw.png
	if(!tileSheet){
		std::cout<<"Couldn't load tile image"<<std::endl;
	}
	else
	{
		std::cout<<"loaded bg image"<<std::endl;
	}

	bg = new World(tileSheet,"map/map.map", bgImage);
	std::cout<<"stage loaded"<<std::endl;
	//objects.push_back(bg);

	player1 = new Player(PlayerImage);
	std::cout<<"Player loaded"<<std::endl;
	objects.push_back(player1);

	cam = new Camera(0,0);
	std::cout<<"Camera loaded"<<std::endl;


	eventQueue = al_create_event_queue();
	std::cout<<"eventQueue created"<<std::endl;
	timer = al_create_timer(1.0 / FPS);
	std::cout<<"timer created"<<std::endl;

	al_register_event_source(eventQueue, al_get_timer_event_source(timer));
	al_register_event_source(eventQueue, al_get_keyboard_event_source());

	al_start_timer(timer);





}


void Game::shutdownGameEngine()
{
	//==============================================
	//DESTROY ALLEGRO OBJECTS
	//==============================================
	for(iter = objects.begin(); iter != objects.end(); )
	{
		//(*iter)->Destroy();
		delete (*iter);
		iter = objects.erase(iter);
	}

	al_destroy_bitmap(image);
	al_destroy_bitmap(bgImage);
	al_destroy_bitmap(tileSheet);
	al_destroy_bitmap(PlayerImage);
	al_destroy_font(font18);
	al_destroy_font(font11);
	al_destroy_event_queue(eventQueue);
	al_destroy_display(display);
	al_destroy_timer(timer);
	//delete input;
}

void Game::processGameEngine()
{
	while(!done){
		al_wait_for_event(eventQueue, &ev); // tells the eventQueue wait for an input

		//key pressed
		if (ev.type==ALLEGRO_EVENT_KEY_DOWN){
			switch(ev.keyboard.keycode){
			case ALLEGRO_KEY_ESCAPE: 
				done = true;
				break;
			case ALLEGRO_KEY_BACKSPACE:
				done = true;
				break;
			case ALLEGRO_KEY_LEFT: 
				keys[LEFT]=true;
				break;
			case ALLEGRO_KEY_RIGHT: 
				keys[RIGHT]=true;
				break;
			case ALLEGRO_KEY_SPACE: 
				keys[SPACE]=true;
				break;

			}
		}

		//key released
		else if(ev.type == ALLEGRO_EVENT_KEY_UP)
		{
			switch(ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_ESCAPE:
				done = true;
				break;
			case ALLEGRO_KEY_BACKSPACE:
				done = true;
				break;
			case ALLEGRO_KEY_LEFT: 
				keys[LEFT]=false;
				break;
			case ALLEGRO_KEY_RIGHT: 
				keys[RIGHT]=false;
				break;
			case ALLEGRO_KEY_SPACE: 
				keys[SPACE]=false;
				break;

			}

		}

		//==============================================
		//Game UPDATE
		//==============================================		
		else if (ev.type == ALLEGRO_EVENT_TIMER){
			render=true;

			//UPDATE FPS===========
			frames++;
			if(al_current_time() - GameTime >= 1)
			{
				GameTime = al_current_time();
				gameFPS = frames;
				frames = 0;
			}

			//LEFT 
			if(keys[LEFT])
			{
				//dir = -1;
				//World::coord.x= World::velX * World::dirX;
				player1->moveLeft();

				//what if the Player wants to jump while moving?
				if(keys[SPACE])
				{
				if (player1->isJumpAllowed()){
					player1->setJump();
					}
				} //jumping
			}
			//or RIGHT
			else if(keys[RIGHT])
			{
				//dir = 1;
				player1->moveRight();
				
				//what if the Player wants to jump while moving?
				if(keys[SPACE])
				{
				if (player1->isJumpAllowed()){
					player1->setJump();
					} //jumping
				}
			}
			//or jumping
			else if(keys[SPACE])
			{
				if (player1->isJumpAllowed()){
					player1->setJump();
					//what if the Player wants move right while jumping?
					if(keys[RIGHT])
					{
						//dir = 1;
						player1->moveRight();
					}
					//what if the Player wants move left while jumping?
					else if(keys[LEFT])
					{
						//dir = -1;
						player1->moveLeft();
					}
				}
			}

			//or default position
			else
			{
				//dir = 0;
				player1->resetAnimation();
			}

			bg->update();
			

			//for(iter = objects.begin(); iter != objects.end(); ++iter)
			//{
			//	(*iter)->Update();
			//}
			player1->update(bg->getMap());
			//player1->update();
			cam->update();

		}

		//==============================================
		//RENDER
		//==============================================
		if(render && al_is_event_queue_empty(eventQueue))
		{
			render = false;
			//al_draw_textf(font18, al_map_rgb(255, 0, 255), 5, 5, 0, "FPS: %i", gameFPS); // display Game FPS on screen

			
			bg->render();
			for(iter = objects.begin(); iter != objects.end(); ++iter)
					(*iter)->render();
			//al_draw_bitmap_region(image, curFrame * frameWidth,0, frameWidth, frameHeight, x,y,0);

			if (debug)
			{
				showDebugMode();
			}
			al_flip_display();

		
			al_clear_to_color(al_map_rgb(0,0,0)); //that prevents the filled Rect draw imga just like snake style

		} //end render
	}//end while done
}

//int main()
//{
//
//	// call our engine initialization function
//	initializeGameEngine();
// 
//	// call our engine process function
//	processGameEngine();
// 
//	// call our engine shutdown function
//	shutdownGameEngine();
// 
//	// terminate the program
//	return 0;
//	
//}
