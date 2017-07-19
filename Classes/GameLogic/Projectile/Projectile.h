#pragma once

#include "cocos2d.h"
#include "AppConsts.h"
#include "GameLogic/Collidable.h"

class Projectile : public cocos2d::Sprite, public Collidable {
public:
    virtual void CollidesToWorld();

    virtual bool CollidesToNodes(std::vector<cocos2d::Node *> Nodes);

    int GetShootTag();

    float GetVelocity();

    float GetVelocityFactor();

    float GetDistance();

    float GetDamage();

    void SetVelocityFactor(float VelocityFactor);

    void SetDamageFactor(float DamageFactor);

protected:
    void SetShootTag(int ShootTag);

    void SetVelocity(float Velocity);

    void SetDistance(float Distance);

    void SetDamage(float Damage);

private:
    int ShootTag = AppConsts::Projectile::SHOOT_TAG;
    float Velocity = AppConsts::Projectile::VELOCITY;
    float VelocityFactor = AppConsts::Projectile::VELOCITY_FACTOR;
    float Distance = AppConsts::Projectile::DISTANCE;
    float Damage = AppConsts::Projectile::DAMAGE;
    float DamageFactor = AppConsts::Projectile::DAMAGE_FACTOR;
};
