#include "World.h"

int World::start;
unsigned int World::end;

//World::World(ALLEGRO_BITMAP *bgSheet, char* filename, ALLEGRO_BITMAP *bgImage)
//{
	//tileSize = 50;
	//coord.x =  0;
	//coord.y = 0;
	//coord.w = WIDTH;
	//coord.h = HEIGHT;

	//tile.x = tile.y = 80;
	//tile.w = WIDTH;
	//tile.h = HEIGHT;

//}

World::World(void)
{
	tileSheet=NULL;
	//tile.w = tileSize;
	//tile.h = tileSize;
	defaultTileId = 0;
	mapX = 0;
	mapY = 0;
	visibleHeight = 0;
	visibleWidth = 0;
	width = 0;
	height =0;

}

World::~World(void)
{
	this->close_map(); //###########################################2ND MAP STRATEGY
}

void World::addEntity(GameObject gameObject)
{
	//entities.push_back(gameObject);
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
	//coord.x = 0;
	//coord.y = 0;
	//coord.w = WIDTH;
	//coord.h = HEIGHT;
	//std::cout<<"x="<<x<<std::endl;
	//std::cout<<"y="<<y<<std::endl;
	if (x < 0) 
		x = 0;
    else if (x + visibleWidth > width) 
		x = width - visibleWidth; //if the player is in right limit of the scenario
    if (y < 0) 
		y = 0; //if the player is in below the lowest limit of the scenario
    else if (y + visibleHeight > height) 
		y = height - visibleHeight; //if the player is above the hightest vertical limit of the scenario
    
    mapX = x;
    mapY = y;

	//std::cout<<"mapX is="<<mapX<<std::endl;
	//std::cout<<"mapY is="<<mapY<<std::endl;


}


//###############################################################################################################################
//###########################################2ND MAP STRATEGY BEGIN##############################################################
//###############################################################################################################################
void World::close_map() {
    cells.clear();
    for (unsigned int i = 0; i < tiles.size(); ++i) {
        if (tiles[i]) al_destroy_bitmap(tiles[i]);
        tiles.clear();
    }
    
    if (mapbmp) al_destroy_bitmap(mapbmp);
}

bool World::read_tileset_information(const ALLEGRO_CONFIG *config) {
    const char* tileset_file = al_get_config_value(config, "tileset", "tileset_file");
    if (!tileset_file) {
        std::cout << "tileset_file key doesn't exist" << std::endl;
        return false;
    }
    
    const char *dimension = al_get_config_value(config, "tileset", "tile_dimension");
    if (!dimension) {
        std::cout << "tile_dimension key doesn't exist" << std::endl;
        return false;
    }
    
    //gap_x and gap_y are optional keys.
    const char *gap_x = al_get_config_value(config, "tileset", "tile_horizontal_gap");
    if (!gap_x) {
        std::cout << "tile_horizontal_gap key doesn't exist" << std::endl;
        gap_x = new char[2];
        gap_x = "1";
    }

    const char *gap_y = al_get_config_value(config, "tileset", "tile_vertical_gap");
    if (!gap_y) {
        std::cout << "tile_vertical_gap key doesn't exist" << std::endl;
        gap_y = new char[2];
        gap_y = "1";
    }
    
    const char *offset = al_get_config_value(config, "tileset", "offset");
    if (!offset) {
        std::cout << "offset key doesn't exist" << std::endl;
        offset = new char[2];
        offset = "0";
    }

    return this->load_tileset(tileset_file, 
                              std::atoi(dimension), 
                              std::atoi(gap_x), 
                              std::atoi(gap_y), 
                              std::atoi(offset));
}

