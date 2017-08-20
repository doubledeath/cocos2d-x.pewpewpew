#pragma once

#include "cocos2d.h"

class Collidable
{
public:
    virtual cocos2d::Rect getRect() const = 0;
    virtual int getType() const = 0;
    virtual int getTypeMask() const = 0;
    virtual void onCollided() = 0;
    virtual void onCollisionResolved() = 0;
};
