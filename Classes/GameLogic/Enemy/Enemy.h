#pragma once

#include "cocos2d.h"
#include "GameLogic/Physics/MovableSprite.h"
#include "GameLogic/Physics/Damageable.h"
#include "EnemyConsts.h"

class Enemy : public virtual MovableSprite, public virtual Damageable
{
public:
    Enemy();

    virtual int getMoveRotation() const override;
    virtual int getMoveVelocity() const override;
    virtual int getMoveDistance() const override;
    virtual void setMoveRotation(int moveRotation) override;

    virtual int getHitPoints() const override;

    virtual void setMoveVelocity(int moveVelocity);
    virtual void setMoveDistance(int moveDistance);
    virtual void onSpawned();
protected:
    virtual void setHitPoints(int hitPoints) override;
    virtual void onDamaged() override;
    virtual void onDead() override;
private:
    int mMoveRotation = EnemyConsts::Enemy::INIT_MOVE_ROTATION;
    int mMoveVelocity = EnemyConsts::Enemy::INIT_MOVE_VELOCITY;
    int mMoveDistance = EnemyConsts::Enemy::INIT_MOVE_DISTANCE;
    int mHitPoints = EnemyConsts::Enemy::BASE_HIT_POINTS;
};
