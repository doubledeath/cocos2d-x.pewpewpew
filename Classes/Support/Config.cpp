#include "Config.h"

USING_NS_CC;

Config *Config::fromString(std::string stringConfig)
{
    log("Read config on data:\n%s", stringConfig.c_str());

    return nullptr;
}

Config::Config()
{

}

int Config::getCountTarget()
{
    return 0;
}

int Config::getSpeed()
{
    return 0;
}

int Config::getTime()
{
    return 0;
}
