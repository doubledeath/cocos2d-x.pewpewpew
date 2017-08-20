#pragma once

#include "GameLogic/Physics/MovableSprite.h"
#include "PhysicsConsts.h"

class Projectile : public MovableSprite
{
public:
    Projectile();

    virtual void onCollided() override;

    virtual int getMoveRotation() const override;
    virtual int getMoveVelocity() const override;
    virtual int getMoveDistance() const override;
    virtual void setMoveRotation(int moveRotation) override;

    virtual int getDamage() const;
    std::vector<Collidable *> getPierceableList() const;
    virtual void setMoveVelocity(int moveVelocity);
    virtual void setMoveDistance(int moveDistance);
    virtual void setDamage(int damage);
    virtual void onSpawned(int initMoveRotation, std::vector<Collidable *> pierceableList);
private:
    int mMoveRotation = PhysicsConsts::Projectile::INIT_MOVE_ROTATION;
    int mMoveVelocity = PhysicsConsts::Projectile::INIT_MOVE_VELOCITY;
    int mMoveDistance = PhysicsConsts::Projectile::INIT_MOVE_DISTANCE;
    int mDamage = PhysicsConsts::Projectile::BASE_DAMAGE;
    std::vector<Collidable *> mPierceableList;
};
