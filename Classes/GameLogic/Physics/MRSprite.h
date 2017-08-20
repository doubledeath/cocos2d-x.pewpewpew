#pragma once

#include "cocos2d.h"
#include "MovableSprite.h"
#include "Resolvable.h"

class MRSprite : public MovableSprite, public virtual Resolvable
{
public:
    virtual void resolve(cocos2d::Vec2 resolveChange, int resolveVelocity, cocos2d::CallFunc *onResolved) override;
    virtual void interruptResolving() override;
};
