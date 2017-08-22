#pragma once

#include "GameLogic/Physics/Projectile.h"

class CannonBall : public Projectile {
public:
    CREATE_FUNC(CannonBall)

    CannonBall();

    virtual bool init();
    virtual void update(float delta) override;

    virtual void onCollided() override;

    virtual void onSpawned(int initMoveRotation, std::vector<Collidable *> pierceableList, std::function<void (cocos2d::ParticleSystem *cannonBallTrail)> particleApplierDelegate);
private:
    cocos2d::ParticleSystem *mTrail;
};
