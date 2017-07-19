#pragma once

#include "cocos2d.h"

class CollisionManager {
public:
    virtual bool IsCollidesToWorld(cocos2d::Node *Node) = 0;

    virtual bool IsCollidesToNode(cocos2d::Node *Node, cocos2d::Node *Target) = 0;
};
