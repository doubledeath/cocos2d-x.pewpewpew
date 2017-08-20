#pragma once

#include "Enemy.h"

class Balloon : public Enemy
{
public:
    CREATE_FUNC(Balloon)

    virtual bool init() override;
};
