#pragma once
#include "base.h"
#include "game.h"
class player :
	public base
{

	int tileSize;
	ALLEGRO_BITMAP *playerImg;
	sprite camera;
	sprite box;
	sprite pos;
	bool ground, jump;
	bool nc; // non collision

protected:
	int velCamX;
	int velCamY;
	int velPosX;
	int velPosY;
	int velCoordX;
	int velCoordY;
	int isScrolling;

public:
	void Init(ALLEGRO_BITMAP *pImg);
	void Update(std::vector<std::vector<int> >& map);
	void Render();
	int GetXVel(){return player::velX;}
	int GetYVel(){return player::velY;}
	int GetPosXVel(){return player::velPosX;}
	int GetPosYVel(){return player::velPosY;}

	int GetCoordX(){return player::coord.x;}
	int GetDirX(){return player::dirX;}
	sprite GetCoord(){return player::coord;}
	sprite GetRect(){return player::box;}
	sprite GetPos(){return player::pos;}
	sprite GetCamera(){return player::camera;}
	bool IsJumpAllowed(){return true;}
	bool IsColliding(){return true;}
	bool IsJumping(){return true;}
	int GetIsScrolling(){return player::isScrolling;}
	void SetVel(int vel);
	void SetXvel(int vel);
	void SetYvel(int vel);
	void SetPosXvel(int cVel);
	void SetPosYvel(int cVel);
	void SetCamXvel(int cVel);
	void SetCamYvel(int cVel);
	void SetCoordXvel(int cVel);
	void SetJump();


	void MoveLeft(std::vector<std::vector<int> > themap);
	void MoveRight(std::vector<std::vector<int> > themap);
	void ResetAnimation(std::vector<std::vector<int> > themap);
	void Move(std::vector<std::vector<int> >& map);
	player(ALLEGRO_BITMAP *pImg);
	~player(void);
};

