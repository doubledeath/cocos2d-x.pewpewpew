#include "AppConsts.h"

USING_NS_CC;

namespace AppConsts {
    namespace SplashScene {
        const float LOADING_TIME = 3;
        const float FADE_TIME = 1;
    }
    namespace World {
        const float TOUCH_OR_CLICK_DISTANCE = 10;
        const float LONG_TOUCH_OR_CLICK_TIME = 1000;
        const Color4F BACKGROUND_COLOR = Color4F(Color4B(0x0B, 0x66, 0x23, 0xFF));
    }
    namespace Cannon {
        const std::string TEXTURE = "Texture/Player/Cannon.png";
        const float INIT_X_FACTOR = 0.5;
        const float INIT_Y_FACTOR = 0.125;
        const float INIT_ROTATION = 180;
        const Vec2 INIT_ANCHOR_POINT = Vec2(0.5, 0.5);
        const float ROTATE_DURATION = 1;
        const float RELOAD_DURATION = 1;
    }
    namespace Projectile {
        const int SHOOT_TAG = 1601;
        const float VELOCITY = 2.71;
        const float VELOCITY_FACTOR = 1;
        const float DISTANCE = 1000;
        const float DAMAGE = 1;
        const float DAMAGE_FACTOR = 1;
    }
    namespace CannonBall {
        const std::string TEXTURE = "Texture/Projectile/CannonBall.png";
        const Vec2 INIT_ANCHOR_POINT = Vec2(0.5, 0.5);
    }
    namespace Enemy {
        const float VELOCITY = 2.71;
        const float VELOCITY_FACTOR = 1;
        const float HIT_POINTS = 1;
    }
    namespace Balloon {
        const std::string TEXTURE = "Texture/Enemy/Balloon.png";
        const float INIT_X_FACTOR = 0.5;
        const float INIT_Y_FACTOR = 0.875;
        const Vec2 INIT_ANCHOR_POINT = Vec2(0.5, 0.5);
        const float VELOCITY_FACTOR = 0.1;
        const int FLY_TAG = 201;
    }
    namespace Wind {
        const std::string TMX = "Tmx/GameObject/Wind.tmx";
        const float INIT_X_FACTOR = 0.5;
        const float INIT_Y_FACTOR = 0.5;
        const cocos2d::Vec2 INIT_ANCHOR_POINT = Vec2(0.5, 0.5);
    }
}