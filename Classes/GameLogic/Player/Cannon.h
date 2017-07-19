#pragma once

#include "cocos2d.h"
#include "Player.h"

class Cannon : public Player {
public:
    static Cannon *Create();

    virtual bool init();

    CREATE_FUNC(Cannon);

    virtual void OnWorldTouchOrClick(cocos2d::Vec2 Location);

    virtual void OnWorldLongTouchOrClick(cocos2d::Vec2 Location);

private:
    bool IsReloading;
    bool IsRotating;

    void OnReloaded(float Delta);
};
