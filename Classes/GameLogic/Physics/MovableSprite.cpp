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
