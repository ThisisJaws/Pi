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
#include "StrongEnemy.h"
#include "FastEnemy.h"
#include "StaticObject.h"
#include "Ammo.h"
#include "Gem.h"

class Game{
    //VARIABLES
private:
    //irrlicht device, this is the root for EVERYTHING within the engine
    irr::IrrlichtDevice *device;
    //a pointer to the video driver
    irr::video::IVideoDriver *driver;
    //a pointer to the scene manager
    irr::scene::ISceneManager *smgr;
    //a pointer to the gui iterface
    irr::gui::IGUIEnvironment *guienv;
    //object to receive keyboard input
    EventReceiver *eReceiver;

    //all objects to get drawn/updated will get placed in this list
    static std::list<Object*> objectsToUpdate;

    //The font to use
    irr::gui::IGUIFont *font;

    //To count the fps
    int lastFPS;
    int FPS;

    //Handle frame independent movement
    irr::u32 then;
    irr::u32 now;
    irr::f32 frameDeltaTime;

    //FUNCTIONS
public:
    //constructor
    Game(irr::IrrlichtDevice *device);

    //load all the objects to go in the scene
    void load(irr::scene::ICameraSceneNode *camera);

    //main loop of the game, will just update everything
    void play();

    //call when the game gets reset (if th player dies and whats to start over)
    //void restart();

    //call before exiting porgram
    void cleanUp();

    //adds objects onto the static list
    static void addObjectToUpdate(Object *toAdd);
};

#endif	/* GAME_H */

