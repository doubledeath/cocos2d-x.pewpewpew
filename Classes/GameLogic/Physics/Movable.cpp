#include "Movable.h"

USING_NS_CC;

void Movable::onCollided()
{
    interruptMoveToRotation();
}

void Movable::onCollisionResolved()
{
    moveToRotation();
}

Vec2 Movable::getMoveChange()
{
    auto distance = getMoveDistance();
    auto angle = CC_DEGREES_TO_RADIANS(getMoveRotation());
    // sin on x and cos on y because coordinate system
    // rotated by 90 degrees
    auto x = sin(angle) * distance;
    auto y = cos(angle) * distance;

    return Vec2(x, y);
}
