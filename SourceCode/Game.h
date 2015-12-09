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

    //Keep track of the player
    PlayerShip *g_player;

    //The skybox
    irr::scene::ISceneNode *skyBox;

    //Static text of the Infomation
    irr::gui::IGUIStaticText *scoreText;
    irr::gui::IGUIStaticText *ammoText;
    irr::gui::IGUIStaticText *FPSText;

    //Handle frame independent movement
    irr::u32 then;
    irr::u32 now;
    irr::f32 frameDeltaTime;

    //check if the game has been loaded
    bool loaded;

    //FUNCTIONS
public:
    //constructor
    Game(irr::IrrlichtDevice *device, EventReceiver *receiver);

    //load all the objects to go in the scene
    void load(irr::scene::ICameraSceneNode *camera);

    //main loop of the game, will just update everything. Returns true if player dies
    bool play();

    //call before exiting porgram
    void cleanUp();

    //adds objects onto the static list
    static void addObjectToUpdate(Object *toAdd);

    //returns true if objects are loaded in the scene
    bool isLoaded();
};

#endif	/* GAME_H */

