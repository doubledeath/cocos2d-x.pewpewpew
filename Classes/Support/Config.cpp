#include "Config.h"
#include "ConfigConsts.h"

USING_NS_CC;

Config::Config()
{
    setCountTarget(ConfigConsts::Balloon::COUNT_TARGET_DEFAULT_VALUE);
    setSpeed(ConfigConsts::CannonBall::SPEED_DEFAULT_VALUE);
    setTime(ConfigConsts::World::TIME_DEFAULT_VALUE);
}

Config::~Config()
{

}

void Config::fromString(std::string stringConfig)
{
    log("Parsing config from string started:\n%s", stringConfig.c_str());

    try
    {
        std::stringstream stream(stringConfig);

        while(!stream.eof())
        {
            std::string buf;
            std::string::size_type idx;
            std::getline(stream, buf);

            if (buf.find(ConfigConsts::Balloon::COUNT_TARGET) != std::string::npos)
            {
                int countTarget = std::stoi(buf.substr(ConfigConsts::Balloon::COUNT_TARGET.length() + 1), &idx);

                if (countTarget >= 1)
                {
                    setCountTarget(countTarget);

                    log("Parsed: %s", (ConfigConsts::Balloon::COUNT_TARGET + "=" + std::to_string(getCountTarget())).c_str());
                }
                else
                {
                    log("%s", (ConfigConsts::Balloon::COUNT_TARGET + "is lower then 1, resetting to default...").c_str());
                }
            }

            if (buf.find(ConfigConsts::CannonBall::SPEED) != std::string::npos)
            {
                int speed = std::stoi(buf.substr(ConfigConsts::CannonBall::SPEED.length() + 1), &idx);

                if (speed >= 1)
                {
                    setSpeed(speed);

                    log("Parsed: %s", (ConfigConsts::CannonBall::SPEED + "=" + std::to_string(getSpeed())).c_str());
                }
                else
                {
                    log("%s", (ConfigConsts::CannonBall::SPEED + "is lower then 1, resetting to default...").c_str());
                }
            }

            if (buf.find(ConfigConsts::World::TIME) != std::string::npos)
            {
                int time = std::stoi(buf.substr(ConfigConsts::World::TIME.length() + 1), &idx);

                if (time >= 1)
                {
                    setTime(time);

                    log("Parsed: %s", (ConfigConsts::World::TIME + "=" + std::to_string(getTime())).c_str());
                }
                else
                {
                    log("%s", (ConfigConsts::World::TIME + "is lower then 1, resetting to default...").c_str());
                }
            }
        }
    }
    catch(const std::runtime_error& runtimeError)
    {
        log("%s", ("Error occured: " + std::string(runtimeError.what())).c_str());
        log("Resetting values to defaults...");

        setCountTarget(ConfigConsts::Balloon::COUNT_TARGET_DEFAULT_VALUE);
        setSpeed(ConfigConsts::CannonBall::SPEED_DEFAULT_VALUE);
        setTime(ConfigConsts::World::TIME_DEFAULT_VALUE);
    }
    catch(const std::exception& exception)
    {
        log("%s", ("Error occured: " + std::string(exception.what())).c_str());
        log("Resetting values to defaults...");

        setCountTarget(ConfigConsts::Balloon::COUNT_TARGET_DEFAULT_VALUE);
        setSpeed(ConfigConsts::CannonBall::SPEED_DEFAULT_VALUE);
        setTime(ConfigConsts::World::TIME_DEFAULT_VALUE);
    }
    catch (...)
    {
        log("Unknown error occured\nResetting values to defaults...");

        setCountTarget(ConfigConsts::Balloon::COUNT_TARGET_DEFAULT_VALUE);
        setSpeed(ConfigConsts::CannonBall::SPEED_DEFAULT_VALUE);
        setTime(ConfigConsts::World::TIME_DEFAULT_VALUE);
    }

    log("Parsing config from string ended");
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
