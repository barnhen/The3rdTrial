#include "background.h"

background::background(ALLEGRO_BITMAP *bgSheet, char* filename, ALLEGRO_BITMAP *bgImage)
{
	//tileSize = 50;
	coord.x =  coord.y = 0;
	coord.w = WIDTH;
	coord.h = HEIGHT;
	bgImg = bgImage;
	tileImg = bgSheet;
	loadmap(filename);
	camera.x = camera.y = 0;
	camera.w = WIDTH;
	camera.h = HEIGHT;

}


background::~background(void)
{
	al_destroy_bitmap(bgImg);
}


void background::loadmap(const char* filename)
{
	std::ifstream in (filename);
	if(!in.is_open())
	{
		std::cout<<"Problem loading the file"<<std::endl;
	}
	int width,height;
	in >> width;
	in >> height;
	int current; //current block tile number
	for (int i = 0; i < height; i++)
	{
		std::vector<int> vec;

		for (int j = 0; j < width; j++)
		{
			if(in.eof())
			{
				std::cout<<"File end has reached too soon"<<std::endl;;
				return;
			}
			
			in >> current;
			//if (current == -1)
			//{
			//	enemies.push_back(new enemy(ene, j* 50, i * 50, 1, 0));
			//	vec.push_back(0);
			//}
			//else
			{
			//of all elements 1 to 7 tiles types we add every single one detected
				if (current>=0 && current <=7)
				{
		//			if (current == 3)
		//			{
		//				finish.x = j * 50;
		//				finish.y = i * 50;
		//			}
					vec.push_back(current);
				}
				//or we add the enemy
				else
				{
					vec.push_back(0);
				}
			}
		}
		map.push_back(vec);
	}
	in.close();
	//std::cout<< finish.x << " " << finish.y << std::endl;
}


void background::showmap()
{
	int start = ( base::coord.x - (coord.x % tileSize)) / tileSize;
	int end = (coord.x + coord.w + (tileSize - (coord.x + coord.w) % tileSize)) / 50;
	//std::cout<<"start"<<tileSize * map[0].size()<<std::endl;

	if (start < 0)
	{
		start=0;
	}
	if (end > map[0].size())
	{
		end = map[0].size();
	}

	for (int i = 0; i < map.size(); i++)
	{
		for (int j = 0; j < end; j++)
		{
			if (map[i][j] !=0)
			{
				//we calculate the position in the TileSet-1.bmp image
				sprite blockrect = {
										//because coord of tileset begins with 0 and not 1 I have to do (tilesize * tilenumber) minus 1
										(map[i][j]-1) * tileSize,0,tileSize,tileSize
									 };

				//destrect = destination rectangle and in the screen (so for example if the camera at 100px position and the tile is at 120px position, we show the tile at 20px position
				sprite destrect = {
										j * tileSize - coord.x, i*50
									};
				//SDL_BlitSurface(block, &blockrect,screen,&destrect);
				al_draw_bitmap_region(tileImg, blockrect.x,blockrect.y,blockrect.w,blockrect.h,destrect.x, destrect.y,0);
				//al_flip_display();

			}
		}

	}
}

void background::Update(std::vector<std::vector<int> >& map)
{
	//background::coord.x += background::velX * background::dirX;
	//if (background::coord.x + background::coord.w < 0)
	//{
	//	coord.x = 0;
	//}

}

void background::Render()
{
	al_draw_bitmap_region(bgImg, coord.x,coord.y,coord.w,coord.h,0,0,0);
	showmap();
}