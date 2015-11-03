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

#include <vector>

class Object{
    
    //VARIABLES
protected:
    //reference to the object's mesh
    irr::scene::IAnimatedMesh *objectMesh;
    //reference to the scene node the object will use
    irr::scene::IAnimatedMeshSceneNode *objectNode;
    //a vector of collideable objects
    std::vector<irr::scene::ISceneNode*> collideables;
    
    //vector to handle object positioning
    irr::core::vector3df objectPosition;
    
    //FUNCTIONS
public:
    //constructor
    Object(const irr::io::path &pathOfMesh, const irr::io::path &pathOfTexture, irr::scene::ISceneManager *sceneManagerReference, irr::video::IVideoDriver *driverReference);
    //destructor
    ~Object();
    
    //this will be called every update of the main game loop
    virtual void tick(float deltaTime) = 0;
    
    //get the object's mesh
    irr::scene::IAnimatedMesh* getMesh();
    
    //get the object's scene node
    irr::scene::IAnimatedMeshSceneNode* getSceneNode();
    
    //adds a collideable object into the vector
    void addCollideable(irr::scene::ISceneNode *collideable);
    
    //clears the vector containing collideable objects
    void clearCollideables();
    
protected:
    //returns true if the object has collided with an object contained within the vector
    bool checkCollision();
    
    //call to update an objects position
    void updatePosition(irr::core::vector3df newPosition);
};

#endif	/* OBJECT_H */

