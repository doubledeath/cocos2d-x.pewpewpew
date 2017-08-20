#pragma once

#include "cocos2d.h"
#include "Collidable.h"

class Movable : public virtual Collidable
{
public:
    virtual void onCollided() override;
    virtual void onCollisionResolved() override;

    virtual int getMoveRotation() const = 0;
    virtual int getMoveVelocity() const = 0;
    virtual int getMoveDistance() const = 0;
    virtual void setMoveRotation(int moveRotation) = 0;
    virtual void moveBy(cocos2d::Vec2 moveChange, int moveVelocity, cocos2d::CallFunc *onMovedBy) = 0;
    virtual void interruptMoveBy() = 0;
protected:
    virtual void moveToRotation() = 0;
    virtual void interruptMoveToRotation() = 0;

    virtual cocos2d::Vec2 getMoveChange();
};
