#pragma once

#include "cocos2d.h"

namespace AppConsts {
    namespace SplashScene {
        extern const float LOADING_TIME; // Seconds
        extern const float FADE_TIME; // Seconds
    }
    namespace World {
        extern const float TOUCH_OR_CLICK_DISTANCE;
        extern const float LONG_TOUCH_OR_CLICK_TIME; // Milliseconds
        extern const cocos2d::Color4F BACKGROUND_COLOR;
    }
    namespace Cannon {
        extern const std::string TEXTURE;
        extern const float INIT_X_FACTOR;
        extern const float INIT_Y_FACTOR;
        extern const float INIT_ROTATION;
        extern const cocos2d::Vec2 INIT_ANCHOR_POINT;
        extern const float ROTATE_DURATION;
        extern const float RELOAD_DURATION;
    }
    namespace Projectile {
        extern const int SHOOT_TAG;
        extern const float VELOCITY;
        extern const float VELOCITY_FACTOR;
        extern const float DISTANCE;
        extern const float DAMAGE;
        extern const float DAMAGE_FACTOR;
    }
    namespace CannonBall {
        extern const std::string TEXTURE;
        extern const cocos2d::Vec2 INIT_ANCHOR_POINT;
    }
    namespace Enemy {
        extern const float VELOCITY;
        extern const float VELOCITY_FACTOR;
        extern const float HIT_POINTS;
    }
    namespace Balloon {
        extern const std::string TEXTURE;
        extern const float INIT_X_FACTOR;
        extern const float INIT_Y_FACTOR;
        extern const cocos2d::Vec2 INIT_ANCHOR_POINT;
        extern const float VELOCITY_FACTOR;
        extern const int FLY_TAG;
    }
    namespace Wind {
        extern const std::string TMX;
        extern const float INIT_X_FACTOR;
        extern const float INIT_Y_FACTOR;
        extern const cocos2d::Vec2 INIT_ANCHOR_POINT;
    }
}
