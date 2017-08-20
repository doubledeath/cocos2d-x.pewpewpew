#pragma once

#include "cocos2d.h"
#include "CollidableSprite.h"
#include "Movable.h"

class MovableSprite : public CollidableSprite, public virtual Movable
{
public:
    virtual void onCollided() override;
    virtual void onCollisionResolved() override;

    virtual void moveBy(cocos2d::Vec2 moveChange, int moveVelocity, cocos2d::CallFunc *onMovedBy) override;
    virtual void interruptMoveBy() override;
protected:
    virtual void moveToRotation() override;
    virtual void interruptMoveToRotation() override;
private:
    float getMoveDuration(int moveVelocity) const;
};
