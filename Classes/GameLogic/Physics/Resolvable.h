#pragma once

#include "Collidable.h"

class Resolvable : public virtual Collidable
{
public:
    virtual void resolve(cocos2d::Vec2 resolveChange, int resolveVelocity, cocos2d::CallFunc *onResolved) = 0;
    virtual void interruptResolving() = 0;
};
