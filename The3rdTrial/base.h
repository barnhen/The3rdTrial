#pragma once
#include "sprite.h"
#include <iostream>
#include <allegro5\allegro.h>
#include <allegro5\allegro_image.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>
#include <list>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_color.h>
#include <allegro5\color.h>
#include <vector>



//struct box
//{
//	int x;
//	int y;
//	int w;
//	int h;
//};

const int WIDTH = 640;
const int HEIGHT = 480;

class base
{
protected:
	int maxFrame;
	int curFrame;
	int frameCount;
	int frameDelay;
	int velX;
	int velY;
	int dirX;
	int dirY;

	bool collision(sprite* rec1, sprite* rec2);


public:
	base(void);
	~base(void);
	static sprite coord;//coord variable, store the absolute coordinate of the screen, so if I go a 1000px it will be a 1000px

	void virtual Update(std::vector<std::vector<int> >& map);
	void virtual Render();
	int GetX();
	int GetY();

	bool intersects(sprite r);

	inline const char * BoolToString(bool b){  return b ? "true" : "false";}

};

