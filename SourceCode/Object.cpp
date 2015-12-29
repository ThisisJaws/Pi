#include "Object.h"

Object::Object(const irr::io::path &pathOfMesh, const irr::io::path &pathOfTexture, irr::scene::ISceneManager *sceneManagerReference, irr::video::IVideoDriver *driverReference, bool spawnOnConstruct, irr::core::vector3df spawnPos, irr::s32 objectTypeID){
    //set the default object type to undefined
    typeID = objectTypeID;

    //set the spawn position
    this->spawnPos = spawnPos;

    //default this to false, no object has been spawned yet
    objectSpawned = false;

    //dont want it to get deleted straight away
    markedForDelete = false;

	//Make sure the collisionManager points to nothing
	collMan = 0;

    //if we want the object to be spawned into the scene when the constructor is called (defaulted as true)
    if(spawnOnConstruct){
        spawnObject(pathOfMesh, pathOfTexture, sceneManagerReference, driverReference);
    }
}

bool Object::isMarkedForDelete(){
    return markedForDelete;
}

void Object::markForDelete(){
    markedForDelete = true;
}

irr::s32 Object::getTypeID(){
	return objectNode->getID();
}

irr::scene::IAnimatedMesh* Object::getMesh(){
    return objectMesh;
}

irr::scene::IAnimatedMeshSceneNode* Object::getSceneNode(){
    return objectNode;
}

irr::core::vector3df Object::getPosition(){
    return objectNode->getPosition();
}

irr::scene::ISceneNode* Object::checkCollision(int direction){
	//WORKING HERE TO GET COLLISION WORKING WITH TRIANGLE SELECTORS NOW - REMEMBER TO ALSO CHANGE THE FUNCTIONS IN BULLET, COLELCTABLE AND PLAYERSHIP

	//Cast a ray from the object to slightly infront of the object
	irr::core::line3df ray;
	ray.start = getPosition();
	ray.end = ray.start;
	ray.end.Z += 1 * direction;
	//Current interection of a level or a mesh
	irr::core::vector3df interesection;
	//The triangle that was hit
	irr::core::triangle3df hitTriangle;

	irr::scene::ISceneNode *objectTest = collMan->getSceneNodeAndCollisionPointFromRay(ray, interesection, hitTriangle);
	return objectTest;

	/*
    //if we don't have any collideables then return straight away
    if(collideables.size() <= 0){
        return NULL;
    }

    //loop through and return true if any object has collided
    for(std::list<Object*>::iterator nodeIterator = collideables.begin(); nodeIterator != collideables.end(); ++nodeIterator){
        if(*nodeIterator != this){
            if(objectNode->getTransformedBoundingBox().intersectsWithBox((*nodeIterator)->getSceneNode()->getTransformedBoundingBox())){
				
				return *nodeIterator;
            }
        }
    }

    return NULL;
	*/
}

void Object::updatePosition(irr::core::vector3df newPosition){
    objectNode->setPosition(getPosition() + newPosition);
}

void Object::updatePosition(float x, float y, float z){
    irr::core::vector3df temp = irr::core::vector3df(x, y, z);
    updatePosition(temp);
}

void Object::changePosition(irr::core::vector3df newPosition){
    objectNode->setPosition(newPosition);
}

void Object::removeFromScene(){
    objectNode->remove();
}

void Object::spawnObject(const irr::io::path &pathOfMesh, const irr::io::path& pathOfTexture, irr::scene::ISceneManager* sceneManagerReference, irr::video::IVideoDriver* driverReference){
    //if the object hasn't been 'spawned' then place it into the scene
    if(!objectSpawned){
        //load the mesh
        objectMesh = sceneManagerReference->getMesh(pathOfMesh);

        //create the scene node using loaded mesh
        objectNode = sceneManagerReference->addAnimatedMeshSceneNode(objectMesh, NULL, typeID, spawnPos);
        objectNode->setMaterialTexture(0, driverReference->getTexture(pathOfTexture));

        //set the object to not need lighting
        objectNode->setMaterialFlag(irr::video::EMF_LIGHTING, false);

		//Create a triangle selector of this object
		irr::scene::ITriangleSelector *selector = sceneManagerReference->createTriangleSelector(objectNode);
		//Give the node the newly created selector
		objectNode->setTriangleSelector(selector);
		//Drop the selector to remove it from memory
		selector->drop();

		//Create a reference to the collision Manager, to use when the collision function is called
		collMan = sceneManagerReference->getSceneCollisionManager();

        objectSpawned = true;
    }
}
