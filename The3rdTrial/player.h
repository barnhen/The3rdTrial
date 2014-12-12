#pragma once
#include "Character.h"
//#include "World.h"
class Player :	public Character
{
private:
	
	Player(Player const&); // the trouble to return object instance

	//int tileSize;
	ALLEGRO_BITMAP *playerImg;
	Rect camera;
	
	Rect pos;
	bool ground, jump;
	bool nc; // non collision	
	float gravity;

protected:
	Rect destrect;
	int velCamX;
	int velCamY;
	int velPosX;
	int velPosY;
	int velCoordX;
	int velCoordY;
	int isScrolling;
	const char* debugMsg;
	const char* debugCollisionMsg;

public:
	Player(float x, float y, float width, float height, float velX, float velY, float maxVelY, ALLEGRO_BITMAP *pImg);
	//Player();
	~Player(void);

	//void init(ALLEGRO_BITMAP *pImg);
	//void update(std::vector<std::vector<int> >& map);
	//void update();
	void render();	
	virtual void implementDraw() const;
	//float getXVel(){return Player::velX;}
	//float getYVel(){return Player::velY;}
	float getPosXVel(){return Player::velPosX;}
	float getPosYVel(){return Player::velPosY;}

	//float getCoordX(){return Player::coord.x;}
	int getDirX(){return Player::dirX;}
	//Rect getCoord(){return Player::coord;}
	Rect getDestRect(){return Player::destrect;}
	Rect getRect(){return Character::box;}
	//float getPosX(){return boundingBox.getX();}
	//float getPosY(){return boundingBox.getY();}
	Rect getCamera(){return Player::camera;}
	//float getX(){return Character::box.x;}
	//float getY(){return Character::box.y;}
	bool isJumpAllowed();
	bool isColliding(){return true;}
	bool isJumping(){return true;}
	int getIsScrolling(){return Player::isScrolling;}
	void setVel(int vel);
	void setDestRect(Rect dest);
	void setXvel(int vel);
	void setYvel(int vel);
	void setPosXvel(int cVel);
	void setPosYvel(int cVel);
	void setCamXvel(int cVel);
	void setCamYvel(int cVel);
	void setCoordXvel(int cVel);
	void letsJump();


	//void MoveLeft(std::vector<std::vector<int> > themap);
	//void MoveRight(std::vector<std::vector<int> > themap);
	//void ResetAnimation(std::vector<std::vector<int> > themap);
	//void Move(std::vector<std::vector<int> >& map);
	//void moveLeft();
	//void moveRight();
	//void resetAnimation();
	void move();

	const char* getDebugPlayerMov(){return Player::debugMsg;}
	const char* getDebugPlayerCollision(){return Player::debugCollisionMsg;}
	

	//player& GetInstance(){return player();};
	//static Player &getInstance(); // the trouble to return object instance
};

