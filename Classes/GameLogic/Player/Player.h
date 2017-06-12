#pragma once

#include "cocos2d.h"

class Player : public cocos2d::Sprite {
public:
    virtual void OnWorldTouchOrClick(cocos2d::Vec2 Location) = 0;

    virtual void OnWorldLongTouchOrClick(cocos2d::Vec2 Location) = 0;
};
