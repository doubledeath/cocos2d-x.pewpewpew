#pragma once

#include "cocos2d.h"
#include "Physics.h"
#include "Player/Player.h"

class World : public cocos2d::Node {
public:
    static World *Create();

    virtual bool init();

    CREATE_FUNC(World);
private:
    struct TouchOrClickInfo {
        bool EventStarted;
        long EventStartMillis;
        cocos2d::Vec2 EventStartVec2;
    };

    class Physics *Physics;

    std::vector<Player *> PlayerList;
    TouchOrClickInfo TouchOrClickInfo;

    void CreateEnvironment();

    void CreatePhysics();

    void AddGameObjects();

    void AddEventDispatcher();

    void SpawnCannon();

    void SpawnEnemies();

    void TouchOrClickEventDown(cocos2d::Touch *Touch, cocos2d::EventMouse *EventMouse);

    void TouchOrClickEventUp(cocos2d::Touch *Touch, cocos2d::EventMouse *EventMouse);

    void OnTouchOrClick(cocos2d::Vec2 Location);

    void OnLongTouchOrClick(cocos2d::Vec2 Location);
};
