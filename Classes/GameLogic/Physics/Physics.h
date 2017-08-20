#pragma once

#include "cocos2d.h"
#include "Collidable.h"
#include "Movable.h"
#include "Damageable.h"
#include "Projectile.h"
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
     * @brief resolving collision between movable and it's collided
     * @param movable which will be moved for resolve collisions
     * @param collided
     */
    void resolveCollision(Movable *movable, Collidable *collided);
    void resolveDamage(Damageable *damageable, Projectile *projectile);
};
