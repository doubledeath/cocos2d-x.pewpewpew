#pragma once

#include "cocos2d.h"
#include "CollidableSprite.h"
#include "Movable.h"

class MovableSprite : public CollidableSprite, public virtual Movable
{
public:
    virtual void onCollided() override;
    virtual void onCollisionResolved() override;

    virtual int getMoveRotation() const override;
    virtual int getMoveVelocity() const override;
    virtual int getMoveDistance() const override;
    virtual void setMoveRotation(int moveRotation) override;

    virtual void setMoveVelocity(int moveVelocity);
    virtual void setMoveDistance(int moveDistance);
protected:
    virtual void moveToRotation() override;
    virtual void interruptMoveToRotation() override;

    float getMoveDuration(int moveVelocity) const;
private:
    int mMoveRotation;
    int mMoveVelocity;
    int mMoveDistance;
};
