#include "player.h"

int leftScrolled = 0;
background *theBg;
bool isMoving = false;
//isScrolling = false;
//bool ground = false;
//bool jump = false;
//bool nc = false; // non collision





player::player(ALLEGRO_BITMAP *pImg)
{
	playerImg = pImg;
	player::tileSize =50;
	isScrolling = 0; // false
	//coord.x = 80; // player starting x position
	//coord.y = 0;
	//coord.w = player::tileSize;
	//coord.h = player::tileSize;


	box.x = 80; // player starting x position
	box.y = 0;
	box.w = player::tileSize;
	box.h = player::tileSize;

	camera.x = 80; // player starting x position
	camera.y = 0;
	camera.w = player::tileSize;
	camera.h = player::tileSize;

	pos.x = 80; // player starting x position
	pos.y = 0;
	pos.w = player::tileSize;
	pos.h = player::tileSize;



	player::velX = 0;
	player::dirX = 0;
	player::velCamX = 0;

	ground = false;
	jump = false;
	nc = false; // non collision


}


player::~player(void)
{
}

void player::Init(ALLEGRO_BITMAP *pImg)
{
}




void player::Render()
{
	al_draw_filled_rectangle(player::box.x, player::box.y,player::box.x + player::box.w ,player::box.y + player::box.h, al_map_rgba(255,0,255,100));
	//al_draw_filled_rectangle(player::coord.x, player::coord.y,player::coord.x + player::box.w ,player::coord.y + player::box.h, al_map_rgba(255,0,255,100));
	//al_draw_filled_rectangle(200, 100,tileSize,tileSize, al_map_rgba(255,0,255,100));

}

void player::SetVel(int vel)
{
	velX = vel;
	//velY = vel;
	velPosX = vel;
	//velCamX = vel;
	//velCamY = vel;
	velCoordX = vel;
	//velCoordY = vel;
}


void player::SetCoordXvel(int vel)
{
	velCoordX = vel;
}


void player::SetXvel(int vel)
{
	velX = vel;
}

void player::SetYvel(int vel)
{
	velY = vel;
}


void player::SetCamXvel(int cVel)
{
	velCamX = cVel;
}

void player::SetCamYvel(int cVel)
{
	velCamY = cVel;
}

void player::SetPosXvel(int cVel)
{
	velPosX = cVel;
}

void player::SetPosYvel(int cVel)
{
	velPosY = cVel;
}


