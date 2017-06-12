#pragma once

#include "cocos2d.h"

class Collidable {
public:
    virtual void CollidesToWorld() = 0;

    virtual void CollidesToNodes(std::vector<cocos2d::Node *> NodeList) = 0;

    bool IsCollisionForceIgnored();

    void SetCollisionForceIgnored(bool CollisionForceIgnored);

private:
    bool CollisionForceIgnored = false;
};
