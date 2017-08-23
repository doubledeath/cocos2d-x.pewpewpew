#include "Config.h"
#include "ConfigConsts.h"

USING_NS_CC;

Config::Config()
{
    setCountTarget(ConfigConsts::Balloon::COUNT_TARGET);
    setSpeed(ConfigConsts::CannonBall::SPEED);
    setTime(ConfigConsts::World::TIME);
}

Config::~Config()
{

}

void Config::fromString(std::string stringConfig)
{
    log("Parsing config:\n%s", stringConfig.c_str());


}

int Config::getCountTarget() const
{
    return mCountTarget;
}

int Config::getSpeed() const
{
    return mSpeed;
}

int Config::getTime() const
{
    return mTime;
}

void Config::setCountTarget(int countTarget)
{
    mCountTarget = countTarget;
}

void Config::setSpeed(int speed)
{
    mSpeed = speed;
}

void Config::setTime(int time)
{
    mTime = time;
}
