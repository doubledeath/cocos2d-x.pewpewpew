#include "Physics.h"
#include "PhysicsConsts.h"
#include "CollidableType.h"

USING_NS_CC;

void Physics::update(float delta)
{
    // A simple tunneling effect implementation
    for (auto collidable : mCollidableList)
    {
        // Prepare data
        // Rect just now
        auto collidableRect = collidable->getRect();
        // Rect in past, it was at last update
        auto collidablePastRect = mPastRectMap[collidable];
        // Rect of collidable traveled path, let's name it tunnel
        auto collidableTunnelRect = computeTunnelRect(collidableRect, collidablePastRect);
        // Compute collisions
        auto collided = searchCollided(collidable, collidableRect);
        auto tunnelCollided = searchCollided(collidable, collidableTunnelRect);
        auto postCollided = mPostResolvingMap.find(collidable);
        // Different collision actuality sign for collidables which already
        // resolving collisions now and new ones
        if (mResolvingMap.find(collidable) != mResolvingMap.end() && postCollided == mPostResolvingMap.end())
        {
            // Collisions are resolved
            if (!collided)
            {
                mResolvingMap.erase(collidable);
                mOnCollidedMap.erase(collidable);
                mOnCollisionResolvedMap[collidable] = false;
            }
        }
        // If colldable have any collisions
        else if (collided || tunnelCollided || postCollided != mPostResolvingMap.end())
        {
            // First priority actuallity - post collided, that collision needed to
            // resolve first of all, then tunnel and after just now collision
            auto actuallyCollided = postCollided != mPostResolvingMap.end() ?
                        postCollided->second : (tunnelCollided ? tunnelCollided : collided);

            mResolvingMap[collidable] = actuallyCollided;
            mOnCollidedMap[collidable] = false;
            mOnCollisionResolvedMap.erase(collidable);
            mPostResolvingMap.erase(collidable);
        }
    }
    // Notify and resolve
    for (auto &&onCollidedPair : mOnCollidedMap)
    {
        // If yet was not notified, mark as notified in next cycle
        if (!onCollidedPair.second)
        {
            // Notify
            onCollidedPair.first->onCollided();
        }
    }
    // Resolving collisions if possible
    for (auto resolvingPair : mResolvingMap)
    {
        // If not notified, then not started to resolve
        if (!mOnCollidedMap[resolvingPair.first])
        {
            mOnCollidedMap[resolvingPair.first] = true;
            // Now only for movable we can resolve collision
            if (auto movable = dynamic_cast<Movable *>(resolvingPair.first)) { resolveCollision(movable, resolvingPair.second); }
        }
    }
    for (auto &&onCollisionResolvedPair : mOnCollisionResolvedMap)
    {
        // If yet was not notified
        if (!onCollisionResolvedPair.second)
        {
            onCollisionResolvedPair.second = true;
            // Notify
            onCollisionResolvedPair.first->onCollisionResolved();
        }
    }
    // Update collidable past rect map
    for (auto target : mCollidableList)
    {
        mPastRectMap[target] = target->getRect();
    }
}

void Physics::addCollidable(Collidable *collidable)
{
    if (collidable)
    {
        mCollidableList.push_back(collidable);
        mPastRectMap[collidable] = collidable->getRect();
    }
}

void Physics::removeCollidable(Collidable *collidable)
{
    if (collidable)
    {
        mCollidableList.erase(std::remove(mCollidableList.begin(), mCollidableList.end(), collidable), mCollidableList.end());
        mPastRectMap.erase(collidable);
        mResolvingMap.erase(collidable);
        mPostResolvingMap.erase(collidable);
        mOnCollidedMap.erase(collidable);
        mOnCollisionResolvedMap.erase(collidable);
    }
}

