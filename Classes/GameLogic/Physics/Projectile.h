#pragma once

#include "GameLogic/Physics/MovableSprite.h"
#include "PhysicsConsts.h"

class Projectile : public MovableSprite
{
public:
    Projectile();

    virtual void onCollided() override;

    virtual int getDamage() const;
    virtual std::vector<Collidable *> getPierceableList() const;
    virtual void setDamage(int damage);
    virtual void onSpawned(int initMoveRotation, std::vector<Collidable *> pierceableList);
private:
    int mDamage = PhysicsConsts::Projectile::BASE_DAMAGE;
    std::vector<Collidable *> mPierceableList;
};
