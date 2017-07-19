#include "MainScene.h"

USING_NS_CC;

Scene *MainScene::CreateScene() {
    return MainScene::create();
}

bool MainScene::init() {
    if (!Scene::init()) {
        return false;
    }

    return true;
}
