#include "CollidableNode.h"

USING_NS_CC;

Rect CollidableNode::getRect() const
{
    return getBoundingBox();
}
