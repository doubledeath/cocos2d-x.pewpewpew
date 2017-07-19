#include "Enemy.h"
#include "GameLogic/Projectile/Projectile.h"

USING_NS_CC;

bool Enemy::CollidesToNodes(std::vector<Node *> Nodes) {
    auto Handled = false;

    for (auto Node : Nodes) {
        if (auto _Projectile = dynamic_cast<Projectile *>(Node)) {
            SetHitPoints(GetHitPoints() - _Projectile->GetDamage());

            if (GetHitPoints() <= 0) {
                SetCollisionForceIgnored(true);

                runAction(RemoveSelf::create(true));

                Handled = true;
            }
        }
    }

    return Handled;
}

float Enemy::GetVelocity() {
    return Velocity / VelocityFactor;
}

float Enemy::GetVelocityFactor() {
    return VelocityFactor;
}

float Enemy::GetHitPoints() {
    return HitPoints;
}

void Enemy::SetVelocityFactor(float VelocityFactor) {
    this->VelocityFactor = VelocityFactor;
}

void Enemy::SetVelocity(float Velocity) {
    this->Velocity = Velocity;
}

void Enemy::SetHitPoints(float HitPoints) {
    this->HitPoints = HitPoints;
}
