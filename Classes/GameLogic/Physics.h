#pragma once

#include "cocos2d.h"
#include "Collidable.h"
#include "CollisionManager.h"

class Physics : public cocos2d::Node, public CollisionManager {
public:
    static Physics *Create();

    virtual bool init();

    virtual void update(float Delta);

    virtual void addChild(cocos2d::Node *Child);

    virtual void removeChild(cocos2d::Node *Child, bool CleanUp);

    CREATE_FUNC(Physics);

    virtual bool IsCollidesToWorld(cocos2d::Node *Node);

    virtual bool IsCollidesToNode(cocos2d::Node *Node, cocos2d::Node *Target);

private:
    std::vector<Collidable *> CollidableChildren;

    bool IsCollidesWorld(cocos2d::Node *Target);

    std::vector<cocos2d::Node *> GetCollidedNodes(cocos2d::Node *Target);
};
