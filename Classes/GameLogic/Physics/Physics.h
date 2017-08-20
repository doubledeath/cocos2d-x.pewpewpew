#pragma once

#include "cocos2d.h"
#include "Collidable.h"
#include "Movable.h"
#include "Damageable.h"
#include "Projectile.h"
#include "Resolvable.h"
#include "CollidableType.h"
#include "CollidableTypeMask.h"

class Physics
{
public:
    virtual void update(float delta);
    virtual void addCollidable(Collidable *collidable);
    virtual void removeCollidable(Collidable *collidable);
private:
    std::vector<Collidable *> mCollidableList;
    std::map<Collidable *, cocos2d::Rect> mPastRectMap;
    /**
     * @brief contains collidables which resolving collisions just now
     */
    std::map<Collidable *, Collidable *> mResolvingMap;
    /**
     * @brief contains collidables which still have after last resolve,
     * they can appear in process of resolving, they need to be resolved once again,
     * onCollided will be sent every once item in this list,
     * OnCollisionResolved will be sent only if collidable have completely no collisions
     */
    std::map<Collidable *, Collidable *> mPostResolvingMap;
    /**
     * @brief notified with OnCollided collidables,
     * also indicates if collisions are started to resolve
     */
    std::map<Collidable *, bool> mOnCollidedMap;
    /**
     * @brief notified with OnCollisionResolved collidables
     */
    std::map<Collidable *, bool> mOnCollisionResolvedMap;
    /**
     * @brief searching collided with passed rect
     * @param collidable needed to get type, mask and exclude collision with itself
     * @param rect for search collided
     * @return collidable which collided with rect
     */
    Collidable *searchCollided(Collidable *collidable, cocos2d::Rect rect);
    /**
     * @brief search all collided from targetList with passed rect
     * @param collidable needed to type and mask
     * @param rect for search collided
     * @param targetList list for search
     * @return collidable list which collided with rect
     */
    std::vector<Collidable *> searchCollidedList(Collidable *collidable, cocos2d::Rect rect, std::vector<Collidable *> targetList);
    cocos2d::Rect computeTunnelRect(cocos2d::Rect collidableRect, cocos2d::Rect collidablePastRect);
    /**
     * @brief resolving something between collidable and it's collided
     * @param collidable
     * @param collided
     */
    void resolve(Collidable *collidable, Collidable *collided);
    /**
     * @brief resolving collision between resolvable and it's collided
     * @param resolvable
     * @param collided
     */
    void resolveCollision(Resolvable *resolvable, Collidable *collided);
    /**
     * @brief resolving damage between resolvable and it's collided
     * @param damageable
     * @param projectile
     */
    void resolveDamage(Damageable *damageable, Projectile *projectile);
    /**
     * @brief resolving rotation between movable and it's collided
     * @param movable
     * @param collided
     * @param isOnlyOneContainer needed for check default or container handling
     * @param resolveChangeX needed to compute rotation
     * @param resolveChangeY needed to compute rotation
     */
    void resolveRotation(Movable *movable, Collidable *collided, bool isOnlyOneContainer, float resolveChangeX, float resolveChangeY);
};
