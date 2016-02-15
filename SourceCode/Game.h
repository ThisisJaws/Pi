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
#include "EnemyTypes.h"

#include "StaticObject.h"
#include "Ammo.h"
#include "Gem.h"

#include "LavaWorld.h"
#include "IceWorld.h"
#include "JungleWorld.h"

//Number of playable worlds
#define NUM_WORLDS 3

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

	//Keep track of the score
	unsigned int previousScore;

	//Array of worlds
	World *worlds[NUM_WORLDS];
	//Keep track of the current world
	int currentWorld;

    //All the sky domes we will need
    irr::scene::ISceneNode *skyDome[NUM_WORLDS];

    //GUI Static text of the Infomation
    irr::gui::IGUIStaticText *scoreText;
	irr::gui::IGUIStaticText *livesText;
    irr::gui::IGUIStaticText *ammoText;
    irr::gui::IGUIStaticText *FPSText;
	irr::gui::IGUIStaticText *stageCompleteText;

    //Handle frame independent movement
    irr::u32 then;
    irr::u32 now;
    irr::f32 frameDeltaTime;

    //check if the game has been loaded
    bool loaded;

	//Howlong to wait after the player has finished the stage to start another
	float stageWaitTime;
	float stageWaitPast;

    //FUNCTIONS
public:
    //constructor
    Game(irr::IrrlichtDevice *device, EventReceiver *receiver);
	//destructor
	~Game();

    //load all the objects to go in the scene
    void load(irr::scene::ICameraSceneNode *camera);

    //main loop of the game, will just update everything. Returns true if player dies
    bool play();

    //call before exiting porgram
    void cleanUp();

    //adds objects onto the static list
    static void addObjectToUpdate(Object *toAdd);

	//Check if the objects list contains any type of object
	static bool objectToUpdateContainsAnyType(const int &typeID);

	//Returns the object if the loop contains the ID
	static Object* getObjectReferenceByID(const irr::s32 &objectID);

	//Returns a pointer to the current player
	static PlayerShip* getCurrentPlayer();

    //Returns true if the position is behind the player
    static bool checkBehidPlayer(const irr::f32 &zPos);

    //returns true if objects are loaded in the scene
    bool isLoaded();

    //Returns the score when the game is finished
    unsigned int getFinalScore();

	void resetObjectsToUpdate();
};

#endif	/* GAME_H */

