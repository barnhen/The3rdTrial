#include "Game.h"


std::list<GameObject *> objects;
std::list<GameObject *>::iterator iter;
/*#######################################################################
  coord is defined outised the header by the "One Definition Rule". 
  It means that the var created from GameObejct will have tha same value
  for every class tha can access this var
  #######################################################################
 */
//Rect GameObject::coord;
//bool keys[] = {false, false, false, false, false, false,false,false};
//enum KEYS{UP, DOWN, LEFT, RIGHT, SPACE, C,E,P};
//bool keyHold = false;
//int dir = 0;


// don't forget to put allegro-5.0.10-monolith-md-debug.lib
//==============================================
//SHELL VARIABLES
//==============================================
bool done = false;
bool render = false;

float gameTime = 0;
int frames = 0;
//int gameFPS = 0;
const int FPS = 60;
double fps = 0.0;
bool debug = true;
//state =-1;

//==============================================
//ALLEGRO VARIABLES
//==============================================
ALLEGRO_DISPLAY *display = NULL;
ALLEGRO_EVENT_QUEUE *eventQueue = NULL;
ALLEGRO_TIMER *timer;
ALLEGRO_BITMAP *image = NULL;
ALLEGRO_FONT *font18 = NULL;
ALLEGRO_FONT *font11 = NULL;
ALLEGRO_BITMAP *worldImage = NULL;
ALLEGRO_BITMAP *PlayerImage = NULL;
//ALLEGRO_BITMAP *tileSheet=NULL;
ALLEGRO_EVENT ev;


//==============================================
//PROJECT VARIABLES
//==============================================
World world;
Player *player1; 
Camera cam;

Game::Game(void)
{
}


Game::~Game(void)
{

}

double Game::calcFPS() {
	static double old_time = 0.0;
	double new_time = al_get_time();
    double delta = new_time - old_time;
    double gameFPS = 1.0/(delta);
    old_time = new_time;
	//UPDATE FPS===========
	//double gameFPS = 0.0;
	//frames++;
	//if(al_current_time() - gameTime >= 1)
	//{
	//	gameTime = al_current_time();
	//	gameFPS = frames;
	//	frames = 0;
	//}
	return gameFPS;
}

