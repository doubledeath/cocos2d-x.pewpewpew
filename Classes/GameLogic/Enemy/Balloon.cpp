#include "Balloon.h"

USING_NS_CC;

Balloon::Balloon()
{
    setIsCircle(true);
}

bool Balloon::init()
{
    if (!Enemy::initWithFile(EnemyConsts::Balloon::TEXTURE))
    {
        return false;
    }

    return true;
}

void Balloon::onSpawned(std::function<void (ParticleSystem *)> particleApplierDelegate)
{
    mParticleApplierDelegate = particleApplierDelegate;

    Enemy::onSpawned();
}

void Balloon::onDead()
{
    Enemy::onDead();

    if (mParticleApplierDelegate)
    {
        auto explosion = ParticleSystemQuad::create(EnemyConsts::Balloon::EXPLOSION_PLIST);

        explosion->setAutoRemoveOnFinish(true);
        explosion->setPosition(getPosition());
        explosion->setScale(EnemyConsts::Balloon::EXPLOSION_SCALE);

        mParticleApplierDelegate(explosion);
        mParticleApplierDelegate = nullptr;
    }
}
