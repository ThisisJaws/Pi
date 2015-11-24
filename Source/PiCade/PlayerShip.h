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
    int tpDistance;         //distance behind the player
    int tpOffset;           //offset above player
    int sideViewDistance;   //distance from the side of the player
    int sideViewOffset;     //offset infront of the player
    
    //to be able to receive events
    EventReceiver *eReceiver;
    
    //keep track of all the points where the mode changes (these will be a point along the X axis)
    int modeChangePoints[6];    //there will be 3 levels with 2 changes
    int modeChangeIteration;
    
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
    
    //adds the array of made changes points
    void addChangeModePoints(int zPoints[6]);
    
private:
    //turns the player left or right
    void turnLeft();
    void turnRight();
    void moveUp();
    void moveDown();
    
    //changes the player/camera between modes
    void changeMode();
    
    //updates the two camera positions
    void updateCameraPositions();
    
    //updates the camera based on the current mode
    void updateCamera(irr::scene::ICameraSceneNode* sceneCamera);
};

#endif	/* PLAYERSHIP_H */