ALLEGRO_BITMAP* World::create_map_bitmap() {
    int width  = getWidth();
    int height = getHeight();

    ALLEGRO_BITMAP *bmp = al_create_bitmap(width, height);
    ALLEGRO_BITMAP *old = al_get_target_bitmap();
    
    al_set_target_bitmap(bmp);

    for (unsigned int index = 0; index < cells.size(); ++index) {
        Tile *t = cells[index];
        al_draw_bitmap(tiles[t->getId()], t->getX(), t->getY(), 0);
        if (show_grid) {
			cells[index]->drawBoundingBox();
        }
    }

    al_set_target_bitmap(old);
    al_save_bitmap("testmapa.png", bmp);
    return bmp;
}

void World::toggle_grid() {
    show_grid = !show_grid;
    must_redraw = true;
}


bool World::load_map(const std::string& mapname) {
    //closes previously loaded map
    close_map();

    //load map
    ALLEGRO_CONFIG *map_config = al_load_config_file(mapname.c_str());
    if (!map_config) {
        std::cout << "error loading config file for map" << std::endl;
        return false;
    }
    
    if (!read_tileset_information(map_config)) {
        std::cout << "error reading tileset information" << std::endl;
        return false;
    };
    
    const char *number_of_rows = al_get_config_value(map_config, "map", "number_of_rows");
    if (!number_of_rows) {
        std::cout << "number_of_rows key doesn't exist" << std::endl;
        return false;
    }
    
    const char *number_of_cols = al_get_config_value(map_config, "map", "number_of_cols");
    if (!number_of_cols) {
        std::cout << "number_of_cols key doesn't exist" << std::endl;
        return false;
    }
    
    const char *default_tileid = al_get_config_value(map_config, "map", "default_tile_id");
    
    rows            = std::atoi(number_of_rows);
    cols            = std::atoi(number_of_cols);
	defaultTileId = std::atoi(default_tileid);

	std::cout << "rows=" <<rows<< std::endl;
	std::cout << "cols=" <<cols<< std::endl;
	std::cout << "default_tile_id=" <<defaultTileId<< std::endl;
    
    if (!rows || !cols) {
        std::cout << "invalid row / column value" << std::endl;
        return false;
    }
    
    int pos_y = 0;
    
    // read each cell's data
    for (unsigned int i = 0; i < rows; ++i) {
        int pos_x = 0;
        for (unsigned int j = 0; j < cols; ++j) {
            std::ostringstream oss_cell;
            oss_cell << "cell " << i << " " << j;
            
            // tile id
            const char *sid = al_get_config_value(map_config, oss_cell.str().c_str(), "id");
            int id = defaultTileId;
            if (sid) {
                id = std::atoi(sid);
            }
            
            //if the tile is passable (i.e. collision detection is ignored)
            const char *spassable = al_get_config_value(map_config, oss_cell.str().c_str(), "passable");
            bool passable = true;
            if (spassable) {
                passable = std::atoi(spassable) ? true : false;
            }
            
            //create new tile
            Tile *t = new Tile(pos_x, pos_y, cellSize, cellSize, id);
            //t->is_passable(passable);
            cells.push_back(t);
            
            pos_x += cellSize;
        }
        pos_y += cellSize;
    }
    
    al_destroy_config(map_config);
    
    width = calcWidth();
    height = calcHeight();
    
    mapbmp = create_map_bitmap(); //old
	//mapbmp = new_map();
    
    return true;
}

bool World::load_tileset(const std::string& imgname, int cell_dimension, int gap_x, int gap_y, int offset) {
                         
    ALLEGRO_BITMAP *tileimg = al_load_bitmap(imgname.c_str());
    if (!tileimg) {
        std::cout << "tileset file not found: " << imgname << std::endl;
        return false;
    }
    
	this->tileHorizontalGap = gap_x;
	this->tileVerticalGap = gap_y;
    this->offset = offset;
    this->cellSize = cell_dimension;
	this->tilesetFilename.assign(imgname.c_str());
    
    std::cout << "loading " << imgname << std::endl;
    
    unsigned int pos_x         = this->offset;
    unsigned int pos_y         = this->offset;
    unsigned int bitmap_width  = al_get_bitmap_width(tileimg);
    unsigned int bitmap_height = al_get_bitmap_height(tileimg);
    
    while (pos_y < bitmap_height) {
        if (pos_x + cellSize < bitmap_width) {
            ALLEGRO_BITMAP *tile = al_clone_bitmap(al_create_sub_bitmap(tileimg, 
                                                                        pos_x, 
                                                                        pos_y, 
                                                                        cellSize,
                                                                        cellSize));
        
            if (!tile) {
                std::cout << "error cloning tile" << std::endl;
                return false;
            }
        
            tiles.push_back(tile);
			pos_x += cellSize + tileHorizontalGap;
        } else {
            pos_x = this->offset;
			pos_y += cellSize + tileVerticalGap;
        }
    }
    
    al_destroy_bitmap(tileimg);
    return true;
}


