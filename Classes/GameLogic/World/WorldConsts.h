#pragma once

#include "cocos2d.h"

namespace WorldConsts
{
    namespace World
    {
        const float TOUCH_OR_CLICK_DISTANCE = 10;
        const float LONG_TOUCH_OR_CLICK_TIME = 500; // Milliseconds
        const cocos2d::Color4F BACKGROUND_COLOR(cocos2d::Color4B(0x9C, 0xCC, 0x65, 0xFF));
    }
    namespace Enemy
    {
        const int SPAWN_COUNT = 7;
        const float SPAWN_INTERVAL = 0.3;
        const float SPAWN_DELAY = 1;
        const std::string SPAWN_KEY = "spawnEnemies";
        const float SPAWN_X_FACTOR = 0.5;
        const float SPAWN_Y_FACTOR = 0.8;
        const float ZONE_WIDTH_FACTOR = 1;
        const float ZONE_BOTTOM_FACTOR = 0.4;
        const cocos2d::Color4F ZONE_BACKGROUND_COLOR(cocos2d::Color4B(0x29, 0xB6, 0xF6, 0xFF));
    }
    namespace Player
    {
        const float SPAWN_X_FACTOR = 0.5;
        const float SPAWN_Y_FACTOR = 0.125;
    }
}
