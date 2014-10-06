#include "camera.h"

float x= 0;
float y = 0;

camera::camera(void)
{
	
}


camera::~camera(void)
{
}

/**
* Algorithm used: Tweaning -> <code>x += (target - value) * constant</code>
*/
void tick(player *p)
{
	// set the camera to make the player at the center of screen and it follows with the player with a delay
	x += (( -p->GetPos().x + WIDTH / 2) - x) * 0.0875f;
}

float GetX()
{
	return x;
}

float GetY()
{
	return y;
}