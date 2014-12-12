#pragma once


#include "GameObject.h"
#include "Character.h"

enum
{
	TARGET_MODE_NORMAL = 0
	,TARGET_MODE_CENTER
};


class Camera
{
private:
	float x;
	float y;
	float width;
	float height;

	float* targetX;
	float* targetY;

	int posX; 
	int posY; 
	Character *focusedChar;

	Rect position;
	Rect focus;

public:
	static Camera cameraControl;
	Camera(float x ,float y);
	Camera(void);
	~Camera(void);
	
	int targetMode;
	//void tick(Player *p);
	//void tick(Rect p1);
	//void update(Player &p1);
	void setSize(float width,float height);
	void setFocusedCharacter(Character* focusedChar);
	void setPosition(float x, float y);
	void setTarget(float* x, float* y);
    void setFocus(float fx, float fy);
	void update();
	
	//void update(int moveX, int moveY);
	float getX();
	float getY();

	int getPosX() const; //barnhen
	int getPosY() const; //barnhen

	Rect getFocus() const;
	Rect getPosition() const;
	const char* getCameraTargetMode() const;
	float getWidth() const;
	float getHeight() const;
	//Rect getPosition() {return position;}

};

