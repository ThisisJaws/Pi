#include "Object.h"

//static variables need to be defined outside of the class so the lniker knows where to allocate the memory
std::list<Object*> Object::collideables;

Object::Object(const irr::io::path &pathOfMesh, const irr::io::path &pathOfTexture, irr::scene::ISceneManager *sceneManagerReference, irr::video::IVideoDriver *driverReference, bool spawnOnConstruct){
    //set the default object type to undefined
    typeID = TYPE_UNDEFINED_TYPE;
    
    //default this to false, no object has been spawned yet
    objectSpawned = false;
    
    //if we want the object to be spawned into the scene when the constructor is called (defaulted as true)
    if(spawnOnConstruct){
        spawnObject(pathOfMesh, pathOfTexture, sceneManagerReference, driverReference);
    }
}

Object::~Object(){
    //remove the object from the collideables list
    for(std::list<Object*>::iterator nodeIterator = collideables.begin(); nodeIterator != collideables.end(); ++nodeIterator){
        if((*nodeIterator) == this){
            nodeIterator = collideables.erase(nodeIterator);
        }
    }
    
    //remove from scene
    objectNode->remove();
}

int Object::getTypeID(){
    return typeID;
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

Object* Object::checkCollision(){
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

void Object::spawnObject(const irr::io::path &pathOfMesh, const irr::io::path& pathOfTexture, irr::scene::ISceneManager* sceneManagerReference, irr::video::IVideoDriver* driverReference){
    //if the object hasn't been 'spawned' then place it into the scene
    if(!objectSpawned){
        //load the mesh
        objectMesh = sceneManagerReference->getMesh(pathOfMesh);
        
        //create the scene node using loaded mesh
        objectNode = sceneManagerReference->addAnimatedMeshSceneNode(objectMesh);
        //objectNode->setMaterialTexture(0, driverReference->getTexture(pathOfTexture));
        
        //set the object to not need lighting
        objectNode->setMaterialFlag(irr::video::EMF_LIGHTING, false);
        
        //let other objects collision test against this object
        collideables.push_back(this);
        
        objectSpawned = true;
    }
}