#include "MovableSprite.h"
#include "PhysicsConsts.h"

USING_NS_CC;

void MovableSprite::onCollided()
{
    Movable::onCollided();
}

void MovableSprite::onCollisionResolved()
{
    Movable::onCollisionResolved();
}

int MovableSprite::getMoveRotation() const
{
    return mMoveRotation;
}

int MovableSprite::getMoveVelocity() const
{
    return mMoveVelocity;
}

int MovableSprite::getMoveDistance() const
{
    return mMoveDistance;
}

void MovableSprite::setMoveRotation(int moveRotation)
{
    mMoveRotation = moveRotation;
}

void MovableSprite::setMoveVelocity(int moveVelocity)
{
    mMoveVelocity = moveVelocity;
}

void MovableSprite::setMoveDistance(int moveDistance)
{
    mMoveDistance = moveDistance;
}

void MovableSprite::moveToRotation()
{
    auto moveToRotation = MoveBy::create(getMoveDuration(getMoveVelocity()), getMoveChange());

    moveToRotation->setTag(PhysicsConsts::MovableSprite::MOVE_TO_ROTATION_TAG);

    runAction(moveToRotation);
}

void MovableSprite::interruptMoveToRotation()
{
    stopActionByTag(PhysicsConsts::MovableSprite::MOVE_TO_ROTATION_TAG);
}

float MovableSprite::getMoveDuration(int moveVelocity) const
{
    return static_cast<float>(getMoveDistance()) / static_cast<float>(moveVelocity);
}
