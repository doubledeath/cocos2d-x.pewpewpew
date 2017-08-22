#include "Enemy.h"
#include "GameLogic/Physics/CollidableType.h"
#include "GameLogic/Physics/CollidableTypeMask.h"

USING_NS_CC;

Enemy::Enemy()
{
    setType(static_cast<int>(CollidableType::base));
    setTypeMask(static_cast<int>(CollidableTypeMask::base));

    setMoveRotation(EnemyConsts::Enemy::INIT_MOVE_ROTATION);
    setMoveVelocity(EnemyConsts::Enemy::INIT_MOVE_VELOCITY);
    setMoveDistance(EnemyConsts::Enemy::INIT_MOVE_DISTANCE);
}

int Enemy::getHitPoints() const
{
    return mHitPoints;
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
