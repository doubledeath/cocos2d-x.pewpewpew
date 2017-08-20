#pragma once

#include "cocos2d.h"
#include "GameLogic/World/World.h"

class MainScene : public cocos2d::Scene
{
public:
    CREATE_FUNC(MainScene)

    virtual bool init() override;
private:
    World *mWorld;

    void createWorld();
};
