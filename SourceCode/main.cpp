/* 
 * Check the make file for the executable target name/directory
 * click build then run the executable from there
 * 
 * make sure to include all source files in the makefile!!!
 */

//header to play the game
#include "Game.h"

//so it can work on windows
#ifdef _IRR_WINDOWS_
#pragma comment(lib, "Irrlicht.lib")
#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif

/*
 * program entry point
 */
int main(int argc, char** argv) {
    //create a game object - everything gets initialised in the constructor
    Game currentGame = Game();

	bool exit = false;

	do{
		exit = currentGame.play();
	} while(!exit);

    //once the loop breaks go straight to clean up (for now)
    currentGame.cleanUp();
    
    //once the 'play' loop has ended then exit program
    return 0;
}

