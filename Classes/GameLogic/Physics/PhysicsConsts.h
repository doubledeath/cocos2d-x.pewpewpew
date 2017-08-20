#pragma once

#include "cocos2d.h"

namespace PhysicsConsts
{
    namespace Movable
    {
        const int RESOLVE_COLLISION_VELOCITY_FACTOR = 500;
    }
    namespace MovableSprite
    {
        const int MOVE_BY_TAG = 1301;
        const int MOVE_TO_ROTATION_TAG = 1302;
    }
    namespace Projectile
    {
        const int INIT_MOVE_ROTATION = 0;
        const int INIT_MOVE_VELOCITY = 200;
        const int INIT_MOVE_DISTANCE = 10000;
        const int BASE_DAMAGE = 1;
    }
}
