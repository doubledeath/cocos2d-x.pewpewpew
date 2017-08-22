#pragma once

#include "cocos2d.h"

namespace WorldConsts
{
    namespace World
    {
        const float SINGLE_TOUCH_OR_CLICK_DISTANCE = 10;
        const float DOUBLE_TOUCH_OR_CLICK_TIME = 200; // Milliseconds
        const float LONG_TOUCH_OR_CLICK_TIME = 600; // Milliseconds
        const std::string SINGLE_TOUCH_OR_CLICK_KEY = "singleTouchOrClick";
    }
    namespace Enviorment
    {
        const std::string GRASS_AND_SKY_TMX = "Tmx/Envoirment/GrassAndSkyTilemap.tmx";
        const float GRASS_AND_SKY_SCALE = 2;
        const float GRASS_AND_SKY_LEFT_FACTOR = 0.27;
        const float GRASS_AND_SKY_BOTTOM_FACTOR = 0.41;
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
    }
    namespace Player
    {
        const float SPAWN_X_FACTOR = 0.5;
        const float SPAWN_Y_FACTOR = 0.125;
    }
}
