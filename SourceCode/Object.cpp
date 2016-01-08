#include "Object.h"

//Init static member here - 0 is reserved for no collision, 1 is reserved for terrain
irr::s32 Object::objectCount = 2;

Object::Object(const irr::io::path &pathOfMesh, const irr::io::path &pathOfTexture, irr::scene::ISceneManager *sceneManagerReference, irr::video::IVideoDriver *driverReference, bool spawnOnConstruct, irr::core::vector3df spawnPos, irr::s32 objectTypeID){
	//Make the ID of the object the current object count
	uniqueID = objectCount;
	//Increment the object count when the ID has been used
	objectCount++;
	
	//set the ID of the object
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
	return typeID;
}

signed int Object::getUniqueID(){
	return uniqueID;
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

irr::s32 Object::checkCollision(int direction){
	//Cast a ray from the object to slightly infront of the object
	irr::core::line3df ray;
	ray.start = getPosition();
	ray.end = ray.start;
	ray.end.Z += 1;// *direction;
	//Current interection of a level or a mesh
	irr::core::vector3df interesection;
	//The triangle that was hit
	irr::core::triangle3df hitTriangle;

	//Perform the ray cast and return the scene node
	irr::scene::ISceneNode *objectTest = collMan->getSceneNodeAndCollisionPointFromRay(ray, interesection, hitTriangle);
	
	if(objectTest != NULL && objectTest != objectNode){
		return objectTest->getID();
	} else{
		return 0;
	}
}

void Object::updatePosition(const irr::core::vector3df &newPosition){
    objectNode->setPosition(getPosition() + newPosition);
}

void Object::updatePosition(float x, float y, float z){
    irr::core::vector3df temp = irr::core::vector3df(x, y, z);
    updatePosition(temp);
}

void Object::updateRotation(const irr::core::vector3df &angle){
	objectNode->setRotation(getRotation() + angle);
}

irr::core::vector3df Object::getRotation(){
	return objectNode->getRotation();
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
        objectNode = sceneManagerReference->addAnimatedMeshSceneNode(objectMesh, NULL, uniqueID, spawnPos);
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
