#include "Collidable.h"

bool Collidable::IsCollisionForceIgnored() {
    return CollisionForceIgnored;
}

void Collidable::SetCollisionForceIgnored(bool CollisionForceIgnored) {
    this->CollisionForceIgnored = CollisionForceIgnored;
}
