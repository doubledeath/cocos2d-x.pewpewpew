#include "MainScene.h"

USING_NS_CC;

bool MainScene::init()
{
    if (!Scene::init())
    {
        return false;
    }

    createWorld();

    return true;
}

void MainScene::createWorld()
{
    mWorld = World::create();

    addChild(mWorld);
}
