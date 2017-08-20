#include "Projectile.h"
#include "GameLogic/Physics/CollidableType.h"
#include "GameLogic/Physics/CollidableTypeMask.h"

USING_NS_CC;

Projectile::Projectile()
{
    setType(static_cast<int>(CollidableType::projectile));
    setTypeMask(static_cast<int>(CollidableTypeMask::projectile));
}

void Projectile::onCollided()
{
    interruptMoveToRotation();

    runAction(RemoveSelf::create(true));
}

int Projectile::getMoveRotation() const
{
    return mMoveRotation;
}

int Projectile::getMoveVelocity() const
{
    return mMoveVelocity;
}

int Projectile::getMoveDistance() const
{
    return mMoveDistance;
}

void Projectile::setMoveRotation(int moveRotation)
{
    mMoveRotation = moveRotation;
}

int Projectile::getDamage() const
{
    return mDamage;
}

std::vector<Collidable *> Projectile::getPierceableList() const
{
    return mPierceableList;
}

void Projectile::setMoveVelocity(int moveVelocity)
{
    mMoveVelocity = moveVelocity;
}

void Projectile::setMoveDistance(int moveDistance)
{
    mMoveDistance = moveDistance;
}

void Projectile::setDamage(int damage)
{
    mDamage = damage;
}

void Projectile::onSpawned(int initMoveRotation, std::vector<Collidable *> pierceableList)
{
    setMoveRotation(initMoveRotation);

    mPierceableList = pierceableList;

    moveToRotation();
}
