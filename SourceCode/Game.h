/* 
 * This is the class that will handle everything game related
 * so restarting a game ect. can be done with ease from main.cpp
 */

#ifndef GAME_H
#define	GAME_H

//so we can use the engine
#include "irrlicht.h"

//other includes
#include <cstdlib>
#include <list>

#include "EventReceiver.h"
#include "PlayerShip.h"
#include "EnemyShip.h"
#include "BasicEnemy.h"
#include "StaticObject.h"

class Game{
    //VARIABLES
private:
    //irrlicht device, this is the root for EVERYTHING within the engine
    irr::IrrlichtDevice *device;
    //a pointer to the video driver
    irr::video::IVideoDriver *driver;
    //a pointer to the scene manager
    irr::scene::ISceneManager *smgr;
    
    //set up a selector for collision purposes
    irr::scene::ITriangleSelector *selector;
    
    //object to receive keyboard input
    EventReceiver eReceiver;
    
    //all objects to get drawn/updated will get placed in this list
    static std::list<Object*> objectsToUpdate;
    
    //FUNCTIONS
public:
    //constructor
    Game();
    
    //main loop of the game
    int play();
    
    //call when the game gets reset (if th player dies and whats to start over)
    void restart();
    
    //call before exiting porgram
    void cleanUp();
    
    //adds objects onto the static list
    static void addObjectToUpdate(Object *toAdd);
};

#endif	/* GAME_H */

