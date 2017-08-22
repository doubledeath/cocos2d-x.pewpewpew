#pragma once

#include "cocos2d.h"
#include "Collidable.h"

class ParentCollidable : public virtual Collidable
{
public:
    virtual int getType() const override;
    virtual int getTypeMask() const override;
    virtual void onCollided() override;
    virtual void onCollisionResolved() override;
    virtual bool isCircle() override;

    void setType(int type);
    void setTypeMask(int typeMask);
    void setIsCircle(bool isCircle);
private:
    int mType;
    int mTypeMask;
    int mIsCircle;
};
