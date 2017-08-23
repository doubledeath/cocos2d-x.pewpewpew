#pragma once

#include "cocos2d.h"
#include "GameLogic/Physics/Physics.h"
#include "GameLogic/Player/Player.h"
#include "Support/Config.h"

class World : public cocos2d::Node
{
public:
    static World *create(Config *config);

    World(Config *config);

    virtual bool init() override;
    virtual void update(float delta) override;
    virtual void removeChild(cocos2d::Node *child, bool cleanup) override;
private:
    struct TouchOrClickInfo {
        bool eventStarted;
        long eventStartMillis;
        cocos2d::Vec2 eventStartLocation;
    };

    Config *mConfig;
    TouchOrClickInfo mTouchOrClickInfo;
    TouchOrClickInfo mLastTouchOrClickInfo;
    Physics *mPhysics;
    Collidable *mEnemyZone;
    Player *mPlayer;

    void touchOrClickEventDown(cocos2d::Touch *touch, cocos2d::EventMouse *eventMouse);
    void touchOrClickEventUp(cocos2d::Touch *touch, cocos2d::EventMouse *eventMouse);
    void onSingleTouchOrClick(cocos2d::Vec2 location);
    void onDoubleTouchOrClick(cocos2d::Vec2 location);
    void onLongTouchOrClick(cocos2d::Vec2 location);
    void addEventDispatcher();
    void createPhysics();
    void createEnvoirment();
    void loadConfig();
    void spawnPlayer();
    void spawnBalloon();
    void spawnEnemies();
};
