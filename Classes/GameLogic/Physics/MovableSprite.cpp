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

void MovableSprite::moveBy(Vec2 moveChange, int moveVelocity, CallFunc *onMovedBy)
{
    auto moveBy = MoveBy::create(getMoveDuration(moveVelocity), moveChange);
    auto moveByAndNotify = Sequence::create(moveBy, onMovedBy, nullptr);

    moveByAndNotify->setTag(PhysicsConsts::MovableSprite::MOVE_BY_TAG);

    runAction(moveByAndNotify);
}

void MovableSprite::interruptMoveBy()
{
    stopActionByTag(PhysicsConsts::MovableSprite::MOVE_BY_TAG);
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
