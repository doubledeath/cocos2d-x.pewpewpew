#include "MRSprite.h"
#include "PhysicsConsts.h"

USING_NS_CC;

void MRSprite::resolve(Vec2 resolveChange, int resolveVelocity, CallFunc *onResolved)
{
    auto resolve = MoveBy::create(getMoveDuration(resolveVelocity), resolveChange);
    auto resolveAndNotify = Sequence::create(resolve, onResolved, nullptr);

    resolveAndNotify->setTag(PhysicsConsts::MovableSprite::RESOLVE_TAG);

    runAction(resolveAndNotify);
}

void MRSprite::interruptResolving()
{
    stopActionByTag(PhysicsConsts::MovableSprite::RESOLVE_TAG);
}
