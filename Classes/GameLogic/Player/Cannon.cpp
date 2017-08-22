#include "Cannon.h"
#include "GameLogic/Projectile/CannonBall.h"
#include "PlayerConsts.h"

USING_NS_CC;

Cannon::Cannon()
{
    setLocalZOrder(PlayerConsts::Cannon::Z_ORDER);
}

bool Cannon::init()
{
    if (!Sprite::initWithFile(PlayerConsts::Cannon::TEXTURE))
    {
        return false;
    }

    return true;
}

void Cannon::onWorldSingleTouchOrClick(Vec2 location)
{
    pew();
}

void Cannon::onWorldDoubleTouchOrClick(Vec2 location)
{
    rotate(location);
}

void Cannon::onWorldLongTouchOrClick(Vec2 location)
{
    rotate(location);
}

void Cannon::setAddToWorldDelegate(const std::function<void (CannonBall *cannonBall)> &addToWorldDelegate)
{
    mAddToWorldDelegate = addToWorldDelegate;
}

void Cannon::setGetCannonBallPierceableListDelegate(const std::function<std::vector<Collidable *> ()> &getCannonBallPierceableListDelegate)
{
    mGetCannonBallPierceableListDelegate = getCannonBallPierceableListDelegate;
}

void Cannon::rotate(Vec2 location)
{
    // Rotate cannon if possible
    if (!mIsRotating) {
        mIsRotating = true;

        auto diff = getPosition() - location;
        // Simmulate init rotation
        auto angle = CC_RADIANS_TO_DEGREES(atan2(diff.x, diff.y)) - PlayerConsts::Cannon::INIT_ROTATION;
        auto rotateAction = RotateTo::create(PlayerConsts::Cannon::ROTATE_DURATION, angle);
        auto callback = CallFunc::create([=]() { mIsRotating = false; });
        auto sequence = Sequence::create(rotateAction, callback, nullptr);

        runAction(sequence);
    }
}

void Cannon::pew()
{
    // Pew by a new CannonBall if possible
    if (mAddToWorldDelegate && !mIsReloading && !mIsRotating) {
        mIsReloading = true;

        auto cannonBall = CannonBall::create();
        auto cannonBallPierceableList = mGetCannonBallPierceableListDelegate ? mGetCannonBallPierceableListDelegate() : std::vector<Collidable *> ();

        cannonBall->setPosition(Vec2(getBoundingBox().getMidX(), getBoundingBox().getMidY()));

        mAddToWorldDelegate(cannonBall);

        cannonBall->onSpawned(getRotation(), cannonBallPierceableList);

        scheduleOnce([=](float delta) { onReloaded(); }, PlayerConsts::Cannon::RELOAD_DURATION, PlayerConsts::Cannon::PEW_KEY);
    }
}

void Cannon::onReloaded()
{
    mIsReloading = false;
}
