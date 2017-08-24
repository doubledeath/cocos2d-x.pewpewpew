#pragma once

#include "cocos2d.h"
#include "GameLogic/Physics/Physics.h"
#include "GameLogic/Player/Player.h"

class World : public cocos2d::Node
{
public:
    CREATE_FUNC(World)

    virtual bool init() override;
    virtual void update(float delta) override;
    virtual void removeChild(cocos2d::Node *child, bool cleanup) override;
private:
    struct TouchOrClickInfo {
        bool eventStarted;
        long eventStartMillis;
        cocos2d::Vec2 eventStartLocation;
    };

    TouchOrClickInfo mTouchOrClickInfo;
    TouchOrClickInfo mLastTouchOrClickInfo;
    Physics *mPhysics;
    Collidable *mEnemyZone;
    Player *mPlayer;
    int mTimeRemaining;
    cocos2d::Label *mTimerLabel;
    cocos2d::Node *mGameOverMenu;

    void touchOrClickEventDown(cocos2d::Touch *touch, cocos2d::EventMouse *eventMouse);
    void touchOrClickEventUp(cocos2d::Touch *touch, cocos2d::EventMouse *eventMouse);
    void onSingleTouchOrClick(cocos2d::Vec2 location);
    void onDoubleTouchOrClick(cocos2d::Vec2 location);
    void onLongTouchOrClick(cocos2d::Vec2 location);
    void addEventDispatcher();
    void createPhysics();
    void createEnvoirment();
    void createGameOverMenu();
    void spawnPlayer();
    void spawnBalloon();
    void spawnEnemies();
    void cleanWorld();
    void startGame();
    void startTimer();
    void endGame();
    int getRemainingEnemy();
};
