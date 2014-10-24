#pragma once
#include "GameObject.h"
#include "World.h"
class Player :	public GameObject
{

	Player(Player const&); // the trouble to return object instance

	int tileSize;
	ALLEGRO_BITMAP *playerImg;
	Rect camera;
	
	Rect pos;
	bool ground, jump;
	bool nc; // non collision

protected:
	Rect box;
	Rect destrect;
	int velCamX;
	int velCamY;
	int velPosX;
	int velPosY;
	int velCoordX;
	int velCoordY;
	int isScrolling;
	const char* debugMsg;

public:
	void init(ALLEGRO_BITMAP *pImg);
	void update(std::vector<std::vector<int> >& map);
	//void update();
	void render();
	int getXVel(){return Player::velX;}
	int getYVel(){return Player::velY;}
	int getPosXVel(){return Player::velPosX;}
	int getPosYVel(){return Player::velPosY;}

	int getCoordX(){return Player::coord.x;}
	int getDirX(){return Player::dirX;}
	Rect getCoord(){return Player::coord;}
	Rect getDestRect(){return Player::destrect;}
	Rect getRect(){return Player::box;}
	Rect getPos(){return Player::pos;}
	Rect getCamera(){return Player::camera;}
	bool isJumpAllowed(){return true;}
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
	void setJump();


	//void MoveLeft(std::vector<std::vector<int> > themap);
	//void MoveRight(std::vector<std::vector<int> > themap);
	//void ResetAnimation(std::vector<std::vector<int> > themap);
	//void Move(std::vector<std::vector<int> >& map);
	void moveLeft();
	void moveRight();
	void resetAnimation();
	void move();

	const char* getDebugPlayerMov(){return Player::debugMsg;}
	Player(ALLEGRO_BITMAP *pImg);
	Player();
	~Player(void);

	//player& GetInstance(){return player();};
	static Player &getInstance(); // the trouble to return object instance
};