void World::redraw() const {
    ALLEGRO_BITMAP *old = al_get_target_bitmap();
    
    al_set_target_bitmap(mapbmp);
    
    al_clear_to_color(al_map_rgb(0,0,0));
    
    for (unsigned int i = 0; i < cells.size(); ++i) {
        Tile *t = cells[i];
		al_draw_bitmap(tiles[t->getId()], t->getX(), t->getY(), 0);

        if (show_grid) {
			cells[i]->drawBoundingBox();
        }
    }
    
    for (unsigned int i = 0; i < chars.size(); ++i) {
        chars[i]->draw();
    }
    
    al_set_target_bitmap(old);
}

void World::draw() {
    if (always_redraw) {
        redraw();
    } else if (must_redraw) {
        redraw();
        must_redraw = false;
    }
    
	//this will print the background, the foreground, the player... everything
    al_draw_bitmap_region(mapbmp, mapX, mapY, visibleWidth, visibleHeight, 0, 0, 0);
	//std::cout<<"visiblewidth="<<visiblewidth<<"|visibleheight="<<visibleheight<<std::endl;
}

//###############################################################################################################################
//###########################################2ND MAP STRATEGY END##############################################################
//###############################################################################################################################

bool World::loadMap(const char* filename)
{
	//bgImg = bgImage;
	//tileImg = bgSheet;

	bgImg = al_load_bitmap("image\\background.png");
	if(!bgImg){
		std::cout<<"Couldn't load background image"<<std::endl;
	}
	else
	{
		std::cout<<"loaded bg image"<<std::endl;
	}

	tilesetFilename = "image\\TileSet-1.fw.png";

	tileSheet = al_load_bitmap("image\\TileSet-1.fw.png");//World.png TileSet-1.fw.png
	if(!tileSheet){
		std::cout<<"Couldn't load tile image"<<std::endl;
		return false;
	}
	else
	{
		std::cout<<"loaded tileset image"<<std::endl;
	}

	tileHorizontalGap = 2;
	tileVerticalGap = 2;
	offset = 2;


	//loadTileSet(tilesetFilename, tileSize, tileHorizontalGap, tileVerticalGap, offset);

	//for(int i = 0; i < size; i++)
	//{
	//	tile[i].ID = BRICK;
	//	bricks[i].level = 0;
	//	bricks[i].size = 0;
	//	bricks[i].timer = 0;
	//	bricks[i].x = 0;
	//	bricks[i].xstart = 0;
	//	bricks[i].y = 0;
	//	bricks[i].ystart = 0;
	//}

	//loadmap(filename);

	std::ifstream in (filename);
	if(!in.is_open())
	{
		std::cout<<"Problem loading the file"<<std::endl;
		return false;
	}

	
	in >> cols;
	in >> rows;

	width = calcWidth();
	height = calcHeight();
	

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


	std::cout<<"cols->"<<cols<<std::endl;
	std::cout<<"rows->"<<rows<<std::endl;
	int current; //current block tile number

	int posY = 0;

	for (unsigned int j = 0; j < rows; j++)
	//for (unsigned int i = 0; i < mapHeight; i++)
	{
		std::vector<int> vec;
		int posX = 0;

		//for (unsigned int j = 0; j < mapWidth; j++)
		for (unsigned int i = 0; i < cols; i++)
		{		
			if(in.eof())
			{
				std::cout<<"File end has reached too soon"<<std::endl;
				return false;
			}
			int id = defaultTileId;

			in >> current;
			
			id = current;

			Tile *tile = new Tile(posX,posY,tileSize,tileSize, id);

			if (current == -1)
			{
			//	enemies.push_back(new enemy(ene, j* 50, i * 50, 1, 0));
			//	vec.push_back(0);
			}
			else
			{
			//of all elements 1 to 7 tiles types we add every single one detected
				if (current>=0 && current <=7)
				{
					if (current == 3)
					{
		//				finish.x = j * 50;
		//				finish.y = i * 50;
					}
					vec.push_back(current);
				}
				//or we add the enemy
				else
				{
					vec.push_back(0);
				}
			}
			cells.push_back(tile);

			//posX += tileSize;
			
		}
		
		//posY += tileSize;

		map.push_back(vec);
		
	}
	in.close();
	
    width  = getWidth();
    height = getHeight();

	//std::cout<< finish.x << " " << finish.y << std::endl;
	//inteiro = 4;
	std::cout<<"map loaded"<< std::endl;

	//mapBitmap =	createBitmap();

	return true;
}

