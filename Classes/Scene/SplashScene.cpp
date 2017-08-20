#include "SplashScene.h"
#include "../AppConsts.h"
#include "MainScene.h"

USING_NS_CC;

bool SplashScene::init()
{
    if (!Scene::init())
    {
        return false;
    }

    scheduleOnce(CC_SCHEDULE_SELECTOR(SplashScene::startMainScene), AppConsts::SplashScene::LOADING_TIME);

    return true;
}

void SplashScene::startMainScene(float delta)
{
    Director::getInstance()->replaceScene(TransitionFade::create(AppConsts::SplashScene::LOADING_FADE_TIME, MainScene::create()));
}
