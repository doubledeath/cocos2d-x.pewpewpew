#pragma once

#include "cocos2d.h"
#include "CollidableSprite.h"
#include "Movable.h"

class MovableSprite : public CollidableSprite, public virtual Movable
{
public:
    virtual void onCollided() override;
    virtual void onCollisionResolved() override;
protected:
    virtual void moveToRotation() override;
    virtual void interruptMoveToRotation() override;

    float getMoveDuration(int moveVelocity) const;
};
