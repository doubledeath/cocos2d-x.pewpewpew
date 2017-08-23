#include "World.h"
#include "WorldConsts.h"
#include "GameLogic/Player/Cannon.h"
#include "GameLogic/Enemy/Balloon.h"
#include "GameLogic/Physics/CollidableNode.h"
#include "GameLogic/Physics/CollidableType.h"
#include "GameLogic/Physics/CollidableTypeMask.h"

USING_NS_CC;

World *World::create(Config *config)
{
    World *pRet = new(std::nothrow) World(config);

    if (pRet && pRet->init())
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        delete pRet;
        pRet = nullptr;
        return nullptr;
    }
}

World::World(Config *config)
{
    mConfig = config;
}

bool World::init()
{
    if (!Node::init())
    {
        return false;
    }

    auto origin = Director::getInstance()->getVisibleOrigin();

    setPosition(origin.x, origin.y);
    setContentSize(Director::getInstance()->getVisibleSize());
    // Prevent first touch or click seems as double one
    mLastTouchOrClickInfo.eventStartMillis = WorldConsts::World::DOUBLE_TOUCH_OR_CLICK_TIME * 2;

    createPhysics();
    createEnvoirment();
    spawnPlayer();
    addEventDispatcher();
    spawnEnemies();

    return true;
}

void World::update(float delta)
{
    mPhysics->update(delta);
}

void World::removeChild(Node *child, bool cleanup)
{
    if (auto collidable = dynamic_cast<Collidable *>(child)) { mPhysics->removeCollidable(collidable); }

    Node::removeChild(child, cleanup);
}

void World::touchOrClickEventDown(Touch *touch, EventMouse *eventMouse)
{
    if (mTouchOrClickInfo.eventStarted || (touch == nullptr && eventMouse == nullptr)) { return;}

    auto currentTime = std::chrono::system_clock::now().time_since_epoch();

    mTouchOrClickInfo.eventStartLocation = touch != nullptr ? touch->getLocation() : eventMouse->getLocation();
    mTouchOrClickInfo.eventStartMillis = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime).count();
    mTouchOrClickInfo.eventStarted = true;
}

void World::touchOrClickEventUp(Touch *touch, EventMouse *eventMouse)
{
    if (mTouchOrClickInfo.eventStarted && (touch != nullptr || eventMouse != nullptr))
    {
        auto currentLocation = touch != nullptr ? touch->getLocation() : eventMouse->getLocation();

        if (mTouchOrClickInfo.eventStartLocation.distance(currentLocation) < WorldConsts::World::SINGLE_TOUCH_OR_CLICK_DISTANCE)
        {
            auto currentTime = std::chrono::system_clock::now().time_since_epoch();
            long currentMillis = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime).count();
            auto currentDiff = currentMillis - mTouchOrClickInfo.eventStartMillis;

            if (currentDiff > WorldConsts::World::LONG_TOUCH_OR_CLICK_TIME)
            {
                onLongTouchOrClick(currentLocation);
            }
            else
            {
                auto lastDiff = mTouchOrClickInfo.eventStartMillis - mLastTouchOrClickInfo.eventStartMillis;

                if (lastDiff < WorldConsts::World::DOUBLE_TOUCH_OR_CLICK_TIME)
                {
                    unschedule(WorldConsts::World::SINGLE_TOUCH_OR_CLICK_KEY);

                    onDoubleTouchOrClick(currentLocation);
                }
                else
                {
                    unschedule(WorldConsts::World::SINGLE_TOUCH_OR_CLICK_KEY);
                    scheduleOnce([=](float delta) { onSingleTouchOrClick(currentLocation); },
                        WorldConsts::World::DOUBLE_TOUCH_OR_CLICK_TIME / 1000, // Convert to seconds
                        WorldConsts::World::SINGLE_TOUCH_OR_CLICK_KEY);
                }
            }

            mLastTouchOrClickInfo.eventStartMillis = mTouchOrClickInfo.eventStartMillis;
        }

        mTouchOrClickInfo.eventStarted = false;
    }
}

void World::onSingleTouchOrClick(Vec2 location)
{
    mPlayer->onWorldSingleTouchOrClick(convertToNodeSpace(location));
}

void World::onDoubleTouchOrClick(Vec2 location)
{
    mPlayer->onWorldDoubleTouchOrClick(convertToNodeSpace(location));
}

void World::onLongTouchOrClick(Vec2 location)
{
    mPlayer->onWorldLongTouchOrClick(convertToNodeSpace(location));
}

