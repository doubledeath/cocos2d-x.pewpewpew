#pragma once

#include "cocos2d.h"
#include "GameLogic/World/World.h"
#include "Support/Config.h"

class MainScene : public cocos2d::Scene
{
public:
    static MainScene *create(Config *config);

    virtual bool initWithConfig(Config *config);
private:
    World *mWorld;

    void createWorld(Config *config);
};
