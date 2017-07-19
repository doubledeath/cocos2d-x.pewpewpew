#include "World.h"
#include "AppConsts.h"
#include "Player/Cannon.h"
#include "Enemy/Balloon.h"
#include "GameObject/Wind.h"

USING_NS_CC;

World *World::Create() {
    return World::create();
}

bool World::init() {
    if (!Node::init()) {
        return false;
    }

    CreateEnvironment();
    CreatePhysics();
    AddGameObjects();
    AddEventDispatcher();
    SpawnCannon();
    SpawnEnemies();

    return true;
}

void World::CreateEnvironment() {
    auto Origin = Director::getInstance()->getVisibleOrigin();
    auto Size = Director::getInstance()->getVisibleSize();
    // Add a background
    auto Background = DrawNode::create();

    Background->drawSolidRect(Origin,
                              Vec2(Origin.x + Size.width, Origin.y + Size.height),
                              AppConsts::World::BACKGROUND_COLOR);

    addChild(Background);
}

void World::CreatePhysics() {
    Physics = Physics::Create();

    addChild(Physics);
}

void World::AddGameObjects() {
    // Add a wind
    auto Wind = Wind::Create();

    Physics->addChild(Wind);
}

void World::AddEventDispatcher() {
    // Create a "one by one" touch event listener
    // (processes one touch at a time)
    auto TouchListener = EventListenerTouchOneByOne::create();
    // trigger when you push down
    TouchListener->onTouchBegan = [=](Touch *Touch, Event *Event) {
        TouchOrClickEventDown(Touch, nullptr);

        return true;
    };
    // trigger when you let up
    TouchListener->onTouchEnded = [=](Touch *Touch, Event *Event) {
        TouchOrClickEventUp(Touch, nullptr);
    };
    // Create a mouse event listener
    auto MouseListener = EventListenerMouse::create();
    // trigger when you click down
    MouseListener->onMouseDown = [=](Event *Event) {
        TouchOrClickEventDown(nullptr, (EventMouse *) Event);
    };
    // trigger when you click up
    MouseListener->onMouseUp = [=](Event *Event) {
        TouchOrClickEventUp(nullptr, (EventMouse *) Event);
    };
    // Add listeners
    _eventDispatcher->addEventListenerWithSceneGraphPriority(TouchListener, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(MouseListener, this);
}

void World::SpawnCannon() {
    auto _Player = Cannon::Create();

    PlayerList.push_back(static_cast<Player *>(_Player));
    Physics->addChild(_Player);
}

void World::SpawnEnemies() {
    unsigned int Enemies = 5; // todo

    if (Enemies > 0) {
        schedule([=](float Delta) {
            auto _Enemy = Balloon::Create();

            Physics->addChild(_Enemy);

            _Enemy->OnSpawned();
        }, 1.0f / 2, Enemies - 1, 0, "SpawnEnemies"); // Little delay between spawns
    }
}

void World::TouchOrClickEventDown(cocos2d::Touch *Touch, cocos2d::EventMouse *EventMouse) {
    if (TouchOrClickInfo.EventStarted || (Touch == nullptr && EventMouse == nullptr)) {
        return;
    }

    auto CurrentTime = std::chrono::system_clock::now().time_since_epoch();

    TouchOrClickInfo.EventStartVec2 = Touch != nullptr ? Touch->getLocation() : EventMouse->getLocation();
    TouchOrClickInfo.EventStartMillis = std::chrono::duration_cast<std::chrono::milliseconds>(CurrentTime).count();
    TouchOrClickInfo.EventStarted = true;
}

void World::TouchOrClickEventUp(cocos2d::Touch *Touch, cocos2d::EventMouse *EventMouse) {
    if (TouchOrClickInfo.EventStarted && (Touch != nullptr || EventMouse != nullptr)) {
        Vec2 CurrentVec2 = Touch != nullptr ? Touch->getLocation() : EventMouse->getLocation();

        if (TouchOrClickInfo.EventStartVec2.distance(CurrentVec2) < AppConsts::World::TOUCH_OR_CLICK_DISTANCE) {
            auto CurrentTime = std::chrono::system_clock::now().time_since_epoch();
            long CurrentMillis = std::chrono::duration_cast<std::chrono::milliseconds>(CurrentTime).count();

            if (CurrentMillis - TouchOrClickInfo.EventStartMillis > AppConsts::World::LONG_TOUCH_OR_CLICK_TIME) {
                OnLongTouchOrClick(CurrentVec2);
            } else {
                OnTouchOrClick(CurrentVec2);

            }
        }

        TouchOrClickInfo.EventStarted = false;
    }
}

void World::OnTouchOrClick(cocos2d::Vec2 Location) {
    for (auto Player : PlayerList) {
        Player->OnWorldTouchOrClick(convertToNodeSpace(Location));
    }
}

void World::OnLongTouchOrClick(cocos2d::Vec2 Location) {
    for (auto Player : PlayerList) {
        Player->OnWorldLongTouchOrClick(convertToNodeSpace(Location));
    }
}
