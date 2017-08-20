#include "Balloon.h"

USING_NS_CC;

bool Balloon::init()
{
    if (!Enemy::initWithFile(EnemyConsts::Balloon::TEXTURE))
    {
        return false;
    }

    return true;
}
