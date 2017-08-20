#pragma once

#include "cocos2d.h"
#include "GameLogic/Physics/Collidable.h"

class Player : public cocos2d::Sprite {
public:
    virtual void onWorldTouchOrClick(cocos2d::Vec2 Location) = 0;
    virtual void onWorldLongTouchOrClick(cocos2d::Vec2 Location) = 0;
};
