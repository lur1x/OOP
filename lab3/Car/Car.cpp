#include "Car.h"

static constexpr int  MIN_GEAR = -1;
static constexpr int  MAX_GEAR = 5;
static constexpr int MIN_SPEED = 0;
static constexpr int MAX_SPEED = 150;

struct GearLimitSpeed
{
    int lowerLimit;
    int upperLimit;
};

const std::map<int, GearLimitSpeed> SpeedLimitsForGears =
{
        {-1, {MIN_SPEED, 20}},
        {0, {MIN_SPEED, MAX_SPEED}},
        {1, {MIN_SPEED, 30}},
        {2, {20, 50}},
        {3, {30, 60}},
        {4, {40, 90}},
        {5, {50, MAX_SPEED}},
};

bool Car::IsTurnedOn() const
{
    return m_isEngineOn;
}

Car::MoveDirection Car::GetDirection() const
{
    if (m_speed = 0 && )
}

int Car::GetSpeed() const
{
    return m_speed;//
}

int Car::GetGear() const
{
    return m_gear;
}

bool Car::TurnOnEngine()
{
    if (m_isEngineOn)
    {
        return false;
    }

    m_isEngineOn = true;
    return true;
}

bool Car::TurnOffEngine()
{
    if (!m_isEngineOn || m_gear != 0 || m_speed != 0 )
    {
        return false;
    }

    m_isEngineOn = false;
    return true;
}

bool Car::SetGear(int gear)
{

}