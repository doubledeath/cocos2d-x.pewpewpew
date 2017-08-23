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
        const std::string CONFIG_FILE_PATH = "Config/input.txt";
    }
}
