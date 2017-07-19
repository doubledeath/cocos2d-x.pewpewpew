#pragma once

#include "cocos2d.h"
#include "GameLogic/Collidable.h"

class Wind : public cocos2d::TMXTiledMap, public Collidable {
public:
    static Wind *Create();

    virtual bool init();

    CREATE_FUNC(Wind);

    virtual void CollidesToWorld();

    virtual bool CollidesToNodes(std::vector<cocos2d::Node *> Nodes);
};
