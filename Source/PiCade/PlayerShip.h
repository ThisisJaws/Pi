/* 
 * Contains all the functionality for the player/player's ship
 */

#ifndef PLAYERSHIP_H
#define	PLAYERSHIP_H

#include "Object.h"

class PlayerShip : public Object{
    //VARIABLES
private:
    //stores the current delta time
    float currDeltaTime;
    //controls how fast the player can move
    float moveSpeed;
    //controls the player's turn speed
    float turnSpeed;
    
    //vector to handle player positioning
    irr::core::vector3df shipPosition;
    
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
    PlayerShip(const irr::io::path &pathOfMesh, const irr::io::path &pathOfTexture, irr::scene::ISceneManager *sceneManagerReference, irr::video::IVideoDriver *driverReference);
    
    //overriding tick function
    virtual void tick(float deltaTime);
    
    //turns the player left or right
    void turnLeft();
    void turnRight();
    
    //adds a camera so it can be updated and controlled
    void addCamera(irr::scene::ICameraSceneNode *camera);
    
    //changes the player/camera between modes
    void changeMode();
    
private:
    //updates the two camera positions
    void updateCameraPositions();
    
    //updates the camera based on the current mode
    void updateCamera();
};

#endif	/* PLAYERSHIP_H */