void player::Update(std::vector<std::vector<int> >& map)
{
	//player::SetVel(4);

	//####################GRAVITY AND COLICION WITH BG TILES#################BEGIN###################
	int start = ( base::coord.x - (base::coord.x % theBg->GetTileSize())) / theBg->GetTileSize();
	int end = (base::coord.x + base::coord.w + (theBg->GetTileSize() - (base::coord.x + base::coord.w) % theBg->GetTileSize())) / 50;
	
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
			sprite destrect =  { j * 50 - base::coord.x,i * 50, 50, 50 };
			//al_draw_filled_rectangle(destrect.x, destrect.y,destrect.w,destrect.h, al_map_rgba(255,0,255,100));

			
			if (collision(&
				, &destrect))
			{
				nc = true;
				//below condition make the player hit the ground when he falls by gravity
				//if (isScrolling == 1) 
				//{
					if(destrect.y >= box.y + pos.h - 11)
					{
						ground = true;
						velY= 0 ;
					}
					else if (destrect.y + destrect.h <= box.y + 11)
					{
						player::box.x = player::box.x - player::velX;
						//player::coord.x = player::coord.x - player::velX;
						velY = 5; // this will be gravity
					}

					//horizontal box collision check begin
					//will stop the player the pass through box on x direction
					//pushing to left
					if (pos.x + pos.w >= destrect.x - 5 && 
						box.y + pos.h >= destrect.y + 6 && 
						pos.x + pos.w <= destrect.x +20)
					{
						player::box.x = player::box.x - player::velX; // we stop the player from moving to right
						player::pos.x = player::pos.x - player::velPosX; // we stop the posx of player from increasing

						if (isScrolling == 1) {player::coord.x = player::coord.x - player::velPosX;std::cout<<"pushing left col"<<std::endl;}
					
						std::cout<<"pushing left"<<std::endl;
						//std::cout<<"destrect push right if is "<<destrect.x<<std::endl;

					}
					//pushing to right
					else if (pos.x - box.w <= destrect.x + destrect.w + 40 &&
							 box.y + pos.h >= destrect.y + 6)
					{
						//posx=344 box.w=50 destrect.x=228 destrect.w=50 destrect.y
						//player::box.x = player::box.x + player::velX; // we stop the player from moving to right
						//player::pos.x = player::pos.x + player::velPosX; // we stop the posx of player from increasing
						player::box.x = player::box.x - player::velX; // we stop the player from moving to left
						player::pos.x = player::pos.x + player::velPosX; // we stop the posx of player from decreasing

						if (isScrolling == 1) {player::coord.x = player::coord.x + player::velCoordX;std::cout<<"pushing right col"<<std::endl;}// we stop the posx of player from increasing


					
						//SetXvel(0);
						//SetCamXvel(0);

						std::cout<<"pushing right"<<std::endl;
					}
					//horizontal box collision check end
				//} // end if isScrolling
			}// end if collision(&box, &destrect)
		} //end for j < end
	}// end for map.size()
	//below will make the gravity work on the player. he will fall
	if (!nc && !jump) // not colliding nor jumping
	{
		SetYvel(5);
		//std::cout<<"not coliding or jumping"<<std::endl;
		//box.y -= 5;
	}

	//below will make the player start falling after jumping and hit the ground again
	if (jump && velY < 5)
	{
		//SetYvel(velY++);
		velY++;
	}
	else
	{
		jump = false;
	}
	//
	////box.x += velX;
	////box.y += velY;
	//####################GRAVITY AND COLICION WITH BG TILES#################END###################
	
	//####### WILL UPDATE BOX MOVEMENT###############
	player::box.x += player::velX * player::dirX;
	//jumping
	player::box.y += player::velY;
	
	//####### WILL UPDATE ABSOLUTE MAP COORDINATES###############
	if (isScrolling==1) //not scrolling
	{
		player::coord.x += player::velCoordX * player::dirX;
		//player::coord.y += player::velCoordY * player::dirY;

	}

	//####### WILL UPDATE ABSOLUTE POSITION COORDINATES###############
	player::pos.x += player::velPosX * player::dirX;
	//player::camera.x += player::velCamX * player::dirX;
	//player::camera.y += player::velCamY;
	//player::camera.y += player::velY;


}
void player::MoveLeft(std::vector<std::vector<int> > themap)
{
	player::dirX = -1;
	//player::SetCamXvel(1); //old 4
	//player::SetCoordXvel(4);
	//player::SetVel(4);
	//player::SetXvel(4); // to comment


	// if player is in the most right side of scenario limit and wants to walk left untill the mmiddle of screen
	// because we are skippn n x camera vel to scroll left we have to include the velCamX to condition
	if(player::GetPos().x - player::velPosX > (900 - WIDTH/2) - box.w)
	{
		isScrolling = 0;
		//std::cout<<"limit right <left> border"<<900 - WIDTH/2<<std::endl;
		player::SetVel(4);
	}
	// because we are skippn n x camera vel to scroll left we have to include the velCamX to condition
	else if (player::GetPos().x - player::velPosX > WIDTH/2 - box.w)
	{
		isScrolling = 1;
		player::SetXvel(0); //old 0
		player::SetCoordXvel(4);
		//player::coord.x--;
		//below lies the problem when colling to the left the camera scrolls to right when it is suppoesed to stop
		//player::coord.x = player::coord.x - player::velX;
		//player::coord.x += player::velX * player::dirX;

	}
	// if player is in the most left side of scenario limit and wants to walk right untill the mmiddle of screen
	// because we are skipping n x camera vel to scroll left we have to include the velCamX to condition
	else
	{
		isScrolling = 0;
		player::SetVel(4);
		//player::SetCoordXvel(0);
		//player::coord.x = player::coord.x + player::velCoordX;

	}

	//player::Move(themap);
	// border limit

	//player::camera.x--;

	//if(player::camera.x < 0)
	//{
		//std::cout<<"Reached left border limit"<<std::endl;
		//player::camera.x = 0;
	//}
	//else
	//{
	//}

}

void player::MoveRight(std::vector<std::vector<int> > themap)
{
	player::dirX =1;
	//player::SetCamXvel(4);
	//player::SetVel(4);
	//player::SetXvel(4); // to comment

	// player will move from most left part (scenario beginning)) untill the midle of screen
	if (player::GetPos().x < WIDTH/2 - box.w) // middle of screen minus the frame width to center it -> 640/2 - 50 = 270
	{
		isScrolling = 0;
		player::SetVel(4);
	}
	// if player is in the most right side of scenario limit and wants to walk left untill the mmiddle of screen
	// because we are skippn n x camera vel to scroll left we have to include the velCamX to condition
	else if(player::GetPos().x > (900 - WIDTH/2) - box.w)
	{
		isScrolling = 0;
		//std::cout<<"limit right border"<<900 - WIDTH/2<<std::endl;
		player::SetVel(4);
	}
	// in the middle the player will scroll right
	else
	{
		if (player::GetPos().x > (900 - WIDTH/2 - box.w))
		{
			player::SetVel(4);
			/*player::SetCoordXvel(0);*/
		}
		else
		{
			isScrolling = 1; //true
			player::SetXvel(0); //old 0
			player::SetCoordXvel(4);
			//player::coord.x++;
			//player::coord.x += player::velCamX * player::dirX;; // this is the point which scroll the background
		}
	}

	//player::Move(themap);
	

	//player::camera.x++;

	//if(player::camera.x < 0)
	//{
	//	player::camera.x = 0;
	//}
	//else
	//{
	//}

}

void player::SetJump()
{
	if (ground && !jump)
	{
		jump = true;
		ground = false;
		SetYvel(-17); //velocity from jumping from ground to mid-air until reaches 0 and it increase from 0 to more until reaches the ground
		box.y -= 5;
	}
	
}

void player::Move(std::vector<std::vector<int> >& map)
{
}

void player::ResetAnimation(std::vector<std::vector<int> > themap)
{
	player::dirX = 0;
	//player::Move(themap);
}

