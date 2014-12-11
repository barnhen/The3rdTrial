#pragma once
#include "Rect.h"
//#include "World.h"
#include "BoundingBox.h"
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


const int WIDTH = 640;
const int HEIGHT = 480;

/*
http://stackoverflow.com/questions/57483/what-are-the-differences-between-a-pointer-variable-and-a-reference-variable-in
Use references in function parameters and return types to define useful and self-documenting interfaces.
Use pointers to implement algorithms and data structures.
*/

// will work as an Entity class
class GameObject
{
protected:
	int maxFrame;
	int curFrame;
	int frameCount;
	int frameDelay;
	float velX;
	float velY;
	int dirX;
	int dirY;
	//everytime coord is updated by Player object the background if updated
	//static Rect coord;//coord variable, store the absolute coordinate of the screen, so if I go a 1000px it will be a 1000px
	Rect coord;
	//Rect box;
	//float x,y,height,width;

	bool collision(Rect* rec1, Rect* rec2);
	BoundingBox boundingBox;
	//World world;

public:
	//instantianting super class with default values
	GameObject(void) : boundingBox(0,0,0,0,true){};

	//instantianting super class
	GameObject(float x ,float y ,float width, float height, float velX, float velY, bool ignoreCollision = true) 
				: boundingBox(x,y,width,height,ignoreCollision){};

	~GameObject(void);

	//void virtual Update(std::vector<std::vector<int> >& map);
	void virtual update();
	void virtual render();
	void init(float x ,float y ,float width, float height, float velX, float velY);

	/*below is a constant funciton, meaning a function that will not alter any member variables of the class
	 it belongs to. This is the style recommended to us getter, since their only purpose is to retrieve data
	 and should not modify anyhing in the process
	*/
	float getX() const {return boundingBox.getX();}
	float getY() const {return boundingBox.getY();}
	float getWidth(){return this->boundingBox.getWidth();}
	float getHeight(){return this->boundingBox.getHeight();}
	int getDirX(){return dirX;}
	int getDirY(){return dirY;}


	//static Rect getCoord(){return coord;}

	//float getXVel(){return this->coord.vX;}
	//float getYVel(){return this->coord.vY;}


	//bool intersects(Rect r);

	inline const char * boolToString(bool b){  return b ? "true" : "false";}

	//bool valueInRange(int value, int min, int max);
	//bool rectOverlap(Rect A , Rect B);
	//bool rectTouch(Rect A , Rect B);


};

