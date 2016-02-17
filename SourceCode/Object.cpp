#include "Object.h"

//Init static member here - 0 is reserved for no collision, 1 is reserved for terrain
irr::s32 Object::objectCount = 2;

Object::Object(const irr::io::path &pathOfMesh, const irr::io::path &pathOfTexture, irr::scene::ISceneManager *sceneManagerReference, const irr::core::vector3df &spawnPos, const irr::s32 &objectTypeID, const bool &checkCollisionFromBoundingBox){
	//Make the ID of the object the current object count
	uniqueID = objectCount;
	//Increment the object count when the ID has been used
	objectCount++;
	
	//set the ID of the object
    typeID = objectTypeID;

    //set the spawn position
    this->spawnPos = spawnPos;

    //dont want it to get deleted straight away
    markedForDelete = false;

	//Make sure the collisionManager points to nothing
	collMan = 0;

	//load the mesh
	objectMesh = sceneManagerReference->getMesh(pathOfMesh);

	//create the scene node using loaded mesh
	objectNode = sceneManagerReference->addAnimatedMeshSceneNode(objectMesh, NULL, uniqueID, spawnPos);
	objectNode->setMaterialTexture(0, sceneManagerReference->getVideoDriver()->getTexture(pathOfTexture));

	//Create a triangle selector of this object
	irr::scene::ITriangleSelector *selector;
	if(checkCollisionFromBoundingBox){
		selector = sceneManagerReference->createTriangleSelectorFromBoundingBox(objectNode);
	} else{
		selector = sceneManagerReference->createTriangleSelector(objectNode);
	}
	//Give the node the newly created selector
	objectNode->setTriangleSelector(selector);
	//Drop the selector to remove it from memory
	selector->drop();

	//Create a reference to the collision Manager, to use when the collision function is called
	collMan = sceneManagerReference->getSceneCollisionManager();

}

Object::~Object(){
	//needs a virtual destructor to make sure all derived object's constructors get called
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
	ray.end.Z += 1 * direction;
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

void Object::updatePosition(const float &x, const float &y, const float &z){
	updatePosition(irr::core::vector3df(x, y, z));
}

void Object::changePosition(const irr::core::vector3df &newPosition){
	objectNode->setPosition(newPosition);
}

irr::core::vector3df Object::getRotation(){
	return objectNode->getRotation();
}

void Object::updateRotation(const irr::core::vector3df &angle){
	objectNode->setRotation(getRotation() + angle);
}

void Object::updateRotation(const float &x, const float &y, const float & z){
	updateRotation(irr::core::vector3df(x, y, z));
}

void Object::changeRotation(const irr::core::vector3df &angle){
	objectNode->setRotation(angle);
}

void Object::removeFromScene(){
    objectNode->remove();
}
