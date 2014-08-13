#include "game.h"


std::list<base *> objects;
std::list<base *>::iterator iter;
sprite base::coord;
bool keys[] = {false, false, false, false, false, false,false};
enum KEYS{UP, DOWN, LEFT, RIGHT, SPACE, C,E};


// don't forget to put allegro-5.0.10-monolith-md-debug.lib
//==============================================
//SHELL VARIABLES
//==============================================
bool done = false;
bool render = false;

float gameTime = 0;
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
ALLEGRO_BITMAP *playerImage = NULL;
ALLEGRO_BITMAP *tileSheet=NULL;
ALLEGRO_EVENT ev;


//==============================================
//PROJECT VARIABLES
//==============================================
background *bg;
player *player1; 

game::game(void)
{
}


game::~game(void)
{

}

void ShowDebugMode(void)
{
	//al_init_font_addon();
	//al_init_ttf_addon();
	al_draw_textf(font18, al_map_rgb(255, 255, 0), 5, 5, 0, "FPS: %i", gameFPS); // display game FPS on screen
	al_draw_textf(font11, al_map_rgb(255, 255, 0), 5, 25, 0, "player x vel: %i", player1->GetXVel()); 
	al_draw_textf(font11, al_map_rgb(255, 255, 0), 90, 25, 0, "player dirX: %i", player1->GetDirX()); 
	al_draw_textf(font11, al_map_rgb(255, 255, 0), 180, 25, 0, "player posX: %i", player1->GetPos()); 
	al_draw_textf(font11, al_map_rgb(255, 255, 0), 270, 25, 0, "player box x: %i", player1->GetRect().x);
	al_draw_textf(font11, al_map_rgb(255, 255, 0), 360, 25, 0, "player box y: %i", player1->GetRect().y);
	al_draw_textf(font11, al_map_rgb(255, 255, 0), 450, 25, 0, "player cam x: %i", player1->GetCamera().x);
	al_draw_textf(font11, al_map_rgb(255, 255, 0), 540, 25, 0, "player y vel: %i", player1->GetYVel());


	al_draw_textf(font11, al_map_rgb(255, 255, 0), 180, 35, 0, "bg coord x: %i", bg->GetCoordX()); 
	al_draw_textf(font11, al_map_rgb(255, 255, 0), 270, 35, 0, "bg bomapx x: %i", bg->GetMapSize()); 

	al_draw_textf(font11, al_map_rgb(255, 255, 0), 180, 45, 0, "Scrolling: %s\n", player1->GetIsScrolling()?"true":"false"); 


}


void initializeGameEngine ()
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


	if(!font18)
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

	playerImage = NULL;

	tileSheet = al_load_bitmap("image\\TileSet-1.fw.png");//background.png TileSet-1.fw.png
	if(!tileSheet){
		std::cout<<"Couldn't load tile image"<<std::endl;
	}
	else
	{
		std::cout<<"loaded bg image"<<std::endl;
	}

	bg = new background(tileSheet,"map.map", bgImage);
	objects.push_back(bg);

	player1 = new player(playerImage);
	objects.push_back(player1);

	eventQueue = al_create_event_queue();
	std::cout<<"eventQueue created"<<std::endl;
	timer = al_create_timer(1.0 / FPS);
	std::cout<<"timer created"<<std::endl;

	al_register_event_source(eventQueue, al_get_timer_event_source(timer));
	al_register_event_source(eventQueue, al_get_keyboard_event_source());

	al_start_timer(timer);





}


void shutdownGameEngine()
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
	al_destroy_bitmap(playerImage);
	al_destroy_font(font18);
	al_destroy_font(font11);
	al_destroy_event_queue(eventQueue);
	al_destroy_display(display);
	al_destroy_timer(timer);
	//delete input;
}

void processGameEngine()
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
		//GAME UPDATE
		//==============================================		
		else if (ev.type == ALLEGRO_EVENT_TIMER){
			render=true;

			//UPDATE FPS===========
			frames++;
			if(al_current_time() - gameTime >= 1)
			{
				gameTime = al_current_time();
				gameFPS = frames;
				frames = 0;
			}

			//LEFT 
			if(keys[LEFT])
			{
				//background::coord.x= background::velX * background::dirX;
				player1->MoveLeft(bg->GetMap());

				//what if the player wants to jump while moving?
				if(keys[SPACE])
				{
				if (player1->IsJumpAllowed()){
					player1->SetJump();
					}
				} //jumping
			}
			//or RIGHT
			else if(keys[RIGHT])
			{
				player1->MoveRight(bg->GetMap());
				
				//what if the player wants to jump while moving?
				if(keys[SPACE])
				{
				if (player1->IsJumpAllowed()){
					player1->SetJump();
					} //jumping
				}
			}
			//or jumping
			else if(keys[SPACE])
			{
				if (player1->IsJumpAllowed()){
					player1->SetJump();
					//what if the player wants move right while jumping?
					if(keys[RIGHT])
					{
						player1->MoveRight(bg->GetMap());
					}
					//what if the player wants move left while jumping?
					else if(keys[LEFT])
					{
						player1->MoveLeft(bg->GetMap());
					}
				}
			}

			//or default position
			else
			{
				player1->ResetAnimation(bg->GetMap());
			}

			//bg->Update();


			for(iter = objects.begin(); iter != objects.end(); ++iter)
			{
				(*iter)->Update(bg->GetMap());
			}


		}

		//==============================================
		//RENDER
		//==============================================
		if(render && al_is_event_queue_empty(eventQueue))
		{
			render = false;
			//al_draw_textf(font18, al_map_rgb(255, 0, 255), 5, 5, 0, "FPS: %i", gameFPS); // display game FPS on screen

			

			for(iter = objects.begin(); iter != objects.end(); ++iter)
					(*iter)->Render();
			//al_draw_bitmap_region(image, curFrame * frameWidth,0, frameWidth, frameHeight, x,y,0);

			if (debug)
			{
				ShowDebugMode();
			}
			al_flip_display();

		
			al_clear_to_color(al_map_rgb(0,0,0)); //that prevents the filled rectangle draw imga just like snake style

		} //end render
	}//end while done
}

int main()
{

	// call our engine initialization function
	initializeGameEngine();
 
	// call our engine process function
	processGameEngine();
 
	// call our engine shutdown function
	shutdownGameEngine();
 
	// terminate the program
	return 0;
	
}
