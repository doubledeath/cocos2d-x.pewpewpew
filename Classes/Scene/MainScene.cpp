#include "MainScene.h"

USING_NS_CC;

MainScene *MainScene::create(Config *config)
{
    MainScene *pRet = new(std::nothrow) MainScene();

    if (pRet && pRet->initWithConfig(config))
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        delete pRet;
        pRet = nullptr;
        return nullptr;
    }
}

bool MainScene::initWithConfig(Config *config)
{
    if (!Scene::init())
    {
        return false;
    }

    createWorld(config);

    return true;
}

void MainScene::createWorld(Config *config)
{
    mWorld = World::create(config);

    addChild(mWorld);
}
