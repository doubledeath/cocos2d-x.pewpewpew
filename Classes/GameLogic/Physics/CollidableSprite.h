#pragma once

#include "cocos2d.h"
#include "ParentCollidable.h"

class CollidableSprite : public cocos2d::Sprite, public virtual ParentCollidable
{
public:
    CREATE_FUNC(CollidableSprite)

    virtual cocos2d::Rect getRect() const override;
};
