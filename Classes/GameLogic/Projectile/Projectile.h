#pragma once

#include "cocos2d.h"
#include "AppConsts.h"
#include "GameLogic/Collidable.h"

class Projectile : public cocos2d::Sprite, public Collidable {
public:
    virtual void CollidesToWorld();

    virtual void CollidesToNodes(std::vector<cocos2d::Node *> Nodes);

    int GetShootTag();

    float GetDistance();

    float GetVelocityFactor();

    float GetVelocity();

    void SetVelocityFactor(float VelocityFactor);

protected:
    void SetShootTag(int ShootTag);

    void SetDistance(float Distance);

    void SetVelocity(float Velocity);

private:
    int ShootTag = AppConsts::Projectile::SHOOT_TAG;
    float Velocity = AppConsts::Projectile::VELOCITY;
    float VelocityFactor = AppConsts::Projectile::VELOCITY_FACTOR;
    float Distance = AppConsts::Projectile::DISTANCE;
};
