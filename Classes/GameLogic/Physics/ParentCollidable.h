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

    void setType(int type);
    void setTypeMask(int typeMask);
private:
    int mType;
    int mTypeMask;
};