Collidable *Physics::searchCollided(Collidable *collidable, Rect rect)
{
    Collidable *found = nullptr;
    float foundDistance;

    std::vector<Collidable *> targetList;

    // Remove itself from list
    for (auto target : mCollidableList)
    {
        if (collidable != target) { targetList.push_back(target); }
    }

    auto collidedList = searchCollidedList(collidable, rect, targetList);
    // We search first of all closest container,
    // if there is no containers, closest non-container
    // Container pass
    for (auto collided : collidedList)
    {
        auto collidedRect = collided->getRect();
        auto isCollidedContainer = collided->getType() == static_cast<int>(CollidableType::container);

        if (isCollidedContainer)
        {
            auto leftDistance = std::abs(rect.getMinX() - collidedRect.getMaxX());
            auto rightDistance = std::abs(rect.getMaxX() - collidedRect.getMinX());
            auto topDistance = std::abs(rect.getMaxY() - collidedRect.getMinY());
            auto bottomDistance = std::abs(rect.getMinY() - collidedRect.getMaxY());

            auto minVerticalDistance = std::min(topDistance, bottomDistance);
            auto minHorizontalDistance = std::min(leftDistance, rightDistance);
            auto minDistance = std::min(minVerticalDistance, minHorizontalDistance);
            // If distance is closer
            if (!found || minDistance < foundDistance)
            {
                found = collided;
                foundDistance = minDistance;
            }
        }
    }
    // Non-container pass, if not found on prev pass
    if (!found)
    {
        for (auto collided : collidedList)
        {
            auto collidedRect = collided->getRect();

            auto leftDistance = std::abs(rect.getMinX() - collidedRect.getMaxX());
            auto rightDistance = std::abs(rect.getMaxX() - collidedRect.getMinX());
            auto topDistance = std::abs(rect.getMaxY() - collidedRect.getMinY());
            auto bottomDistance = std::abs(rect.getMinY() - collidedRect.getMaxY());

            auto minVerticalDistance = std::min(topDistance, bottomDistance);
            auto minHorizontalDistance = std::min(leftDistance, rightDistance);
            auto minDistance = std::min(minVerticalDistance, minHorizontalDistance);
            // If distance is closer
            if (!found || minDistance < foundDistance)
            {
                found = collided;
                foundDistance = minDistance;
            }
        }
    }

    return found;
}

std::vector<Collidable *> Physics::searchCollidedList(Collidable *collidable, Rect rect, std::vector<Collidable *> targetList)
{
    std::vector<Collidable *> collidedList;

    auto isContainer = collidable->getType() == static_cast<int>(CollidableType::container);

    for (auto target : targetList)
    {
        // Can't collide with this type
        if ((collidable->getTypeMask() & target->getType()) == 0) { continue; }
        // If projectile pierce target
        if (auto projectile = dynamic_cast<Projectile *>(collidable))
        {
            auto pierceableList = projectile->getPierceableList();

            if (std::find(pierceableList.begin(), pierceableList.end(), target) != pierceableList.end()) { continue; }
        }

        auto isCollided = false;
        auto isTargetContainer = target->getType() == static_cast<int>(CollidableType::container);
        auto isOnlyOneContainer = isContainer ^ isTargetContainer;
        auto targetRect = target->getRect();
        // Special handling one container and other is not
        if (isOnlyOneContainer)
        {
            // Detect which one is container
            auto containerRect = isContainer ? rect : targetRect;
            auto nonContainerRect = isTargetContainer ? rect : targetRect;
            // If container smaller then non-container, they have to use default handling
            if (nonContainerRect.size.width >= containerRect.size.width || nonContainerRect.size.height >= containerRect.size.height)
            {
                isOnlyOneContainer = false;
            }
            else
            {
                // If some side is out of container, there is collision
                isCollided = nonContainerRect.getMaxX() >= containerRect.getMaxX() ||
                        nonContainerRect.getMinX() <= containerRect.getMinX() ||
                        nonContainerRect.getMaxY() >= containerRect.getMaxY() ||
                        nonContainerRect.getMinY() <= containerRect.getMinY();
            }
        }
        // Default handling, using built-in intersect algorithm
        if (!isOnlyOneContainer) { isCollided = rect.intersectsRect(targetRect); }
        if (isCollided) { collidedList.push_back(target); }
    }

    return collidedList;
}

Rect Physics::computeTunnelRect(Rect collidableRect, Rect collidablePastRect)
{
    // Not the best, but simple solution
    return collidableRect.unionWithRect(collidablePastRect);
}

