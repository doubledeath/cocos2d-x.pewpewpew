#pragma once

#include "cocos2d.h"

class SplashScene : public cocos2d::Scene
{
public:
    CREATE_FUNC(SplashScene)

    virtual bool init() override;
private:
    void startMainScene(float delta);
};
