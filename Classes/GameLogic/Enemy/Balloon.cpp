#include "Balloon.h"
#include "GameLogic/CollisionManager.h"
#include "GameLogic/GameObject/Wind.h"

USING_NS_CC;

Balloon *Balloon::Create() {
    return Balloon::create();
}

bool Balloon::init() {
    if (!Sprite::initWithFile(AppConsts::Balloon::TEXTURE)) {
        return false;
    }

    auto WorldOrigin = Director::getInstance()->getVisibleOrigin();
    auto WorldSize = Director::getInstance()->getVisibleSize();

    setAnchorPoint(AppConsts::Balloon::INIT_ANCHOR_POINT);
    setPosition(Vec2(WorldOrigin.x + WorldSize.width * AppConsts::Balloon::INIT_X_FACTOR,
                     WorldOrigin.y + WorldSize.height * AppConsts::Balloon::INIT_Y_FACTOR));
    SetVelocityFactor(AppConsts::Balloon::VELOCITY_FACTOR);

    return true;
}

void Balloon::update(float Delta) {
    if (!CanStartNewFly) {
        if (auto _CollisionManager = dynamic_cast<CollisionManager *>(getParent())) {
            // We correctly left collision, now can shift rotation
            bool NotCollidesToWorld = !_CollisionManager->IsCollidesToWorld(this);
            bool NotCollidesToNodes = true;

            for (auto Node : CollidedGameObjects) {
                NotCollidesToNodes = NotCollidesToNodes && !_CollisionManager->IsCollidesToNode(this, Node);
            }

            if (NotCollidesToWorld && NotCollidesToNodes) {
                CollidedGameObjects.clear();

                stopAction(getActionByTag(FlyTag));
                // Add a random shift within 40 degrees
                VirtualRotation += std::rand() % 40 - 20;

                CanStartNewFly = true;

                MoveToVirtualRotation();
            }
        }
    }
}

void Balloon::CollidesToWorld() {
    StartNewFly();
}

bool Balloon::CollidesToNodes(std::vector<cocos2d::Node *> Nodes) {
    auto Handled = Enemy::CollidesToNodes(Nodes);

    if (!Handled) {
        for (auto Node : Nodes) {
            if (dynamic_cast<Wind *>(Node) &&
                std::find(CollidedGameObjects.begin(), CollidedGameObjects.end(), Node) == CollidedGameObjects.end()) {
                CollidedGameObjects.push_back(Node);

                StartNewFly();

                Handled = true;
            } else if (dynamic_cast<Enemy *>(Node)) {
                //todo
            }
        }
    }

    return Handled;
}

void Balloon::OnSpawned() {
    // Start flying
    VirtualRotation = std::rand() % 360; // Random rotation

    CanStartNewFly = true;

    MoveToVirtualRotation();
}

void Balloon::MoveToVirtualRotation() {
    auto WorldSize = Director::getInstance()->getVisibleSize();
    auto Distance = std::max(WorldSize.width, WorldSize.height) * 2;
    auto Angle = CC_DEGREES_TO_RADIANS(VirtualRotation);
    auto TargetX = getPosition().x + sin(Angle) * Distance;
    auto TargetY = getPosition().y + cos(Angle) * Distance;
    auto Fly = MoveTo::create(GetVelocity(), Vec2(TargetX, TargetY));

    Fly->setTag(FlyTag);

    runAction(Fly);
}

void Balloon::StartNewFly() {
    // Before new fly started, need to check if balloon
    // not collides world, checking it in update()
    if (CanStartNewFly) {
        CanStartNewFly = false;

        stopAction(getActionByTag(FlyTag));

        // Inverse rotation
        VirtualRotation += 180;

        if (VirtualRotation >= 360) {
            VirtualRotation -= 360;
        }

        MoveToVirtualRotation();
    }
}
