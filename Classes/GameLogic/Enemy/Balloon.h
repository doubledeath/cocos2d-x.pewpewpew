#pragma once

#include "Enemy.h"

class Balloon : public Enemy {
public:
    static Balloon *Create();

    virtual bool init();

    virtual void update(float Delta);

    CREATE_FUNC(Balloon);

    virtual void CollidesToWorld();

    virtual bool CollidesToNodes(std::vector<cocos2d::Node *> Nodes);

    virtual void OnSpawned();

private:
    int FlyTag = AppConsts::Balloon::FLY_TAG;
    // No need to rotate sprite, but need to use rotation while move
    float VirtualRotation;
    bool CanStartNewFly;
    // They are static and always exists in the world,
    // we can easy hold it without memory leak
    std::vector<cocos2d::Node *> CollidedGameObjects;

    void MoveToVirtualRotation();

    void StartNewFly();
};