void Physics::resolveCollision(Movable *movable, Collidable *collided)
{
    static const float floatComparsionError = 0.000001f;
    static const float resolveChangeError = 2;
    static const float orientationDifferenceError = 2;

    auto damageable = dynamic_cast<Damageable *>(movable);
    auto projectile = dynamic_cast<Projectile *>(collided);
    // If projectile dealing damage, no need to interrupt movable or resolve collision, just resolve damage
    if (damageable && projectile) { resolveDamage(damageable, projectile); return; }
    // If moving, interrupt it, probably it's prev collision resolving action
    movable->interruptMoveBy();

    float resolveChangeX = 0, resolveChangeY = 0;
    //---Compute resolve change
    auto isMovableContainer = movable->getType() == static_cast<int>(CollidableType::container);
    auto isCollidedContainer = collided->getType() == static_cast<int>(CollidableType::container);
    auto isOnlyOneContainer = isMovableContainer ^ isCollidedContainer;
    auto movableRect = movable->getRect();
    auto collidedRect = collided->getRect();
    // Special handling one container and other is not
    if (isOnlyOneContainer)
    {
        // Detect which one is container
        auto containerRect = isMovableContainer ? movableRect : collidedRect;
        auto nonContainerRect = isCollidedContainer ? movableRect : collidedRect;
        // If container smaller then non-container, they have to use default handling
        if (nonContainerRect.size.width >= containerRect.size.width || nonContainerRect.size.height >= containerRect.size.height)
        {
            isOnlyOneContainer = false;
        }
        else
        {
            // If collided is container
            if (isCollidedContainer)
            {
                // Compute difference of out sides + error with same sign
                if (movableRect.getMaxX() > collidedRect.getMaxX()) { resolveChangeX = collidedRect.getMaxX() - movableRect.getMaxX() - resolveChangeError; }
                else if (movableRect.getMinX() < collidedRect.getMinX()) { resolveChangeX = collidedRect.getMinX() - movableRect.getMinX() + resolveChangeError; }

                if (movableRect.getMaxY() > collidedRect.getMaxY()) { resolveChangeY = collidedRect.getMaxY() - movableRect.getMaxY() - resolveChangeError; }
                else if (movableRect.getMinY() < collidedRect.getMinY()) { resolveChangeY = collidedRect.getMinY() - movableRect.getMinY() + resolveChangeError; }
                // If movable just stay it never resolve collisions, let's move it anyway,
                // on random value dirty solution, but it seems to be worked
                if (std::abs(0 - resolveChangeX) < floatComparsionError && std::abs(0 - resolveChangeY) < floatComparsionError)
                {
                    int indexOfMovable = std::find(mCollidableList.begin(), mCollidableList.end(), movable) - mCollidableList.begin();
                    int indexOfCollided = std::find(mCollidableList.begin(), mCollidableList.end(), collided) - mCollidableList.begin();
                    int randomChange = RandomHelper::random_int(1, 8);

                    resolveChangeX = resolveChangeY = indexOfMovable > indexOfCollided ? -randomChange : randomChange;
                }
            }
            // If movable is container no need to move it, we not react inside collisions
        }
    }
    // Default handling
    if (!isOnlyOneContainer)
    {
        // Compute difference of inversed sides + error with same sign
        if (movableRect.getMinX() < collidedRect.getMaxX() && movableRect.getMaxX() > collidedRect.getMaxX())
        {
            resolveChangeX = collidedRect.getMaxX() - movableRect.getMinX() + resolveChangeError;
        }
        else if (movableRect.getMaxX() < collidedRect.getMaxX() && movableRect.getMaxX() > collidedRect.getMinX())
        {
            resolveChangeX = collidedRect.getMinX() - movableRect.getMaxX() - resolveChangeError;
        }

        if (movableRect.getMinY() < collidedRect.getMaxY() && movableRect.getMaxY() > collidedRect.getMaxY())
        {
            resolveChangeY = collidedRect.getMaxY() - movableRect.getMinY() + resolveChangeError;
        }
        else if (movableRect.getMaxY() < collidedRect.getMaxY() && movableRect.getMaxY() > collidedRect.getMinY())
        {
            resolveChangeY = collidedRect.getMinY() - movableRect.getMaxY() - resolveChangeError;
        }
        // Duplicate of upper code because not in all situations we need change resolvechange vars
        if (std::abs(0 - resolveChangeX) < floatComparsionError && std::abs(0 - resolveChangeY) < floatComparsionError)
        {
            int indexOfMovable = std::find(mCollidableList.begin(), mCollidableList.end(), movable) - mCollidableList.begin();
            int indexOfCollided = std::find(mCollidableList.begin(), mCollidableList.end(), collided) - mCollidableList.begin();
            int randomChange = RandomHelper::random_int(1, 8);

            resolveChangeX = resolveChangeY = indexOfMovable > indexOfCollided ? -randomChange : randomChange;
        }
    }
    //---Apply a new move rotation
    // If movable is container no need to rotate it, we not react inside collisions
    // but if they are both containers, we need to handle it default way
    if (!isMovableContainer || !isOnlyOneContainer)
    {
        float leftDistance, rightDistance, topDistance, bottomDistance;
        Rect resolvedRect(Vec2(movableRect.getMinX() + resolveChangeX, movableRect.getMinY() + resolveChangeY), movableRect.size);
        // In fact there is will be true only if collided is container, so
        // we need special handling in this situation
        if (isOnlyOneContainer)
        { // Compare same sides
            leftDistance = std::abs(resolvedRect.getMinX() - collidedRect.getMinX());
            rightDistance = std::abs(resolvedRect.getMaxX() - collidedRect.getMaxX());
            topDistance = std::abs(resolvedRect.getMaxY() - collidedRect.getMaxY());
            bottomDistance = std::abs(resolvedRect.getMinY() - collidedRect.getMinY());

            auto minVertical = std::min(topDistance, bottomDistance);
            auto minHorizontal = std::min(leftDistance, rightDistance);
            // Orientation of collision, 0 if symmetric, 1 if vertical, -1 if horizontal
            int orientation = std::abs(minVertical - minHorizontal) < orientationDifferenceError ? 0 : (minHorizontal > minVertical ? 1 : -1);
            int newMoveRotation = movable->getMoveRotation();
            // For different collision orientation different rotation
            if (orientation == 1) { newMoveRotation = 180 - movable->getMoveRotation(); } // Mirroring rotation
            else if (orientation == -1) { newMoveRotation = 360 - movable->getMoveRotation(); } // Mirroring rotation
            else { newMoveRotation += 180; } // Inverse rotation
            // Circling degrees
            if (newMoveRotation < 0) { newMoveRotation += 360; }
            else if (newMoveRotation >= 360) { newMoveRotation -= 360; }
            // Set computed rotation
            movable->setMoveRotation(newMoveRotation);
        }
        else
        { // Compare inversed sides
            leftDistance = std::abs(resolvedRect.getMinX() - collidedRect.getMaxX());
            rightDistance = std::abs(resolvedRect.getMaxX() - collidedRect.getMinX());
            topDistance = std::abs(resolvedRect.getMaxY() - collidedRect.getMinY());
            bottomDistance = std::abs(resolvedRect.getMinY() - collidedRect.getMaxY());
            // Inverse rotation + random shift within 40 degrees
            int newMoveRotation = movable->getMoveRotation() + RandomHelper::random_int(-20, 20);
            newMoveRotation += newMoveRotation >= 180 ? -180 : 180;
            // Set computed rotation
            movable->setMoveRotation(newMoveRotation);
        }
    }
    auto resolveVelocity = movable->getMoveVelocity() * PhysicsConsts::Movable::RESOLVE_COLLISION_VELOCITY_FACTOR;
    //---Start resolving move
    movable->moveBy(Vec2(resolveChangeX, resolveChangeY), resolveVelocity, CallFunc::create([=]()
    {
        auto collided = searchCollided(movable, movable->getRect());

        if (collided && mPostResolvingMap.find(movable) == mPostResolvingMap.end()) { mPostResolvingMap[movable] = collided; }
    }));
}

void Physics::resolveDamage(Damageable *damageable, Projectile *projectile)
{
    damageable->applyDamage(projectile->getDamage());
}
