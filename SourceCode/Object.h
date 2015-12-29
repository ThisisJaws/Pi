/* 
 * this class is for everything that will be drawn/updated 
 * with in the game - like the player/enemies/pick ups ect...
 * All object classes should inherit from this and not be created
 * from this class
 */

#ifndef OBJECT_H
#define	OBJECT_H

#include "irrlicht.h"
#include "ObjectTypes.h"
#include <list>

class Object{
    //VARIABLES
private:
    //reference to the object's mesh
    irr::scene::IAnimatedMesh *objectMesh;
    //reference to the scene node the object will use
    irr::scene::IAnimatedMeshSceneNode *objectNode;
    
	//Pointer to the collision manager to check for collisions
	irr::scene::ISceneCollisionManager *collMan;
    
    //the spawn position of the Object
    irr::core::vector3df spawnPos;

    //keep track if the object has been spawned or not
    bool objectSpawned;
    
    //mark an object for delete to remove it o update
    bool markedForDelete;

	//to store the type of the object for the spawn on construct function
	irr::s32 typeID;
    
    //FUNCTIONS
public:
    //constructor
    Object(const irr::io::path &pathOfMesh, const irr::io::path &pathOfTexture, irr::scene::ISceneManager *sceneManagerReference, irr::video::IVideoDriver *driverReference, bool spawnOnConstruct = true, irr::core::vector3df spawnPos = irr::core::vector3df(0, 0, 0), irr::s32 objectTypeID = TYPE_UNDEFINED_TYPE);
    
    //this will be called every update of the main game loop
    virtual void tick(irr::f32 deltaTime) = 0;
    
    //check if the object needs to be deleted
    virtual bool isMarkedForDelete();
    //mark the object for deletion
    virtual void markForDelete();
    
    //get thew type of the object
    irr::s32 getTypeID();
    
    //get the object's mesh
    virtual irr::scene::IAnimatedMesh* getMesh();
    
    //get the object's scene node
    virtual irr::scene::IAnimatedMeshSceneNode* getSceneNode();
    
    //get the position of the object
    virtual irr::core::vector3df getPosition();
    
    //call to update the current position with the direction
    virtual void updatePosition(irr::core::vector3df newPosition);
    virtual void updatePosition(float x, float y, float z);
    
    //call to completely change the object position (see update pos to move the object)
    virtual void changePosition(irr::core::vector3df newPosition);

	//call the remove the object's mesh from the scene
	void removeFromScene();
    
protected:
    //returns true if the object has collided with an object contained within the vector, direction will be either 1 or -1;
    virtual irr::scene::ISceneNode* checkCollision(int direction);
    
    //spawns the object into the scene if it hasn't happened already
    virtual void spawnObject(const irr::io::path &pathOfMesh, const irr::io::path &pathOfTexture, irr::scene::ISceneManager *sceneManagerReference, irr::video::IVideoDriver *driverReference);
};

#endif	/* OBJECT_H */

