#pragma once

#include "cocos2d.h"

namespace AppConsts
{
    namespace AppDelegate
    {
        const cocos2d::Size DESIGN_RESOLUTION_SIZE(600, 1080);
        const cocos2d::Size SMALL_RESOLUTION_SIZE(266, 480);
        const cocos2d::Size MEDIUM_RESOLUTION_SIZE(568, 1024);
        const cocos2d::Size LARGE_RESOLUTION_SIZE(1137, 2048);
    }
    namespace SplashScene
    {
        const float LOADING_TIME = 1; // Seconds
        const float LOADING_FADE_TIME = 0.5; // Seconds
    }
//    namespace World
//    {
//        const float TOUCH_OR_CLICK_DISTANCE = 10;
//        const float LONG_TOUCH_OR_CLICK_TIME = 1000; // Milliseconds
//        const cocos2d::Color4F BACKGROUND_COLOR(cocos2d::Color4B(0x0B, 0x66, 0x23, 0xFF));
//        const float ENEMIES_FIELD_WIDTH_FACTOR = 0.70;
//        const float ENEMIES_FIELD_BOTTOM_FACTOR = 0.50;
//    }
//    namespace Enemy
//    {
//        const int VELOCITY = 4;
//        const int VELOCITY_FACTOR = 1;
//        const int HIT_POINTS = 1;
//    }
//    namespace Balloon
//    {
//        const std::string TEXTURE = "Texture/Enemy/Balloon.png";
//        const float X_FACTOR = 0.5;
//        const float Y_FACTOR = 0.875;
//        const cocos2d::Vec2 ANCHOR_POINT(0.5, 0.5);
//        const int MAX_VELOCITY = 1000; //52
//        const int VELOCITY_FACTOR = 14; //13
//        const int FLY_TAG = 201;
//    }
//    namespace Cannon {
//        const std::string TEXTURE = "Texture/Player/Cannon.png";
//        const float X_FACTOR = 0.5;
//        const float Y_FACTOR = 0.125;
//        const float ROTATION = 180;
//        const cocos2d::Vec2 ANCHOR_POINT(0.5, 0.5);
//        const float ROTATE_DURATION = 1;
//        const float RELOAD_DURATION = 1;
//    }
//    namespace Projectile {
//        const int SHOOT_TAG = 1601;
//        const int VELOCITY = 16;
//        const int VELOCITY_FACTOR = 1;
//        const float DISTANCE = 1000;
//        const int DAMAGE = 1;
//        const int DAMAGE_FACTOR = 1;
//    }
//    namespace CannonBall {
//        const std::string TEXTURE = "Texture/Projectile/CannonBall.png";
//        const cocos2d::Vec2 ANCHOR_POINT(0.5, 0.5);
//    }
}
