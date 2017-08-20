#include "CannonBall.h"
#include "ProjectileConsts.h"

USING_NS_CC;

bool CannonBall::init()
{
    if (!Sprite::initWithFile(ProjectileConsts::CannonBall::TEXTURE))
    {
        return false;
    }

    return true;
}
