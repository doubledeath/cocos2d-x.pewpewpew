#include "CollidableSprite.h"

USING_NS_CC;

Rect CollidableSprite::getRect() const
{
    return getBoundingBox();
}
