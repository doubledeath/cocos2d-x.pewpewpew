#include "Projectile.h"

USING_NS_CC;

void Projectile::CollidesToWorld() {
    SetCollisionForceIgnored(true);

    stopAllActionsByTag(GetShootTag());

    runAction(RemoveSelf::create(true));
}

void Projectile::CollidesToNodes(std::vector<cocos2d::Node *> Nodes) {

}

int Projectile::GetShootTag() {
    return ShootTag;
}

float Projectile::GetDistance() {
    return Distance;
}

float Projectile::GetVelocityFactor() {
    return VelocityFactor;
}

float Projectile::GetVelocity() {
    return Velocity * VelocityFactor;
}

void Projectile::SetVelocityFactor(float VelocityFactor) {
    this->VelocityFactor = VelocityFactor;
}

void Projectile::SetShootTag(int ShootTag) {
    this->ShootTag = ShootTag;
}

void Projectile::SetDistance(float Distance) {
    this->Distance = Distance;
}

void Projectile::SetVelocity(float Velocity) {
    this->Velocity = Velocity;
}
