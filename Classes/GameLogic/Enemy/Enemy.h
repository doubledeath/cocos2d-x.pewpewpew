#pragma once

#include "cocos2d.h"
#include "GameLogic/Collidable.h"

class Enemy : public cocos2d::Sprite, public Collidable {
public:
    virtual void CollidesToWorld();

    virtual void CollidesToNodes(std::vector<cocos2d::Node *> Nodes);
};
