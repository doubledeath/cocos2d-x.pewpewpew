#include "Cannon.h"
#include "AppConsts.h"
#include "GameLogic/Projectile/CannonBall.h"

USING_NS_CC;

Cannon *Cannon::Create() {
    return Cannon::create();
}

bool Cannon::init() {
    if (!Sprite::initWithFile(AppConsts::Cannon::TEXTURE)) {
        return false;
    }

    auto WorldOrigin = Director::getInstance()->getVisibleOrigin();
    auto WorldSize = Director::getInstance()->getVisibleSize();

    setAnchorPoint(AppConsts::Cannon::INIT_ANCHOR_POINT);
    setPosition(Vec2(WorldOrigin.x + WorldSize.width * AppConsts::Cannon::INIT_X_FACTOR,
                     WorldOrigin.y + WorldSize.height * AppConsts::Cannon::INIT_Y_FACTOR));

    return true;
}

void Cannon::OnWorldTouchOrClick(cocos2d::Vec2 Location) {
    //Spawn a new CannonBall and move it if possible
    if (!IsReloading) {
        IsReloading = true;

        auto CannonBall = CannonBall::Create();

        auto Angle = CC_DEGREES_TO_RADIANS(getRotation());
        auto InitX =
                getPosition().x + sin(Angle) * (getContentSize().width / 2 + CannonBall->getContentSize().width / 2);
        auto InitY =
                getPosition().y + cos(Angle) * (getContentSize().height / 2 + CannonBall->getContentSize().height / 2);
        auto TargetX = getPosition().x + sin(Angle) * CannonBall->GetDistance();
        auto TargetY = getPosition().y + cos(Angle) * CannonBall->GetDistance();
        auto ShootCannonBall = MoveTo::create(CannonBall->GetVelocity(), Vec2(TargetX, TargetY));

        ShootCannonBall->setTag(CannonBall->GetShootTag());

        getParent()->addChild(CannonBall);

        CannonBall->setRotation(getRotation());
        CannonBall->setPosition(Vec2(InitX, InitY));
        CannonBall->runAction(ShootCannonBall);

        scheduleOnce(CC_SCHEDULE_SELECTOR(Cannon::OnReloaded), AppConsts::Cannon::RELOAD_DURATION);
    }
}

void Cannon::OnWorldLongTouchOrClick(cocos2d::Vec2 Location) {
    // Rotate cannon if possible
    if (!IsRotating) {
        IsRotating = true;

        auto Diff = getPosition() - Location;
        // By default rotation 0 degrees means face is to bottom of screen,
        // but our face have to be to top, so simulate it already rotated by 180 degrees
        auto Angle = CC_RADIANS_TO_DEGREES(atan2(Diff.x, Diff.y)) - AppConsts::Cannon::INIT_ROTATION;
        auto Action = Sequence::create(RotateTo::create(AppConsts::Cannon::ROTATE_DURATION, Angle),
                                       CallFunc::create([=]() {
                                           IsRotating = false;
                                       }), nullptr);
        runAction(Action);
    }
}

void Cannon::OnReloaded(float Delta) {
    IsReloading = false;
}

