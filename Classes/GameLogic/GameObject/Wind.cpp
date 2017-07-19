#include "Wind.h"
#include "AppConsts.h"

USING_NS_CC;

Wind *Wind::Create() {
    return Wind::create();
}

bool Wind::init() {
    if (!TMXTiledMap::initWithTMXFile(AppConsts::Wind::TMX)) {
        return false;
    }

    auto WorldOrigin = Director::getInstance()->getVisibleOrigin();
    auto WorldSize = Director::getInstance()->getVisibleSize();

    setAnchorPoint(AppConsts::Wind::INIT_ANCHOR_POINT);
    setPosition(Vec2(WorldOrigin.x + WorldSize.width * AppConsts::Wind::INIT_X_FACTOR,
                     WorldOrigin.y + WorldSize.height * AppConsts::Wind::INIT_Y_FACTOR));

    return true;
}

void Wind::CollidesToWorld() {

}

bool Wind::CollidesToNodes(std::vector<cocos2d::Node *> Nodes) {
    auto Handled = false;

    return Handled;
}
