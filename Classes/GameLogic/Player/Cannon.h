#pragma once

#include "cocos2d.h"
#include "Player.h"
#include "GameLogic/Projectile/CannonBall.h"

class Cannon : public Player
{
public:
    CREATE_FUNC(Cannon)

    Cannon();

    virtual bool init();

    virtual void onWorldSingleTouchOrClick(cocos2d::Vec2 location);
    virtual void onWorldDoubleTouchOrClick(cocos2d::Vec2 location);
    virtual void onWorldLongTouchOrClick(cocos2d::Vec2 location);

    virtual void setAddToWorldDelegate(const std::function<void (CannonBall *cannonBall)> &addToWorldDelegate);
    virtual void setGetCannonBallPierceableListDelegate(const std::function<std::vector<Collidable *> ()> &getCannonBallPierceableListDelegate);
    virtual void setParticleApplierDelegate(const std::function<void (cocos2d::ParticleSystem *particle)> &particleApplierDelegate);
private:
    bool mIsReloading = false;
    bool mIsRotating = false;
    std::function<void (CannonBall *cannonBall)> mAddToWorldDelegate = nullptr;
    std::function<std::vector<Collidable *> ()> mGetCannonBallPierceableListDelegate = nullptr;
    std::function<void (cocos2d::ParticleSystem *cannonBallTrail)> mParticleApplierDelegate = nullptr;

    void rotate(cocos2d::Vec2 location);
    void pew();
    void onReloaded();
};
