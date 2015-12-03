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
    //the player's score
    unsigned short score;
    
    //how many bullets the player can shoot
    unsigned short ammo;
    
    //variables to control the camera pos
    int tpDistance;         //distance behind the player
    int tpOffset;           //offset above player
    int sideViewDistance;   //distance from the side of the player
    int sideViewOffset;     //offset in front of the player
    
    //camera position gets adjusted by these offsets
    float cameraYOffset, maxYOffset, minYOffset;
    float cameraXOffset, maxXOffset;
    
    //to control the camera being used in the scene
    irr::scene::ICameraSceneNode *camera;
    //vectors to switch between the two camera positions
    irr::core::vector3df thirdPersonPosition;
    irr::core::vector3df sideViewPosition;
    
    //to be able to receive events
    EventReceiver *eReceiver;
    
    //keep track of all the points where the mode changes (these will be a point along the X axis)
    int modeChangePoints[6];    //there will be 3 levels with 2 changes
    int modeChangeIteration;
    
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
    
    //adds the array of made changes points
    void addChangeModePoints(int zPoints[6]);
    
    //getters and setters for ammo and score
    unsigned short getAmmo();
    void increaseAmmo(unsigned short amount);
    
    unsigned short getScore();
    void increaseScore(unsigned short amount);
      
private:
    //turns the player left or right
    void turnLeft(float speed, irr::f32 deltaTime);
    void turnRight(float speed, irr::f32 deltaTime);
    void moveUp(float speed, irr::f32 deltaTime);
    void moveDown(float speed, irr::f32 deltaTime);
    
    //changes the player/camera between modes
    void changeMode();
    
    //updates the two camera positions
    void updateCameraPositions();
    
    //updates the camera based on the current mode
    void updateCamera(irr::scene::ICameraSceneNode* sceneCamera);
};

#endif	/* PLAYERSHIP_H */

