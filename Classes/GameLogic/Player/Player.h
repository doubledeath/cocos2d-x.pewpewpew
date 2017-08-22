#pragma once

#include "cocos2d.h"
#include "GameLogic/Physics/Collidable.h"

class Player : public cocos2d::Sprite {
public:
    virtual void onWorldSingleTouchOrClick(cocos2d::Vec2 location) = 0;
    virtual void onWorldDoubleTouchOrClick(cocos2d::Vec2 location) = 0;
    virtual void onWorldLongTouchOrClick(cocos2d::Vec2 location) = 0;
};
