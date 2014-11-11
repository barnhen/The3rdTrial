#include "PhysicsComponent.h"
#include <iostream>


PhysicsComponent::PhysicsComponent(void)
{
}


PhysicsComponent::~PhysicsComponent(void)
{
}

void PhysicsComponent::update()
{	
	//static int worldTilesize = World::getTileSize();
	//Rect coordinate = GameObject::getCoord();
	//int start = ( coordinate.x - ((int)coordinate.x % 50)) / 50;
	//int end = (coordinate.x + coordinate.w + (50 - (int)(coordinate.x + coordinate.w) % 50)) / 50;


	//std::cout<<"start is "<<start<<"end is "<<end<<std::endl;

	//if (start < 0)
	//{
	//	start=0;
	//}
	//if (end > map[0].size())
	//{
	//	end = map[0].size();
	//}

		//##################Player MOVING#####################################BEGIN##################
	//if (Player::dirX == 1) // move right
	//{
	//	// Player will move from most left part (scenario beginning)) untill the midle of screen
	//	if (Player::getPos().x <= WIDTH/2 -Character::box.w) // middle of screen minus the frame width to center it -> 640/2 - 50 = 270
	//	{
	//		//isScrolling = 0;
			//Player::setVel(4);
	//		//std::cout<<"Player::GetPos().x < WIDTH/2 -Character::box.w"<<std::endl;
	//		debugMsg = "moving from most left part (scenario beginning)) untill the midle of screen";
	//	}
	//	// if Player is in the most right side of scenario limit and wants to walk left untill the mmiddle of screen
	//	// because we are skipping n x camera vel to scroll left we have to include the velCamX to condition
	//	else if(Player::getPos().x >= (900 - WIDTH/2) -Character::box.w)
	//	{
	//		//isScrolling = 0;
	//		//std::cout<<"limit right border"<<900 - WIDTH/2<<std::endl;
	//		Player::setVel(4);
	//		//std::cout<<"Player::GetPos().x > (900 - WIDTH/2) -Character::box.w"<<std::endl;
	//		debugMsg = "if Player is in the most right side of scenario limit and wants to walk left untill the mmiddle of screen";
	//	}
	//	// in the middle the Player will scroll right
	//	else
	//	{
	//		if (Player::getPos().x > (900 - WIDTH/2 -Character::box.w))
	//		{
	//			Player::setVel(4);
	//			//std::cout<<"if Player::GetPos().x > (900 - WIDTH/2 -Character::box.w)"<<std::endl;
	//			debugMsg = "in the middle the Player will scroll right 1";
	//		}
	//		else
	//		{
	//			//isScrolling = 1; //true
	//			Player::setXvel(0); //old 0
	//			Player::setCoordXvel(4);
	//			//std::cout<<"else Player::GetPos().x > (900 - WIDTH/2 -Character::box.w)"<<std::endl;
	//			debugMsg = "Player moving right while camera is scrolling";
	//		}
	//	}
	//}

	//else if(Player::dirX == -1) // move left
	//{
	//	// if Player is in the most right side of scenario limit and wants to walk left untill the mmiddle of screen
	//	// because we are skippn n x camera vel to scroll left we have to include the velCamX to condition
	//	if(Player::getPos().x - Player::velPosX > (900 - WIDTH/2) -Character::box.w)
	//	{
	//		//isScrolling = 0;
	//		//std::cout<<"limit right <left> border"<<900 - WIDTH/2<<std::endl;
	//		Player::setVel(4);
	//		debugMsg = "Player moving from right border to left where camera is not scrolling";
	//	}
	//	// because we are skippn n x camera vel to scroll left we have to include the velCamX to condition
	//	else if (Player::getPos().x - Player::velPosX > WIDTH/2 -Character::box.w)
	//	{
	//		//isScrolling = 1;
	//		Player::setXvel(0); //old 0
	//		Player::setCoordXvel(4);
	//		debugMsg = "Player moving from the center camera to the left border";
	//		//below lies the problem when colling to the left the camera scrolls to right when it is suppoesed to stop

	//	}
	//	// if Player is in the most left side of scenario limit and wants to walk right untill the mmiddle of screen
	//	// because we are skipping n x camera vel to scroll left we have to include the velCamX to condition
	//	else
	//	{
	//		//isScrolling = 0;
	//		Player::setVel(4);
	//		debugMsg = "Player moving left to border left where camera is not scrolling";

	//	}
	//}

	//if (Player::getPos().x - Player::velPosX < 0)
	//{
	//	Player::pos.x=0; // 0 to absolute pos.
	//	//Character::box.x=0; // 0 to relative pos.
	//}
	////##################Player MOVING#####################################END##################

	////####################GRAVITY AND COLICION WITH BG TILES#################BEGIN###################
	//World* world;
	//int start = world->getStartMapBoundaries();
	//int end = world->getEndMapBoundaries();


	////int start = ( World::getInstance()->getBox().x - (World::getInstance()->getBox().x % World::getInstance()->getTileSize())) / World::getInstance()->getTileSize();
	////int end = (World::getInstance()->getBox().x + World::getInstance()->getBox().w + (World::getInstance()->getTileSize() - (World::getInstance()->getBox().x + World::getInstance()->getBox().w) % World::getInstance()->getTileSize())) / 50;
	////World* theBg = World::getInstance();
	////int start = theBg->getStartMapBoundaries();
	////int end = theBg->getStartMapBoundaries();

	////int start = (World::getInstance()->getStartMapBoundaries());
	////int end = (World::getInstance()->getEndMapBoundaries());

	////int *start = World::getInstance()->getStartMapBoundaries();
	////int *end = World::getInstance()->getEndMapBoundaries();



	////std::cout<<"start: "<<*start<<std::endl;
	////std::cout<<"end: "<<*end<<std::endl;

	////std::cout<<"start: "<<start<<std::endl;
	////std::cout<<"end: "<<end<<std::endl;


	//if (start < 0)
	//{
	//	start=0;
	//}
	//if (end > map[0].size())
	//{
	//	end = map[0].size();
	//}
	//nc = false; // non collision

	//for (int i = 0; i < map.size(); i++)
	//{
	//	for (int j = start; j < end; j++)
	//	{
	//		if(map[i][j] == 0)
	//			continue;
	//		destrect.x=j * 50 - GameObject::coord.x;
	//		destrect.y=i * 50; //original
	//		
	//		//if (collision(&box, &destrect))
	//		if (rectOverlap(box, destrect))
	//		{
	//			nc = true;
	//			setDestRect(destrect);
	//			//below condition make the Player hit the ground when he falls by gravity
	//			if(destrect.y <= Character::box.y + Character::box.h)
	//			{
	//				ground = true;
	//				GameObject::velY= 0 ;
	//			}
	//			//else if (destrect.y + destrect.h <=Character::box.y + 150)
	//			//{
	//			//	GameObject::velY = 10; // this will be gravity
	//			//}

	//			//horizontalCharacter::box collision check begin
	//			//will stop the Player the pass throughCharacter::box on x direction
	//			//pushing to left
	//			if (Character::box.x + Character::box.w >= destrect.x - 5 && 
	//				//Character::box.y + Character::box.h >= destrect.y + 6 && 
	//				Character::box.x + Character::box.w <= destrect.x +20)
	//			{
	//				Character::box.x = Character::box.x - GameObject::velX; // we stop the Player from moving to right
	//				Player::pos.x = Player::pos.x - Player::velPosX; // we stop the posx of Player from increasing

	//				//if (isScrolling == 1) {Player::coord.x = Player::coord.x - Player::velPosX;std::cout<<"pushing left col"<<std::endl;}
	//				
	//				std::cout<<"pushing left|X coord="<<pos.x<<"|y coord="<<box.y<<"|destrect x="<<destrect.x<<"|destrect.y="<<destrect.y<<std::endl;
	//					
	//				//std::cout<<"destrect push right if is "<<destrect.x<<std::endl;

	//			}
	//			//pushing to right
	//			else if (Character::box.x -Character::box.w <= destrect.x + destrect.w
	//					//&& Character::box.y +Character::box.h >= destrect.y + 6
	//					)
	//			{
	//				Character::box.x = Character::box.x + GameObject::velX; // we stop the Player from moving to left
	//				Player::pos.x = Player::pos.x + Player::velPosX; // we stop the posx of Player from decreasing

	//				//if (isScrolling == 1) 
	//				//{Player::coord.x = Player::coord.x + Player::velCoordX;std::cout<<"pushing right col"<<std::endl;}// we stop the posx of Player from increasing


	//				
	//				std::cout<<"pushing right|X coord="<<pos.x<<"|y coord="<<box.y<<"|destrect x="<<destrect.x<<"|destrect.y="<<destrect.y<<std::endl;

	//			}
	//				//horizontalCharacter::box collision check end
	//			//} // end if isScrolling
	//		}// end if collision(&box, &destrect)
	//	} //end for j < end
	//}// end for map.size()
	////below will make the gravity work on the Player. he will fall
	////if (!nc && !jump) // not colliding nor jumping

	//// means he is either falling or started falling
	//if (!nc && !jump) // not colliding nor jumping
	//{
	//	GameObject::velY = 6.5; //will make gravity to fall the Player faster
	//	//std::cout<<"not coliding or jumping"<<std::endl;
	//	//box.y -= 5;

	//	//if(velY>=0)
	//	//{
	//	//	Player::coord.y++;
	//	//}
	//}
	//else
	//{
	//	//jump = false;
	//}


	////below will make the Player start falling after jumping and hit the ground again
	////if (!jump && GameObject::velY < 6.5)
	////{
	////	//SetYvel(velY++);
	////	//GameObject::velY+=1; //will make the jump last
	////	GameObject::velY = 6.5;
	////}
	//if (!ground)
	//{
	//	GameObject::velY+=gravity; //will make the jump last
	//}


	////max vel downword
	////if(GameObject::velY > 15)
	////{
	////	GameObject::velY = 15;
	////}

	////####################GRAVITY AND COLICION WITH BG TILES#################END###################
	//


}
