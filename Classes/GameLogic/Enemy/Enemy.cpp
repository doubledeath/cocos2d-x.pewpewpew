#include "Enemy.h"
#include "GameLogic/Physics/CollidableType.h"
#include "GameLogic/Physics/CollidableTypeMask.h"

USING_NS_CC;

Enemy::Enemy()
{
    setType(static_cast<int>(CollidableType::base));
    setTypeMask(static_cast<int>(CollidableTypeMask::base));
}

int Enemy::getMoveRotation() const
{
    return mMoveRotation;
}

int Enemy::getMoveVelocity() const
{
    return mMoveVelocity;
}

int Enemy::getMoveDistance() const
{
    return mMoveDistance;
}

void Enemy::setMoveRotation(int moveRotation)
{
    mMoveRotation = moveRotation;
}

int Enemy::getHitPoints() const
{
    return mHitPoints;
}

void Enemy::setMoveVelocity(int moveVelocity)
{
    mMoveVelocity = moveVelocity;
}

void Enemy::setMoveDistance(int moveDistance)
{
    mMoveDistance = moveDistance;
}

void Enemy::onSpawned()
{
    // Add a random init move rotation
    setMoveRotation(RandomHelper::random_int(0, 359));

    moveToRotation();
}

void Enemy::setHitPoints(int hitPoints)
{
    mHitPoints = hitPoints;
}

void Enemy::onDamaged()
{

}

void Enemy::onDead()
{
    interruptResolving();
    interruptMoveToRotation();

    runAction(RemoveSelf::create(true));
}
