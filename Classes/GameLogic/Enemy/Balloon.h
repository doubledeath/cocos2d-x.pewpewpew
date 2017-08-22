#pragma once

#include "Enemy.h"

class Balloon : public Enemy
{
public:
    CREATE_FUNC(Balloon)

    virtual bool init() override;

    virtual void onSpawned(std::function<void (cocos2d::ParticleSystem *cannonBallTrail)> particleApplierDelegate);
protected:
    virtual void onDead() override;
private:
    std::function<void (cocos2d::ParticleSystem *cannonBallTrail)> mParticleApplierDelegate;
};
