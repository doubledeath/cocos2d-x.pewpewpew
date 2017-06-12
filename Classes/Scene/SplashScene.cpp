#include "SplashScene.h"
#include "../AppConsts.h"
#include "MainScene.h"

USING_NS_CC;

Scene *SplashScene::CreateScene() {
    return SplashScene::create();
}

bool SplashScene::init() {
    if (!Scene::init()) {
        return false;
    }

    //todo

    //
    this->scheduleOnce(CC_SCHEDULE_SELECTOR(SplashScene::StartMainScene), AppConsts::SplashScene::LOADING_TIME);

    return true;
}

void SplashScene::StartMainScene(float Delay) {
    Director::getInstance()->replaceScene(TransitionFade::create(AppConsts::SplashScene::FADE_TIME, MainScene::CreateScene()));
}
