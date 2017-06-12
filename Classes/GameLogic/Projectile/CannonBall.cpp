#include "CannonBall.h"

USING_NS_CC;

CannonBall *CannonBall::Create() {
    return CannonBall::create();
}

bool CannonBall::init() {
    if (!Sprite::initWithFile(AppConsts::CannonBall::TEXTURE)) {
        return false;
    }

    setAnchorPoint(AppConsts::CannonBall::INIT_ANCHOR_POINT);

    return true;
}