void World::addEventDispatcher()
{
    // Create a "one by one" touch event listener
    // (processes one touch at a time)
    auto touchListener = EventListenerTouchOneByOne::create();
    // trigger when you push down
    touchListener->onTouchBegan = [=](Touch *touch, Event *event) { touchOrClickEventDown(touch, nullptr); return true; };
    // trigger when you let up
    touchListener->onTouchEnded = [=](Touch *touch, Event *event) { touchOrClickEventUp(touch, nullptr); };
    // Create a mouse event listener
    auto mouseListener = EventListenerMouse::create();
    // trigger when you click down
    mouseListener->onMouseDown = [=](Event *event) { touchOrClickEventDown(nullptr, dynamic_cast<EventMouse *>(event)); };
    // trigger when you click up
    mouseListener->onMouseUp = [=](Event *event) { touchOrClickEventUp(nullptr, dynamic_cast<EventMouse *>(event)); };
    // Add listeners
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);
}

void World::createPhysics()
{
    mPhysics = new Physics();

    scheduleUpdate(); // Enable calling update method
}

void World::createEnvoirment()
{
    auto origin = Director::getInstance()->getVisibleOrigin();
    auto size = Director::getInstance()->getVisibleSize();
    auto worldZone = CollidableNode::create();
    auto enemyZone = CollidableNode::create();
    auto enemyZoneX = origin.x;
    auto enemyZoneY = origin.y + size.height * WorldConsts::Enemy::ZONE_BOTTOM_FACTOR;
    auto enemyZoneWidth = size.width * WorldConsts::Enemy::ZONE_WIDTH_FACTOR;
    auto enemyZoneHeight = size.height * (1 - WorldConsts::Enemy::ZONE_BOTTOM_FACTOR);

    worldZone->setType(static_cast<int>(CollidableType::container));
    worldZone->setTypeMask(static_cast<int>(CollidableTypeMask::container));
    worldZone->setPosition(origin);
    worldZone->setContentSize(size);

    addChild(worldZone);
    mPhysics->addCollidable(worldZone);

    enemyZone->setType(static_cast<int>(CollidableType::container));
    enemyZone->setTypeMask(static_cast<int>(CollidableTypeMask::container));
    enemyZone->setPosition(enemyZoneX, enemyZoneY);
    enemyZone->setContentSize(Size(enemyZoneWidth, enemyZoneHeight));

    mEnemyZone = enemyZone;

    addChild(enemyZone);
    mPhysics->addCollidable(enemyZone);

    auto grassAndSky = TMXTiledMap::create(WorldConsts::Enviorment::GRASS_AND_SKY_TMX);

    grassAndSky->setScale(WorldConsts::Enviorment::GRASS_AND_SKY_SCALE);

    auto grassAndSkyX = origin.x - grassAndSky->getBoundingBox().size.width * WorldConsts::Enviorment::GRASS_AND_SKY_LEFT_FACTOR;
    auto grassAndSkyY = origin.y - size.height * (1 - WorldConsts::Enviorment::GRASS_AND_SKY_BOTTOM_FACTOR);

    grassAndSky->setPosition(grassAndSkyX, grassAndSkyY);

    addChild(grassAndSky);
}

void World::loadConfig()
{

}

void World::spawnPlayer()
{
    auto origin = Director::getInstance()->getVisibleOrigin();
    auto size = Director::getInstance()->getVisibleSize();
    auto cannon = Cannon::create();
    auto cannonX = origin.x + size.width * WorldConsts::Player::SPAWN_X_FACTOR;
    auto cannonY = origin.y + size.height * WorldConsts::Player::SPAWN_Y_FACTOR;

    cannon->setPosition(cannonX, cannonY);
    cannon->setGetCannonBallPierceableListDelegate([=]()
    {
        std::vector<Collidable *> cannonBallPierceableList;

        cannonBallPierceableList.push_back(mEnemyZone);

        return cannonBallPierceableList;
    });
    cannon->setAddToWorldDelegate([=](CannonBall *cannonBall)
    {
        addChild(cannonBall);
        mPhysics->addCollidable(cannonBall);
    });
    cannon->setParticleApplierDelegate([=](ParticleSystem *particle) { addChild(particle); });

    addChild(mPlayer = cannon);
}

void World::spawnBalloon()
{
    auto origin = Director::getInstance()->getVisibleOrigin();
    auto size = Director::getInstance()->getVisibleSize();
    auto balloon = Balloon::create();
    auto balloonX = origin.x + size.width * WorldConsts::Enemy::SPAWN_X_FACTOR;
    auto balloonY = origin.y + size.height * WorldConsts::Enemy::SPAWN_Y_FACTOR;

    balloon->setPosition(balloonX, balloonY);

    addChild(balloon);
    mPhysics->addCollidable(balloon);

    balloon->onSpawned([=](ParticleSystem *particle) { addChild(particle); });
}

void World::spawnEnemies()
{
    auto count = mConfig ? mConfig->getCountTarget() : WorldConsts::Enemy::SPAWN_COUNT;
    auto repeat = count - 1;

    if (count > 0)
    {
        schedule([=](float delta) { spawnBalloon(); }, WorldConsts::Enemy::SPAWN_INTERVAL, repeat, WorldConsts::Enemy::SPAWN_DELAY, WorldConsts::Enemy::SPAWN_KEY);
    }
}
