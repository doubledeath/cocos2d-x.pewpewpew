#pragma once

#include "Collidable.h"

class Damageable : public virtual Collidable
{
public:
    virtual int getHitPoints() const = 0;
    virtual void applyDamage(int damage);
protected:
    virtual void setHitPoints(int hitPoints) = 0;
    virtual void onDamaged() = 0;
    virtual void onDead() = 0;
};