void Game::showDebugMode(void)
{
	//al_init_font_addon();
	//al_init_ttf_addon();
	al_draw_textf(font18, al_map_rgb(255, 255, 0), 5, 5, 0, "FPS: ", fps); // display Game FPS on screen
	al_draw_textf(font18, al_map_rgb(255, 255, 0), 105, 5, 0, "STATE: %d", state); // display state
	al_draw_textf(font11, al_map_rgb(255, 255, 0), 5, 25, 0, "cam Focus x: %.2f", cam.getFocus().x); 
	al_draw_textf(font11, al_map_rgb(255, 255, 0), 150, 25, 0, "camera is moving with X: %.2f", cam.getPosition().x); 
	al_draw_textf(font11, al_map_rgb(255, 255, 0), 300, 25, 0, "Player posX: %.0f", player1->getX()); 
	al_draw_textf(font11, al_map_rgb(255, 255, 0), 450, 25, 0, "Player posY: %.0f", player1->getY()); 
	al_draw_textf(font11, al_map_rgb(255, 255, 0), 5, 35, 0, "Player box x: %.2f", player1->getRect().x);
	al_draw_textf(font11, al_map_rgb(255, 255, 0), 150, 35, 0, "Player box y: %.2f", player1->getRect().y);
	al_draw_textf(font11, al_map_rgb(255, 255, 0), 300, 35, 0, "CAM POSX: %.d", cam.getPosX());
	al_draw_textf(font11, al_map_rgb(255, 255, 0), 450, 35, 0, "Player x vel: %.2f", player1->getRect().vX);
	al_draw_textf(font11, al_map_rgb(255, 255, 0), 5, 45, 0, "Player y vel: %.2f", player1->getRect().vY);

	al_draw_textf(font11, al_map_rgb(255, 255, 0), 150, 45, 0, "Player desX: %.2f", player1->getDestRect().x); 
	al_draw_textf(font11, al_map_rgb(255, 255, 0), 300, 45, 0, "Player desY: %.2f", player1->getDestRect().y);
	al_draw_textf(font11, al_map_rgb(255, 255, 0), 450, 45, 0, "Player desW: %.2f", player1->getDestRect().w);
	//al_draw_textf(font11, al_map_rgb(255, 255, 0), 400, 45, 0, "Player desH: %.2f", player1->getDestRect().h);


	//al_draw_textf(font11, al_map_rgb(255, 255, 0), 5, 55, 0, "map is moving with mapX x: %.2f", world.getMapPosX()); 
	al_draw_textf(font11, al_map_rgb(255, 255, 0), 100, 55, 0, "world map width: %i", world.getWidth()); 
	al_draw_textf(font11, al_map_rgb(255, 255, 0), 200, 55, 0, "world map height: %.i", world.getHeight()); 
	al_draw_textf(font11, al_map_rgb(255, 255, 0), 300, 55, 0, "world blockrect y: %.2f", world.getDestRect().y);
	//al_draw_textf(font11, al_map_rgb(255, 255, 0), 400, 55, 0, "collision time: %.2f", player1->getCollisionTime());
	al_draw_textf(font11, al_map_rgb(255, 255, 0), 400, 55, 0, "map is moving with mapX x: %.2f", world.getMapPosX()); 


	//al_draw_textf(font11, al_map_rgb(255, 255, 0), 5, 65, 0, "Cam x: %.2f", cam.getX()); 
	//al_draw_textf(font11, al_map_rgb(255, 255, 0), 100, 65, 0, "Cam y: %.2f", cam.getY()); 
	al_draw_textf(font11, al_map_rgb(255, 255, 0), 200, 65, 0, "Cam pos x: %.2f", cam.getPosition().x); 
	al_draw_textf(font11, al_map_rgb(255, 255, 0), 300, 65, 0, "Cam pos y: %.2f", cam.getPosition().y); 
	al_draw_textf(font11, al_map_rgb(255, 255, 0), 400, 65, 0, "Cam target mode: %s", cam.getCameraTargetMode());

	al_draw_textf(font11, al_map_rgb(255, 255, 0), 5, 75, 0, "cam focus x: %.2f", cam.getFocus().x); 
	al_draw_textf(font11, al_map_rgb(255, 255, 0), 100, 75, 0, "cam focus y: %.2f", cam.getFocus().y); 
	//al_draw_textf(font11, al_map_rgb(255, 255, 0), 200, 65, 0, "cam pos x: %2.f", cam.getPosition().x); 
	//al_draw_textf(font11, al_map_rgb(255, 255, 0), 300, 65, 0, "cam pos y: %2.f", cam.getPosition().y); 
	//al_draw_textf(font11, al_map_rgb(255, 255, 0), 400, 75, 0, "cam target mode: %s", cam.getCameraTargetMode());


	al_draw_textf(font11, al_map_rgb(255, 255, 0), 5, 85, 0, "Scrolling: %s", player1->getIsScrolling()?"true":"false"); 
	//al_draw_textf(font11, al_map_rgb(255, 255, 0), 100, 85, 0, "Camera X: %f", cam.getX()); 
	al_draw_textf(font11, al_map_rgb(255, 255, 0), 300, 85, 0, "Player coord X: %.0f", player1->getX());
	al_draw_textf(font11, al_map_rgb(255, 255, 0), 5, 95, 0, "Player world start bound: %i", world.getStartMapBoundaries());
	al_draw_textf(font11, al_map_rgb(255, 255, 0), 400, 95, 0, "Player world end bound: %i", world.getEndMapBoundaries());
	al_draw_textf(font11, al_map_rgb(255, 255, 0), 5, 105, 0, player1->getDebugPlayerMov()); 
	al_draw_textf(font11, al_map_rgb(255, 255, 0), 400, 105, 0, player1->getDebugPlayerCollision()); 




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
	state =-1;
	isPaused = false;
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



	//worldImage = al_load_bitmap("image\\background.png");
	//if(!worldImage){
	//	std::cout<<"Couldn't load tile image"<<std::endl;
	//}
	//else
	//{
	//	std::cout<<"loaded world image"<<std::endl;
	//}

	PlayerImage = NULL;

	//tileSheet = al_load_bitmap("image\\TileSet-1.fw.png");//World.png TileSet-1.fw.png
	//if(!tileSheet){
	//	std::cout<<"Couldn't load tile image"<<std::endl;
	//}
	//else
	//{
	//	std::cout<<"loaded world image"<<std::endl;
	//}

	//world = new World(tileSheet,"map/map.map", worldImage);
	//world = new World();
	//if (!world.loadMap("map/map.map"))
	if (!world.load_map("map/map.ini"))

	{
		std::cout << "error loading map" << std::endl;
        std::exit(1);
	}
	std::cout<<"stage loaded"<<std::endl;
	//objects.push_back(world);

	cam.setSize(WIDTH,HEIGHT);

	player1 = new Player(30,0,40,64,4.0,0,8, PlayerImage);
	std::cout<<"Player loaded"<<std::endl;
	//will call the init() method from Character which is superclass of player
	player1->init();
	//player1->init(380,0,40,64,0,0,8); //starting x,y, width, height, vX and vy
	
	cam.setFocusedCharacter(player1);

	objects.push_back(player1);

	//cam = new Camera(0,0);
	std::cout<<"Camera loaded"<<std::endl;

	world.set_always_redraw(true);
	world.setMapVisibleSize(cam.getWidth(), cam.getHeight());
	world.addCharacter(player1);

	//##################################################################################################
	// Here will define at what point the program will start at: Tile screen, menu, gameplay, credits...
	//##################################################################################################
	changeState(state, GameState::PLAYING);

	
	
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
	al_destroy_bitmap(worldImage);
	//al_destroy_bitmap(tileSheet);
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

		//if user closes window then application will shut down
		if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) 
		{
				done = true;
		}

		if (ev.type == ALLEGRO_EVENT_KEY_DOWN) 
		{
			// hitting ESC key also shuts the application.
			if (ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE) 
			{
				done = true;
			}
			
			else if (ev.keyboard.keycode == ALLEGRO_KEY_BACKSPACE) 
			{
				done = true;
			}
		}

		if (state == GameState::PLAYING)
		{
		
			player1->handleInput(ev);

				if (isPaused)
				{
					//al_start_timer(timer);
					//al_flip_display();
					isPaused = false;
				}
				else
				{
					//al_stop_timer(timer);
					//al_flip_display();
					isPaused = true;
				}

		} // if (state == GameState::PLAYING)

		//==============================================
		//Game UPDATE
		//==============================================		
		//else if (ev.type == ALLEGRO_EVENT_TIMER){
		if (ev.type == ALLEGRO_EVENT_TIMER){
			render=true;

			////UPDATE FPS===========
			//frames++;
			//if(al_current_time() - gameTime >= 1)
			//{
			//	gameTime = al_current_time();
			//	gameFPS = frames;
			//	frames = 0;
			//}
						
			//for(iter = objects.begin(); iter != objects.end(); ++iter)
			//{
			//	(*iter)->Update();
			//}
			//world.update();
			//player1->update(world.getMap());
			player1->update();
			
			cam.update();
			//cam.update(player1->getRect().x, player1->getRect().y);
			Rect cameraPos = cam.getPosition();
			//
			Rect cameraFocus;
			cameraFocus.x = 0.0;
			cameraFocus.y = 0.0;

			//update camera position and focus (respecting the x and y returned by world::setMapPos)
            //world.setMapPos(cameraPos.x, cameraPos.y);
			world.setMapPos(cameraPos.x, cameraPos.y);

			//std::cout<<"cameraPos.x is="<<cameraPos.x<<std::endl;
			//std::cout<<"cameraPos.y is="<<cameraPos.y<<std::endl;
			cameraFocus.x = cameraPos.x + WIDTH/2; // here will me center of screen measure the point where the player will scroll the background
			cameraFocus.y = cameraPos.y + HEIGHT/2; // here will me center of screen measure the point where the player will scroll the background
   //             
            cam.setPosition(cameraPos.x, cameraPos.y);
            cam.setFocus(cameraFocus.x, cameraFocus.y);

			fps = calcFPS();
		}

		//==============================================
		//RENDER
		//==============================================
		if(render && al_is_event_queue_empty(eventQueue))
		{
			render = false;
			//al_draw_textf(font18, al_map_rgb(255, 0, 255), 5, 5, 0, "FPS: %i", gameFPS); // display Game FPS on screen

			
			//world.render(); // to uncomment
			world.draw(); //barnhen to uncomment
			for(iter = objects.begin(); iter != objects.end(); ++iter)
					(*iter)->render();
			//al_draw_bitmap_region(image, curFrame * frameWidth,0, frameWidth, frameHeight, x,y,0);

			if (debug)
			{
				showDebugMode();
			}

			// Draw the collision rectangles
			if (player1->isCharBoundingBoxVisible())
			{
				//std::cout<<"show bounding box"<<std::endl;
				//al_draw_filled_rectangle(player1->getCollisionRect().x, player1->getCollisionRect().y,player1->getCollisionRect().x + player1->getCollisionRect().w ,player1->getCollisionRect().y + player1->getCollisionRect().h, al_map_rgba(255,200,255,100));
				al_draw_filled_rectangle(player1->getTopTileRect().x, player1->getTopTileRect().y,player1->getTopTileRect().x + player1->getTopTileRect().w ,player1->getTopTileRect().y + player1->getTopTileRect().h, al_map_rgba(155,200,255,100));
				al_draw_filled_rectangle(player1->getBottomTileRect().x, player1->getBottomTileRect().y,player1->getBottomTileRect().x + player1->getBottomTileRect().w ,player1->getBottomTileRect().y + player1->getBottomTileRect().h, al_map_rgba(0,0,255,100));
				al_draw_filled_rectangle(player1->getMiddleLeftTileRect().x, player1->getMiddleLeftTileRect().y,player1->getMiddleLeftTileRect().x + player1->getMiddleLeftTileRect().w ,player1->getMiddleLeftTileRect().y + player1->getMiddleLeftTileRect().h, al_map_rgba(255,0,0,100));
				al_draw_filled_rectangle(player1->getMiddleRightTileRect().x, player1->getMiddleRightTileRect().y,player1->getMiddleRightTileRect().x + player1->getMiddleRightTileRect().w ,player1->getMiddleRightTileRect().y + player1->getMiddleRightTileRect().h, al_map_rgb(0,95,0));
				al_draw_filled_rectangle(world.getBlockRect().x, world.getBlockRect().y,world.getBlockRect().x + world.getBlockRect().w ,world.getBlockRect().y + world.getBlockRect().h, al_map_rgb(95,95,0));
				//SDL_SetRenderDrawColor(mRenderer, 255, 0, 0, 255);
				//SDL_RenderFillRect(mRenderer, &mRobot->GetBottomTileRect());
				//SDL_SetRenderDrawColor(mRenderer, 150, 0, 0, 255);
				//SDL_RenderFillRect(mRenderer, &mRobot->GetTopTileRect());
				//SDL_SetRenderDrawColor(mRenderer, 255, 255, 0, 255);
				//SDL_RenderFillRect(mRenderer, &mRobot->GetCollisonRect());
			}

			al_flip_display();

		
			al_clear_to_color(al_map_rgb(0,0,0)); //that prevents the filled Rect draw imga just like snake style

		} //end render
	}//end while done
}


//TODO: To implement
void Game::changeState(int &state, int newState)
{
	//things to do before changing to state to the new value
	if(state == GameState::TITLE){
	
	}
	else if (state == GameState::PLAYING){
		//al_stop_sample_instance(songInstance);
	}
	else if (state == GameState::LOST){
	
	}

	//after that we switch the game state
	state = newState;
	
	// and then we do things with the new state
	if(state == GameState::TITLE){
	
	}
	else if (state == GameState::PLAYING){
		//InitShip(ship);
		//InitBullet(bullets, NUM_BULLETS);
		//InitComet(comets, NUM_COMETS);
		//InitExplosions(explosions, NUM_EXPLOSIONS);
	
		//al_play_sample_instance(songInstance);
	}
	else if (state == GameState::LOST){
	
	}
}