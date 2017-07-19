#pragma once

#include "cocos2d.h"

class SplashScene : public cocos2d::Scene {
public:
    static cocos2d::Scene *CreateScene();

    virtual bool init();

    CREATE_FUNC(SplashScene);
private:
    void StartMainScene(float Delta);
};
