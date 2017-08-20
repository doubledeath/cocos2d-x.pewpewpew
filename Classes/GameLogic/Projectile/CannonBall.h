#pragma once

#include "GameLogic/Physics/Projectile.h"

class CannonBall : public Projectile {
public:
    CREATE_FUNC(CannonBall)

    virtual bool init();
};
