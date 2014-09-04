#include "game.h"

int main()
{
	game g;

	// call our engine initialization function
	g.initializeGameEngine();
 
	// call our engine process function
	g.processGameEngine();
 
	// call our engine shutdown function
	g.shutdownGameEngine();
 
	// terminate the program
	return 0;
	
}