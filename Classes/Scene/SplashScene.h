#pragma once

#include "cocos2d.h"
#include "Support/Config.h"

class SplashScene : public cocos2d::Scene
{
public:
    CREATE_FUNC(SplashScene)

    virtual bool init() override;
private:
    Config *mConfig;

    void loadConfig();
    void startMainScene(float delta);
};
