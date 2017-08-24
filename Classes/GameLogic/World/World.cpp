#include "World.h"
#include "WorldConsts.h"
#include "GameLogic/Player/Cannon.h"
#include "GameLogic/Enemy/Balloon.h"
#include "GameLogic/Physics/CollidableNode.h"
#include "GameLogic/Physics/CollidableType.h"
#include "GameLogic/Physics/CollidableTypeMask.h"
#include "Support/Config.h"

USING_NS_CC;

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
    addEventDispatcher();
    startGame();

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
    if (mPlayer) { mPlayer->onWorldSingleTouchOrClick(convertToNodeSpace(location)); }
}

void World::onDoubleTouchOrClick(Vec2 location)
{
    if (mPlayer) { mPlayer->onWorldDoubleTouchOrClick(convertToNodeSpace(location)); }
}

void World::onLongTouchOrClick(Vec2 location)
{
    if (mPlayer) { mPlayer->onWorldLongTouchOrClick(convertToNodeSpace(location)); }
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
    // Label for time
    auto timerLabelX = origin.x + size.width * WorldConsts::Enviorment::TIMER_LABEL_X_FACTOR;
    auto timerLabelY = origin.y + size.height * WorldConsts::Enviorment::TIMER_LABEL_Y_FACTOR;
    auto timerLabelWidth = size.width * WorldConsts::Enviorment::TIMER_LABEL_WIDTH_FACTOR;

    mTimerLabel = Label::createWithTTF("",
                                       WorldConsts::Enviorment::TIMER_LABEL_FONT,
                                       WorldConsts::Enviorment::TIMER_LABEL_FONT_SIZE,
                                       Size(timerLabelWidth, 0), TextHAlignment::CENTER);

    mTimerLabel->setPosition(timerLabelX, timerLabelY);

    addChild(mTimerLabel);

}

void World::createGameOverMenu()
{
    auto origin = Director::getInstance()->getVisibleOrigin();
    auto size = Director::getInstance()->getVisibleSize();
    auto menuItem = MenuItemFont::create("Restart", [=](Ref* pSender) { startGame(); });
    auto menuItemX = origin.x + size.width * WorldConsts::GameOverMenu::RESTART_BUTTON_X_FACTOR;
    auto menuItemY = origin.y + size.height * WorldConsts::GameOverMenu::RESTART_BUTTON_Y_FACTOR;

    menuItem->setPosition(menuItemX, menuItemY);

    auto menuItemBackground = DrawNode::create();

    menuItemBackground->setLocalZOrder(WorldConsts::GameOverMenu::BACKGROUND_Z_ORDER);
    menuItemBackground->drawSolidRect(origin, Vec2(size.width, size.height), WorldConsts::GameOverMenu::BACKGROUND_COLOR);

    auto gameOverMenu = Menu::createWithItem(menuItem);

    gameOverMenu->setLocalZOrder(WorldConsts::GameOverMenu::Z_ORDER);
    gameOverMenu->setPosition(origin);
    gameOverMenu->setContentSize(size);

    mGameOverMenu = Node::create();

    mGameOverMenu->addChild(menuItemBackground);
    mGameOverMenu->addChild(gameOverMenu);

    addChild(mGameOverMenu);
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
    auto count = Config::getInstance().getCountTarget();
    auto repeat = count - 1;

    if (count > 0)
    {
        schedule([=](float delta) { spawnBalloon(); }, WorldConsts::Enemy::SPAWN_INTERVAL, repeat, WorldConsts::Enemy::SPAWN_DELAY, WorldConsts::Enemy::SPAWN_KEY);
    }
}

void World::cleanWorld()
{
    if (mPlayer) { mPlayer->runAction(RemoveSelf::create(true)); mPlayer = nullptr; }

    for (auto child : getChildren())
    {
        if (dynamic_cast<Enemy *>(child)) { child->runAction(RemoveSelf::create(true)); }
    }
}

void World::startGame()
{
    if (mGameOverMenu) { mGameOverMenu->runAction(RemoveSelf::create(true)); mGameOverMenu = nullptr; }

    cleanWorld();
    spawnPlayer();

    mTimerLabel->setString("Spawning enemies...");

    spawnEnemies();
    // Wait for enemies are spawned...
    auto delay = WorldConsts::Enemy::SPAWN_DELAY + WorldConsts::Enemy::SPAWN_INTERVAL * Config::getInstance().getCountTarget();

    scheduleOnce([=](float delta) { if (mPlayer) { mPlayer->onGameStarted(); } startTimer(); }, delay, WorldConsts::Player::ON_GAME_STARTED);
}

void World::startTimer()
{
    mTimeRemaining = Config::getInstance().getTime();

    mTimerLabel->setString("Pew pew pew them!");
    // Scheduling every second
    schedule([=](float delta) {
        auto remainingEnemy = getRemainingEnemy();

        if (remainingEnemy == 0)
        {
            endGame();
        }
        else
        {
            mTimeRemaining--;

            mTimerLabel->setString(std::to_string(mTimeRemaining));

            if (mTimeRemaining <= 0) { endGame(); }
        }
    }, 1, WorldConsts::World::TIMER_KEY);
}

void World::endGame()
{
    auto remainingEnemy = getRemainingEnemy();

    auto wasKilled = Config::getInstance().getCountTarget() - remainingEnemy;

    if (wasKilled == Config::getInstance().getCountTarget())
    {
        mTimerLabel->setString("Congratulations!");
    }
    else
    {
        mTimerLabel->setString("Game over! You tried hard, and killed: " + std::to_string(wasKilled) + " ones!");
    }

    unschedule(WorldConsts::World::TIMER_KEY);

    mPlayer->onGameOver();

    createGameOverMenu();
}

int World::getRemainingEnemy()
{
    auto remainingEnemy = 0;

    for (auto child : getChildren())
    {
        if (dynamic_cast<Enemy *>(child)) { remainingEnemy++; }
    }

    return remainingEnemy;
}
