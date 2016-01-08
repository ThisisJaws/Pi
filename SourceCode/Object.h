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

	//The typeID is what type of object this is (see ObjectTypes.h) stored to quickly check what type of an object it is
	irr::s32 typeID;

	//This increments every time an object is created
	static irr::s32 objectCount;
	//This holds the unique ID of the object so it can be found when searching through lists
	irr::s32 uniqueID;
    
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
    
    //Get the type of the object
    irr::s32 getTypeID();

	//Get the unique ID of the object
	irr::s32 getUniqueID();
    
    //get the object's mesh
    virtual irr::scene::IAnimatedMesh* getMesh();
    
    //get the object's scene node
    virtual irr::scene::IAnimatedMeshSceneNode* getSceneNode();
    
    //get the position of the object
    virtual irr::core::vector3df getPosition();
    
    //call to update the current position with the direction
    virtual void updatePosition(const irr::core::vector3df &newPosition);
    virtual void updatePosition(float x, float y, float z);

	//Rotates the object by the desired amount
	void rotate(const irr::core::vector3df &angle);
	//Returns the current ojbects relative rotation
	irr::core::vector3df getRotation();
    
    //call to completely change the object position (see update pos to move the object)
    virtual void changePosition(irr::core::vector3df newPosition);

	//call the remove the object's mesh from the scene
	void removeFromScene();
    
protected:
    //returns the unique ID of the object that collided, direction will be either 1 or -1;
    virtual irr::s32 checkCollision(int direction);
    
    //spawns the object into the scene if it hasn't happened already
    virtual void spawnObject(const irr::io::path &pathOfMesh, const irr::io::path &pathOfTexture, irr::scene::ISceneManager *sceneManagerReference, irr::video::IVideoDriver *driverReference);
};

#endif	/* OBJECT_H */

