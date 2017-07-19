#pragma once

#include "cocos2d.h"
#include "GameLogic/Collidable.h"
#include "AppConsts.h"

class Enemy : public cocos2d::Sprite, public Collidable {
public:
    /**
     * Call this after spawn
     */
    virtual void OnSpawned() = 0;

    virtual bool CollidesToNodes(std::vector<cocos2d::Node *> Nodes);

    float GetVelocity();

    float GetVelocityFactor();

    float GetHitPoints();

    void SetVelocityFactor(float VelocityFactor);

protected:
    void SetVelocity(float Velocity);

    void SetHitPoints(float HitPoints);

private:
    float Velocity = AppConsts::Enemy::VELOCITY;
    float VelocityFactor = AppConsts::Enemy::VELOCITY_FACTOR;
    float HitPoints = AppConsts::Enemy::HIT_POINTS;
};
