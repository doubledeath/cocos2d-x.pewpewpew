#include "Projectile.h"
#include "GameLogic/Physics/CollidableType.h"
#include "GameLogic/Physics/CollidableTypeMask.h"

USING_NS_CC;

Projectile::Projectile()
{
    setType(static_cast<int>(CollidableType::projectile));
    setTypeMask(static_cast<int>(CollidableTypeMask::projectile));

    setMoveRotation(PhysicsConsts::Projectile::INIT_MOVE_ROTATION);
    setMoveVelocity(PhysicsConsts::Projectile::INIT_MOVE_VELOCITY);
    setMoveDistance(PhysicsConsts::Projectile::INIT_MOVE_DISTANCE);
}

void Projectile::onCollided()
{
    MovableSprite::onCollided();

    runAction(RemoveSelf::create(true));
}

int Projectile::getDamage() const
{
    return mDamage;
}

std::vector<Collidable *> Projectile::getPierceableList() const
{
    return mPierceableList;
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
