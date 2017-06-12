#include "MainScene.h"

USING_NS_CC;

Scene *MainScene::CreateScene() {
    return MainScene::create();
}

bool MainScene::init() {
    if (!Scene::init()) {
        return false;
    }

    CreateWorld();

    return true;
}

void MainScene::CreateWorld() {
    World = World::Create();

    addChild(World);
}
