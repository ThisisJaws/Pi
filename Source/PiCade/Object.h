/* 
 * this class is for everything that wil be draw/updated 
 * with in the game - like the player/enemies/pick ups ect...
 * All object classes should inherit from this and not be created
 * from this class
 */

#ifndef OBJECT_H
#define	OBJECT_H

//reference to the engine 
#include "irrlicht.h"

#include <list>

class Object{
    //VARIABLES
private:
    //reference to the object's mesh
    irr::scene::IAnimatedMesh *objectMesh;
    //reference to the scene node the object will use
    irr::scene::IAnimatedMeshSceneNode *objectNode;
    //a vector of collideable objects
    static std::list<irr::scene::ISceneNode*> collideables;

    //kep track if the object has been spawned or not
    bool objectSpawned;
    
    //FUNCTIONS
public:
    //constructor
    Object(const irr::io::path &pathOfMesh, const irr::io::path &pathOfTexture, irr::scene::ISceneManager *sceneManagerReference, irr::video::IVideoDriver *driverReference, bool spawnOnConstruct = true);
    //destructor
    virtual ~Object();
    
    //this will be called every update of the main game loop
    virtual void tick(irr::f32 deltaTime) = 0;
    
    //get the object's mesh
    irr::scene::IAnimatedMesh* getMesh();
    
    //get the object's scene node
    irr::scene::IAnimatedMeshSceneNode* getSceneNode();
    
    //get the position of the object
    irr::core::vector3df getPosition();
    
    //removes the object from the scene
    void removeFromScene();

protected:
    //returns true if the object has collided with an object contained within the vector
    bool checkCollision();
    
    //call to update the current position with the direction
    void updatePosition(irr::core::vector3df newPosition);
    void updatePosition(float x, float y, float z);
    
    //call to completely change the object position (see update pos to move the object)
    void changePosition(irr::core::vector3df newPosition);
    
    //spawns the object into the scene if it hasn't happened already
    virtual void spawnObject(const irr::io::path &pathOfMesh, const irr::io::path &pathOfTexture, irr::scene::ISceneManager *sceneManagerReference, irr::video::IVideoDriver *driverReference);
};

#endif	/* OBJECT_H */

