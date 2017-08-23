#include "CannonBall.h"
#include "ProjectileConsts.h"
#include "Support/Config.h"

USING_NS_CC;

CannonBall::CannonBall()
{
    setLocalZOrder(ProjectileConsts::CannonBall::Z_ORDER);
    setMoveVelocity(Config::getInstance().getSpeed());
    setIsCircle(true);
}

bool CannonBall::init()
{
    if (!Sprite::initWithFile(ProjectileConsts::CannonBall::TEXTURE))
    {
        return false;
    }

    scheduleUpdate();

    return true;
}

void CannonBall::update(float delta)
{
    mTrail->setPosition(getPosition());
}

void CannonBall::onCollided()
{
    Projectile::onCollided();

    if (mTrail) { mTrail->stopSystem(); }
}

void CannonBall::onSpawned(int initMoveRotation, std::vector<Collidable *> pierceableList, std::function<void (ParticleSystem *cannonBallTrail)> particleApplierDelegate)
{
    mTrail = ParticleSystemQuad::create(ProjectileConsts::CannonBall::TRAIL_PLIST);

    mTrail->setLocalZOrder(ProjectileConsts::CannonBall::TRAIL_Z_ORDER);
    mTrail->setAutoRemoveOnFinish(true);

    particleApplierDelegate(mTrail);

    Projectile::onSpawned(initMoveRotation, pierceableList);
}
