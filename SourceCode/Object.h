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
	//Pointer to the scene manager
	irr::scene::ISceneManager *sceneMan;
    
	//Pointer to the collision manager to check for collisions
	irr::scene::ISceneCollisionManager *collMan;
    
    //the spawn position of the Object
    irr::core::vector3df spawnPos;
    
    //Mark an object for delete to remove it from update
    bool markedForDelete;
	bool deleteReady;

	//The typeID is what type of object this is (see ObjectTypes.h) stored to quickly check what type of an object it is
	irr::s32 typeID;

	//This increments every time an object is created
	static irr::s32 objectCount;
	//This holds the unique ID of the object so it can be found when searching through lists
	irr::s32 uniqueID;

	//Text to animate
	irr::gui::IGUIStaticText *animatedText;
	//Used to animated the text
	bool animateText;
	//Poistion to animate from
	irr::core::vector2di textPos;
	//How long to animate for
	const float ANIMATE_TIME = 0.75f;
	float animTimePast;

    //FUNCTIONS
public:
    //constructor
    Object(const irr::io::path &pathOfMesh, const irr::io::path &pathOfTexture, irr::scene::ISceneManager *sceneManagerReference, const irr::core::vector3df &spawnPos = irr::core::vector3df(0, 0, 0), const irr::s32 &objectTypeID = TYPE_UNDEFINED_TYPE, const bool &checkCollisionFromBoundingBox = false);
    //destructor
	virtual ~Object();

    //this will be called every update of the main game loop
    virtual void tick(irr::f32 deltaTime);
    
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
    virtual void updatePosition(const float &x, const float &y, const float &z);
    //call to completely change the object position (see update pos to move the object)
    virtual void changePosition(const irr::core::vector3df &newPosition);

	//Returns the current ojbects relative rotation
	irr::core::vector3df getRotation();
	//Rotates the object by the desired amount
	void updateRotation(const irr::core::vector3df &angle);
	void updateRotation(const float &x, const float &y, const float &z);
	//Changes the rotation to the given amount
	void changeRotation(const irr::core::vector3df &angle);

	//call the remove the object's mesh from the scene
	void removeFromScene();
    
protected:
    //returns the unique ID of the object that collided, direction will be either 1 or -1;
    virtual irr::s32 checkCollision(int direction);

	//Displays the text on screen
	void displayText(const irr::core::stringw &text, const irr::core::vector3df &worldPos, const int &amount = 0);
};

#endif	/* OBJECT_H */