//this will wrap the tileset , the background, thee foreground... into a single bitmap layer
ALLEGRO_BITMAP* World::createBitmap()
{
	float width = getWidth();
	float height = getHeight();

    ALLEGRO_BITMAP *bmp = al_create_bitmap(width, height); // Creates a new bitmap using the bitmap format and flags for the current thread
    ALLEGRO_BITMAP *old = al_get_target_bitmap(); // Return the target bitmap of the calling thread

	al_set_target_bitmap(bmp); // This function selects the bitmap to which all subsequent drawing operations in the calling thread will draw to

	for (unsigned int index = 0; index < cells.size(); ++index) 
	{
        Tile *tile = cells[index];
		std::cout<<"tile id="<<tile->getId()<<" ;tile x="<<tile->getX()<<" ;tile y="<<tile->getY()<<std::endl;
        al_draw_bitmap(tiles[tile->getId()], tile->getX(), tile->getY(), 0);
        if (showGrid) {
			cells[index]->drawBoundingBox();
        }
    }

	std::cout<<"map bitmap created"<<std::endl;

	al_set_target_bitmap(old); // and set the target bitmap to be using in the next update
	al_save_bitmap("bg_draw.png", bmp);

	return bmp;
}


unsigned int World::calcWidth() const 
{
	return tileSize * cols;
}

unsigned int World::calcHeight() const 
{
	return tileSize * rows;
}


void World::checkCollisionWith(Character *character) {
    if (character == NULL) return;
    //for (unsigned int i = 0; i < cells.size(); ++i) {
    //    c->handle_collision(cells[i]);
    //}
}

