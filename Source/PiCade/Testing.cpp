//see testing.h

#include "Testing.h"

int Testing::runTest(){
    IrrlichtDevice *device = createDevice(EDT_OPENGL, dimension2d<u32>(800, 600), 16, false, false, false, 0);
    if(!device){
        return 1;
    }
    
    IVideoDriver *driver = device->getVideoDriver();
    ISceneManager *smgr = device->getSceneManager();
    
    IAnimatedMesh *shipMesh = smgr->getMesh("Assets/LowestPolyShip.obj");
    if(!shipMesh){
        device->drop();
        return 1;
    }
        
    int a = 0;
    int arraySize = 20; //CHANGE THIS TO ADD SHIPS TO THE SCENE
    int xOffSet = 3;
    int zOffSet = 3;
    vector3df shipPosition = vector3df(0, 0, zOffSet);
    IAnimatedMeshSceneNode *shipNodes[arraySize];
    for(int i = 0; i < arraySize; i++){
        shipNodes[i] = smgr->addAnimatedMeshSceneNode(shipMesh);
        shipNodes[i]->setMaterialFlag(EMF_LIGHTING, false);
        if(a > 0){
            shipPosition.X += xOffSet;
            if(a > 7){
                shipPosition.X = 0;
                shipPosition.Z -= zOffSet;
                a = 0;
            }
        }
        shipNodes[i]->setPosition(shipPosition);
        a++;
    }
    
    smgr->addCameraSceneNode(0, vector3df(-12, 8, 0), vector3df(0, 0, 0));
    
    int lastFPS = -1;
    int fps;
    
    while(device->run()){
        driver->beginScene();
        smgr->drawAll();
        driver->endScene();
        
        fps = driver->getFPS();
        if (lastFPS != fps){
            irr::core::stringw tmp(L"testing ");
            tmp += L" FPS: ";
            tmp += fps;
            device->setWindowCaption(tmp.c_str());
            lastFPS = fps;
        }
    }
    
    device->drop();
    
    return 0;
}
