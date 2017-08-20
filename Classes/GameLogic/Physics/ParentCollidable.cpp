#include "ParentCollidable.h"

USING_NS_CC;

int ParentCollidable::getType() const
{
    return mType;
}

int ParentCollidable::getTypeMask() const
{
    return mTypeMask;
}

void ParentCollidable::onCollided()
{
}

void ParentCollidable::onCollisionResolved()
{
}

void ParentCollidable::setType(int type)
{
    mType = type;
}

void ParentCollidable::setTypeMask(int typeMask)
{
    mTypeMask = typeMask;
}
