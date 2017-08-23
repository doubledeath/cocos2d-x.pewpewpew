#pragma once

#include "cocos2d.h"

class Config
{
public:
    static Config *fromString(std::string stringConfig);

    int getCountTarget();
    int getSpeed();
    int getTime();
private:
    Config();
};
