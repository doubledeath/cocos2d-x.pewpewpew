#pragma once

#include "cocos2d.h"
#include "GameLogic/Physics/MRSprite.h"
#include "GameLogic/Physics/Damageable.h"
#include "EnemyConsts.h"

class Enemy : public virtual MRSprite, public virtual Damageable
{
public:
    Enemy();

    virtual int getHitPoints() const override;

    virtual void onSpawned();
protected:
    virtual void setHitPoints(int hitPoints) override;
    virtual void onDamaged() override;
    virtual void onDead() override;
private:
    int mHitPoints = EnemyConsts::Enemy::BASE_HIT_POINTS;
};
