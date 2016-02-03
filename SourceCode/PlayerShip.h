/*
 * Contains all the functionality for
 * the player/player's ship
 */

#ifndef PLAYERSHIP_H
#define	PLAYERSHIP_H

#include "Ship.h"
#include "EventReceiver.h"

class PlayerShip : public Ship{
    //VARIABLES
private:
    //The player's actual score
    unsigned int score;
	//When the player has gotten enough to recieve an extra life
	unsigned int previousLifeIncrease;
	//How many points to get before a life is aded
	unsigned int lifeIncreasePoints;

	//If this is true then the player will start flashing to indicate damage taken
	bool damageRecieved;
	//Track the ship's flashing
	unsigned short flashCount;		//How many times the ship has flashed
	unsigned short maxFlash;		//How many times to flash
	irr::f32 timeSinceLastFlash;	//When was the last flash
	irr::f32 flashLength;			//How frequently to flash

    //how many bullets the player can shoot
    unsigned short ammo;

	//Will be true if the player loses
	bool lost;

    //variables to control the camera pos
    int tpDistance;         //distance behind the player
    int tpOffset;           //offset above player
    int sideViewDistance;   //distance from the side of the player
    int sideViewOffset;     //offset in front of the player

    //camera position gets adjusted by these offsets
    float cameraYOffset, maxYOffset, minYOffset;
    float cameraXOffset, maxXOffset;

	//This holds the 'base' position, the one that will be considered 0, 0, 0 if the player moves
	irr::core::vector3df basePosition;

    //to control the camera being used in the scene
    irr::scene::ICameraSceneNode *camera;
    //vectors to switch between the two camera positions
    irr::core::vector3df thirdPersonPosition;
    irr::core::vector3df sideViewPosition;

    //to be able to receive events
    EventReceiver *eReceiver;

    //The light to light the level
    irr::scene::ILightSceneNode *light;

	//Stops the player moving the ship
	bool controlsLocked;

    //enum to store the payer's mode
    enum modes{
        flying,
        shooting,
    } currentMode;

    //FUNCTIONS
public:
    //constructor
    PlayerShip(EventReceiver *eReceiver, irr::ITimer *timer, irr::scene::ISceneManager *sceneManagerReference, irr::video::IVideoDriver *driverReference);

    virtual void tick(irr::f32 deltaTime) override;

    //adds a camera so it can be updated and controlled
    void addCamera(irr::scene::ICameraSceneNode *camera);

    //getters and setters for ammo and score
    unsigned short getAmmo();
    void increaseAmmo(unsigned short amount);
    unsigned int getScore();
    void increaseScore(unsigned int amount);

	//Overriden to make sure the cameraOffsets get updated
	virtual void changePosition(irr::core::vector3df newPosition);

	//when the player collides or gets shot we don't want to delete it, just lose the game
	virtual void markForDelete() override;

	//changes the player/camera between modes
	void changeMode(const int &increaseSpeedByFactor = 1);

	//Returns true if the player has lost
	bool playerLost();

	//Overriden so the player can have a period of invulnerability
	virtual void dealDamage(const unsigned short &amount = 1);

	//Locks the contronls (and camera)
	void setControlLock(const bool &lock);

	//Returns the lockControls variable
	bool areControlsLocked();

protected:
	//Overriden for camera controls
	virtual void moveUp(const float &speed, const irr::f32 &deltaTime) override;
	virtual void moveDown(const float &speed, const irr::f32 &deltaTime) override;
	virtual void turnLeft(const float &speed, const irr::f32 &deltaTime) override;
	virtual void turnRight(const float &speed, const irr::f32 &deltaTime) override;

private:
    //updates the two camera positions
    void updateCameraPositions();

    //updates the camera based on the current mode
    void updateCamera(irr::scene::ICameraSceneNode* sceneCamera);
};

#endif	/* PLAYERSHIP_H */

