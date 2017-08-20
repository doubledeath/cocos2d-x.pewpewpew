#pragma once

#include "cocos2d.h"
#include "ParentCollidable.h"

class CollidableNode : public cocos2d::Node, public virtual ParentCollidable
{
public:
    CREATE_FUNC(CollidableNode)

    virtual cocos2d::Rect getRect() const override;
};
