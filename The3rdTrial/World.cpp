#include "World.h"

int World::start;
unsigned int World::end;

World::World(ALLEGRO_BITMAP *bgSheet, char* filename, ALLEGRO_BITMAP *bgImage)
{
	//tileSize = 50;
	//coord.x =  0;
	//coord.y = 0;
	//coord.w = WIDTH;
	//coord.h = HEIGHT;

	bgImg = bgImage;
	tileImg = bgSheet;
	loadmap(filename);
	box.x = box.y = 80;
	box.w = WIDTH;
	box.h = HEIGHT;

}

World::World(void)
{
}

World::~World(void)
{
}


void World::setBlockRectY(int y)
{
	blockrect.y = y;
}

void World::setDestRectY(int y)
{
	destrect.y = y;
}

void World::setMapPos(float& x, float& y)
{
	//coord.x = x;
	//coord.y = y;
	coord.x = 0;
	coord.y = 0;
	coord.w = WIDTH;
	coord.h = HEIGHT;
}


void World::loadmap(const char* filename)
{
	std::ifstream in (filename);
	if(!in.is_open())
	{
		std::cout<<"Problem loading the file"<<std::endl;
	}

	int mapWidth,mapHeight;
	in >> mapWidth;
	in >> mapHeight;
	
	//std::string line;
	//std::vector<std::string> lines;
	//while (std::getline(in, line))
	//{
	//	lines.push_back(line);
	//}

	//// Just outputs the file contents (for debugging)
	//for (unsigned i = 0; i < lines.size(); i++)
	//{
	//	std::cout << lines[i] << std::endl;
	//}


	std::cout<<"mapWidth"<<mapWidth<<std::endl;
	std::cout<<"mapHeight"<<mapHeight<<std::endl;
	int current; //current block tile number
	for (int i = 0; i < mapHeight; i++)
	{
		std::vector<int> vec;

		for (int j = 0; j < mapWidth; j++)
		{
			if(in.eof())
			{
				std::cout<<"File end has reached too soon"<<std::endl;
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
	//inteiro = 4;
	std::cout<<"map loaded"<< std::endl;
}


//void World::loadmap(const char* filename)
//{
//	std::ifstream in (filename);
//	if(!in.is_open())
//	{
//		std::cout<<"Problem loading the file"<<std::endl;
//	}
//
//	std::string line;
//	std::vector<std::string> lines;
//	while (std::getline(in, line))
//	{
//		lines.push_back(line);
//	}
//
//	// Just outputs the file contents (for debugging)
//	for (unsigned i = 0; i < lines.size(); i++)
//	{
//		std::cout << lines[i] << std::endl;
//	}
//
//	//unsigned int mapWidth,mapHeight;
//	
//	//in >> mapWidth;
//	//in >> mapHeight;
//	unsigned numRows = lines.size();
//	unsigned numCols = 0;
//
//
//	std::cout<<"mapWidth"<<numRows<<std::endl;
//	if (numRows > 0)
//	{
//		numCols = lines[0].length();
//		std::cout<<"numCols"<<numCols<<std::endl;
//		for (unsigned i = 1; i < numRows; i++)
//		{
//			if (lines[i].length() != numCols)
//			{
//				std::cerr << "*** Error: Inconsistent number of lines" << std::endl;
//				return;
//			}
//		}
//		
//		for (unsigned row = 0; row < numRows; row++)
//		{
//			std::vector<int> vec;
//			std::cout<<"Definig what to do with map grid components"<<std::endl;
//
//
//			//if(in.eof())
//			//{
//			//	std::cout<<"File end has reached too soon"<<std::endl;
//			//	//return;
//			//}
//
//			for (unsigned col = 0; col < numCols; col++)
//			{
//				char current = lines[row][col];
//				std::cout<<"current"<<current<<std::endl;
//				//Tile* tile = grid->GetTile(row, col);
//				if (current == -1)
//				{
//				//	enemies.push_back(new enemy(ene, j* 50, i * 50, 1, 0));
//				//	vec.push_back(0);
//				}
//				else
//				{
//				//of all elements 1 to 7 tiles types we add every single one detected
//					//if (current>=0 && current <=7)
//					if ((current == '0')
//					   ||(current == '1')
//					   ||(current == '2')
//					   ||(current == '3')
//					   ||(current == '4')
//					   ||(current == '5')
//					   ||(current == '6')
//					   ||(current == '7'))
//					{
//			//			if (current == 3)
//			//			{
//			//				finish.x = j * 50;
//			//				finish.y = i * 50;
//			//			}
//						vec.push_back(current);
//					}
//					//or we add the enemy
//					else
//					{
//						vec.push_back(0);
//					}
//				}
//			}
//			map.push_back(vec);
//
//		}
//		in.close();
//
//	}
//}
//



void World::showmap()
{
	//int start = ( GameObject::coord.x - (coord.x % tileSize)) / tileSize;
	//int end = (coord.x + coord.w + (tileSize - (coord.x + coord.w) % tileSize)) / 50;

	//std::cout<<"coord.x is "<<coord.x<<std::endl;
	unsigned int start = getStartMapBoundaries();
	unsigned int end = getEndMapBoundaries();


	//if (start < 0)
	//{
	//	start=0;
	//}
	//if (end > map[0].size())
	//{
	//	end = map[0].size();
	//}

	for (unsigned int i = 0; i < map.size(); i++)
	{
		for (unsigned int j = 0; j < end; j++)
		{
			if (map[i][j] !=0)
			{
				//we calculate the position in the TileSet-1.bmp image
				blockrect.x = (map[i][j]-1) * tileSize;
				//blockrect.y = 0; //original
				blockrect.y = (map[i][j]-1) * tileSize;
				blockrect.w = tileSize; 
				blockrect.h = tileSize;

				//rectangle blockrect = {
				//						//because coord of tileset begins with 0 and not 1 I have to do (tilesize * tilenumber) minus 1
				//						(map[i][j]-1) * tileSize,0,tileSize,tileSize										
				//					 };
				//std::cout<<"blockrect.x"<<blockrect.x<<"|blockrect.y"<<blockrect.y<<"|blockrect.w"<<blockrect.w<<"blockrect.h"<<blockrect.h<<std::endl;

				//destrect = destination rectangle and in the screen (so for example if the camera at 100px position and the tile is at 120px position, we show the tile at 20px position
				destrect.x = j * tileSize - coord.x;
				//destrect.y = i*50; //original
				destrect.y = i*50 - coord.y;

				//destrect.x = j * tileSize - box.x;
				//destrect.y = i*50 - box.y;

				//coord.y =destrect.y;

				//rectangle destrect = {
				//						j * tileSize - coord.x, i*50
				//					};
				//SDL_BlitSurface(block, &blockrect,screen,&destrect);
				al_draw_bitmap_region(tileImg, blockrect.x,blockrect.y,blockrect.w,blockrect.h,destrect.x, destrect.y,0); //original
				//al_flip_display();

			}
		}

	}
}

int World::getStartMapBoundaries()
{
	/*int*/ start = ( GameObject::getCoord().x - ((int)GameObject::getCoord().x % tileSize)) / tileSize;
	
	if (start < 0)
	{
		start=0;
	}
	return start;
}

int World::getEndMapBoundaries()
{
	/*int*/ end = (GameObject::getCoord().x + GameObject::getCoord().w + (tileSize - (int)(GameObject::getCoord().x + GameObject::getCoord().w) % tileSize)) / 50;
	
	if (end > map[0].size())
	{
		end = map[0].size();
	}

	return end;
}

//void background::Update(std::vector<std::vector<int> >& map)
void World::update()
{
	//background::coord.x += 1 * 1; // will bmove background x auto
	//background::coord.y+= 1 * 1; // will bmove background y auto
	//if (background::coord.x + background::coord.w < 0)
	//{
	//	coord.x = 0;
	//}

}

void World::render()
{
	//will update only background, not foreground
	al_draw_bitmap_region(bgImg, GameObject::getCoord().x,GameObject::getCoord().y,GameObject::getCoord().w,GameObject::getCoord().h,0,0,0);
	//al_draw_bitmap_region(bgImg, 0,0,World::coord.w,World::coord.h,0,0,0);
	//al_draw_bitmap_region(bgImg, box.x,box.y,box.w,box.h,0,0,0);

	//will update only tileset, not background
	showmap();
}



World* World::getInstance()
{
	static World world;
    return &world;
}