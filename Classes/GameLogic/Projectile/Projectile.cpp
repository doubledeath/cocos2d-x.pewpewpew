#include "Projectile.h"
#include "GameLogic/Enemy/Enemy.h"

USING_NS_CC;

void Projectile::CollidesToWorld() {
    SetCollisionForceIgnored(true);

    stopAllActionsByTag(GetShootTag());

    runAction(RemoveSelf::create(true));
}

bool Projectile::CollidesToNodes(std::vector<Node *> Nodes) {
    auto Handled = false;

    for (auto Node : Nodes) {
        if (dynamic_cast<Enemy *>(Node)) {
            SetCollisionForceIgnored(true);

            stopAllActionsByTag(GetShootTag());

            runAction(RemoveSelf::create(true));

            Handled = true;
        }
    }

    return Handled;
}

int Projectile::GetShootTag() {
    return ShootTag;
}

float Projectile::GetVelocity() {
    return Velocity / VelocityFactor;
}

float Projectile::GetVelocityFactor() {
    return VelocityFactor;
}

float Projectile::GetDistance() {
    return Distance;
}

float Projectile::GetDamage() {
    return Damage / DamageFactor;
}

void Projectile::SetVelocityFactor(float VelocityFactor) {
    this->VelocityFactor = VelocityFactor;
}

void Projectile::SetDamageFactor(float DamageFactor) {
    this->DamageFactor = DamageFactor;
}

void Projectile::SetShootTag(int ShootTag) {
    this->ShootTag = ShootTag;
}

void Projectile::SetVelocity(float Velocity) {
    this->Velocity = Velocity;
}

void Projectile::SetDistance(float Distance) {
    this->Distance = Distance;
}

void Projectile::SetDamage(float Damage) {
    this->Velocity = Velocity;
}
