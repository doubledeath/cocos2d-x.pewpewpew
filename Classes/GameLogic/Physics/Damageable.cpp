#include "Damageable.h"

void Damageable::applyDamage(int damage)
{
    setHitPoints(getHitPoints() - damage);

    if (getHitPoints() <= 0) { onDead(); }
    else { onDamaged(); }
}
