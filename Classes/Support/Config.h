#pragma once

#include "cocos2d.h"

class Config
{
public:
    static Config &getInstance()
    {
        static Config config;
        return config;
    }

    void fromString(std::string stringConfig);
    int getCountTarget() const;
    int getSpeed() const;
    int getTime() const;
    void setSpeed(int speed);
    void setCountTarget(int countTarget);
    void setTime(int time);
private:
    int mCountTarget;
    int mSpeed;
    int mTime;

    Config();
    ~Config();

    Config(Config const&) = delete;
    Config& operator= (Config const&) = delete;
};
