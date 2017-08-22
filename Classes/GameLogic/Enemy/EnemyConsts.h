#pragma once

#include "cocos2d.h"

namespace EnemyConsts
{
    namespace Enemy
    {
        const int INIT_MOVE_ROTATION = 0;
        const int INIT_MOVE_VELOCITY = 200;
        const int INIT_MOVE_DISTANCE = 10000;
        const int BASE_HIT_POINTS = 1;
    }
    namespace Balloon
    {
        const std::string TEXTURE = "Texture/Enemy/Balloon.png";
        const std::string EXPLOSION_PLIST = "Particle/Projectile/BalloonExplosion.plist";
        const float EXPLOSION_SCALE = 0.3;
    }
}
