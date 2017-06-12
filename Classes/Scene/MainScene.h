#pragma once

#include "cocos2d.h"
#include "GameLogic/World.h"

class MainScene : public cocos2d::Scene {
public:
    static cocos2d::Scene *CreateScene();

    virtual bool init();

    CREATE_FUNC(MainScene);
private:
    class World *World;

    void CreateWorld();
};
