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
    //stores the current delta time
    irr::f32 currDeltaTime;
    
    //variables to control the camera pos
    int tpDistance;
    int tpOffset;
    int sideViewDistance;
    int sideViewOffset;
    
    //to be able to receive events
    EventReceiver *eReceiver;
    
    //to control the camera being used in the scene
    irr::scene::ICameraSceneNode *camera;
    //vectors to switch between the two camera positions
    irr::core::vector3df thirdPersonPosition;
    irr::core::vector3df sideViewPosition;
    //enum to store the payer's mode
    enum modes{
        flying,
        shooting,
    } currentMode;
    
    //FUNCTIONS
public:
    //constructor
    PlayerShip(EventReceiver *eReceiver, irr::ITimer *timer, irr::scene::ISceneManager *sceneManagerReference, irr::video::IVideoDriver *driverReference);

    //overriding tick function
    virtual void tick(irr::f32 deltaTime);
    
    //adds a camera so it can be updated and controlled
    void addCamera(irr::scene::ICameraSceneNode *camera);
    
    //changes the player/camera between modes
    void changeMode();
    
private:
    //turns the player left or right
    void turnLeft();
    void turnRight();
    void moveUp();
    void moveDown();
    
    //makes the player shoot
    //void shoot();
    
    //updates the two camera positions
    void updateCameraPositions();
    
    //updates the camera based on the current mode
    void updateCamera(irr::scene::ICameraSceneNode* sceneCamera);
};

#endif	/* PLAYERSHIP_H */