//looks up the COLLISION_TYPE enum using the tile's number
COLLISION_TYPE World::collisionLookup(int TileNum)
{
	 std::string collisionName;
	 COLLISION_TYPE collisionType;

	 //if we find an item with this key
	 if( m_CollisionMap.count(TileNum) )
	 {
		 collisionName = m_CollisionMap[TileNum];
		

		 if (collisionName.compare("solid") == 0)
			collisionType = COLLIDE_SOLID;
		 else if (collisionName.compare("none") == 0)
			collisionType = COLLIDE_NONE;
		 else if (collisionName.compare("slope") == 0)
			 collisionType = COLLIDE_SLOPE;
		 else if (collisionName.compare("top") == 0)
			 collisionType = COLLIDE_PLATFORM;
		  
		 else
		 {
			 //throw std::exception("Can't assign collision type based on map listing.");
			 collisionType = COLLIDE_NONE;
			 std::cout<< "Warning!! Couldn't assign an appropriate collide type for " << collisionName.c_str() 
				 <<	 ". Defaulting to COLLIDE_NONE" << std::endl;
		 }
	
	 }
	 else
		 collisionType = COLLIDE_NONE;

	 return collisionType;

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

void World::addCharacter(Player *player)
{
	if (player)
	{
		chars.push_back(player);
	}
	//this->player =p;
}


bool World::loadTileSet(const std::string& imgName, int cellDimension, int gapX, int gapY, int offset)
{

    //ALLEGRO_BITMAP *tileimg = al_load_bitmap(imgName.c_str());
    //if (!tileimg) {
    //    std::cout << "tileset file not found: " << imgName << std::endl;
    //    return false;
    //}

	tileSheet = al_load_bitmap(imgName.c_str()); // c_str will convert form char* to string
	if(!tileSheet){
		std::cout<<"Couldn't load tile image"<<std::endl;
		return false;
	}
	else
	{
		std::cout<<"loaded tileset image"<<std::endl;
	}

    
    this->tileHorizontalGap = gapX;
    this->tileVerticalGap = gapY;
    this->offset = offset;
    this->cellSize = cellDimension;
    this->tilesetFilename.assign(imgName.c_str());
    
    std::cout << "loading " << imgName << std::endl;
    
    unsigned int posX         = this->offset;
    unsigned int posY         = this->offset;
    unsigned int bitmapWidth  = al_get_bitmap_width(tileSheet);
    unsigned int bitmapHeight = al_get_bitmap_height(tileSheet);
    
    while (posY < bitmapHeight) {
        if (posX + cellSize < bitmapWidth) {
			std::cout << "Cloning " << imgName << std::endl;
			// Create a new bitmap with al_create_bitmap, and copy the pixel data from the old bitmap across with al_clone_bitmap.
            ALLEGRO_BITMAP *tile = al_clone_bitmap(al_create_sub_bitmap(tileSheet, 
                                                                        posX, 
                                                                        posY, 
                                                                        cellSize,
                                                                        cellSize));
        
            if (!tile) {
                std::cout << "error cloning tile" << std::endl;
                return false;
            }
        
			std::cout << "Adding tile" << imgName << std::endl;
            tiles.push_back(tile);
            posX += cellSize + tileHorizontalGap;
        } else {
            posX = this->offset;
            posY += cellSize + tileVerticalGap;
        }
    }
    
    al_destroy_bitmap(tileSheet);
    return true;	
}

void World::drawMap()
{

}



//alternative
void World::showMap()
{
	//int start = ( GameObject::coord.x - (coord.x % tileSize)) / tileSize;
	//int end = (coord.x + coord.w + (tileSize - (coord.x + coord.w) % tileSize)) / 50;

	//std::cout<<"coord.x is "<<coord.x<<std::endl;
	//setStartMapBoundaries(GameObject::getCoord());
	//setEndMapBoundaries(GameObject::getCoord());
	//unsigned int start = getStartMapBoundaries();
	//unsigned int end = getEndMapBoundaries();


	//if (start < 0)
	//{
	//	start=0;
	//}
	//if (end > map[0].size())
	//{
	//	end = map[0].size();
	//}

	//int tileSetWidth = al_get_bitmap_width(filename) / tileSize;

	//for (unsigned int i = 0; i < map.size(); i++)
	//{
	//	for (unsigned int j = 0; j < mapHeight; j++)
	//Player *player;
	for (unsigned int i = 0; i < rows; i++)
	{
		for (unsigned int j = 0; j < cols; j++)
		{
			if (map[i][j] !=0)
			{
				//we calculate the position in the TileSet-1.bmp image
				blockrect.x = (map[i][j]-1) * tileSize;
				blockrect.y = 0; //original  important to draw different tileset textures

				//int tX
				//std::cout<<"blockrect.x="<<blockrect.x<<std::endl;

				//blockrect.y = (map[i][j]-1) * tileSize;
				blockrect.w = tileSize; 
				blockrect.h = tileSize;

				//rectangle blockrect = {
				//						//because coord of tileset begins with 0 and not 1 I have to do (tilesize * tilenumber) minus 1
				//						(map[i][j]-1) * tileSize,0,tileSize,tileSize										
				//					 };
				//std::cout<<"blockrect.x"<<blockrect.x<<"|blockrect.y"<<blockrect.y<<"|blockrect.w"<<blockrect.w<<"blockrect.h"<<blockrect.h<<std::endl;

				//destrect = destination rectangle and in the screen (so for example if the camera at 100px position and the tile is at 120px position, we show the tile at 20px position
				//destrect.x = j * tileSize - GameObject::getX();
				destrect.x = j * tileSize;
				destrect.y = i*tileSize; //original
				//destrect.y = i*50 - GameObject::getCoord().y;

				//destrect.x = j * tileSize - tile.x;
				//destrect.y = i*50 - tile.y;

				//coord.y =destrect.y;

				//rectangle destrect = {
				//						j * tileSize - coord.x, i*50
				//					};
				//SDL_BlitSurface(block, &blockrect,screen,&destrect);
				//al_draw_bitmap_region(tileSheet, blockrect.x,blockrect.y,blockrect.w,blockrect.h,destrect.x, destrect.y,0); //original
				//al_draw_bitmap_region(tileSheet, blockrect.x,blockrect.y,visibleWidth,visibleHeight,destrect.x, destrect.y,0); //original
				//al_draw_bitmap_region(tileSheet, mapX,mapY,visibleWidth,visibleHeight,0, 0,0);
				al_draw_bitmap_region(tileSheet, blockrect.x,blockrect.y,blockrect.w,blockrect.h,destrect.x - mapX, destrect.y - mapY,0); //original
				//al_flip_display();

			}
		}

	}
}

void World::setMapVisibleSize(unsigned int width,unsigned int height)
{
	visibleWidth = width;
    visibleHeight = height;
}


void World::setStartMapBoundaries(Rect coordinate)
{
	//coordinate = GameObject::getCoord();
	//	/*int*/ start = ( coordinate.x - ((int)coordinate.x % tileSize)) / tileSize;
	//
	//if (start < 0)
	//{
	//	start=0;
	//}

}

void World::setEndMapBoundaries(Rect coordinate)
{
	//coordinate = GameObject::getCoord();
	/////*int*/ end = (coordinate.x + coordinate.w + (tileSize - (int)(coordinate.x + coordinate.w) % tileSize)) / 50;
	//end = map.size();
	//
	//if (end > map[0].size())
	//{
	//	end = map[0].size();
	//}



}

int World::getStartMapBoundaries()
{
	return start;
}

int World::getEndMapBoundaries()
{
	return end;
}

// will modify xVal and yVal variabes from PhysicsComponents i.e currentTileX and currentTileY
void World::GetCurrentTileValues(float xPos, float yPos, int& xVal, int& yVal)
{
	//xVal = xPos / tile.w;
	//yVal = yPos / tile.h;
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
	//al_draw_bitmap_region(bgImg, GameObject::getCoord().x,GameObject::getCoord().y,GameObject::getCoord().w,GameObject::getCoord().h,0,0,0);
	//al_draw_bitmap_region(bgImg, 0,0,World::coord.w,World::coord.h,0,0,0);
	//al_draw_bitmap_region(bgImg, tile.x,tile.y,tile.w,tile.h,0,0,0);
	//al_draw_bitmap_region(bgImg, 0,0,al_get_bitmap_width(bgImg),al_get_bitmap_height(bgImg),0,0,0); // works
	al_draw_bitmap_region(bgImg, mapX,mapY,visibleWidth,visibleHeight,0, 0,0); // works too

	//will update only tileset, not background
	showMap();

	for (unsigned int i = 0; i < chars.size(); ++i) {
	    chars[i]->draw();
    }

}



World* World::getInstance()
{
	static World world;
    return &world;
}