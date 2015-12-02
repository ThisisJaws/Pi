/* 
 * Check the make file for the executable target name/directory
 * click build then run the executable from there
 * 
 * make sure to include all source files in the makefile!!!
 */

//so it can work on windows
#pragma comment(lib, "Irrlicht.lib")

//header to play the game
#include "Game.h"

/*
 * program entry point
 */
int main(int argc, char** argv) {
    //create a game object - everything gets initialised in the constructor
    Game currentGame = Game();

    //call the play function
    int r = currentGame.play();

    //once the loop breaks go straight to clean up (for now)
    currentGame.cleanUp();
    
    //once the 'play' loop has ended then exit program
    return r;
}

