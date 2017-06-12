#pragma once

#include "cocos2d.h"
#include "Projectile.h"

class CannonBall : public Projectile {
public:
    static CannonBall *Create();

    virtual bool init();

    CREATE_FUNC(CannonBall);
};
