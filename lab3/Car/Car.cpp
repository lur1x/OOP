#include "Car.h"
#include "Constants.h"
#include <iostream>

const int Car::MIN_SPEED = 0;
const int Car::MAX_SPEED = 150;

const std::unordered_map<int, GearLimitSpeed> Car::SpeedLimitsForGears =
        {
                {-1, {0, 20}},
                {0, {MIN_SPEED, MAX_SPEED}},
                {1, {0, 30}},
                {2, {20, 50}},
                {3, {30, 60}},
                {4, {40, 90}},
                {5, {50, 150}},
        };


bool Car::IsTurnedOn() const
{
    return m_isTurnedOn;
}

int Car::GetSpeed() const
{
    return std::abs(m_speed);
}

int Car::GetGear() const
{
    return m_gear;
}

bool Car::TurnOnEngine()
{
    if (!IsTurnedOn())
    {
        m_isTurnedOn = true;
        m_gear = 0;
        m_speed = 0;
    }

    return IsTurnedOn();
}

bool Car::TurnOffEngine()
{
    if (IsTurnedOn() && GetGear() == 0 && GetSpeed() == 0 )
    {
        m_isTurnedOn = false;
    }

    return !IsTurnedOn();
}

bool Car::DisplayInfo() const
{
    std::cout << INFO_ENGINE << (IsTurnedOn() ? INFO_ON : INFO_OFF) << '\n';
    std::cout << INFO_DIRECTION << GetDirection() << '\n';
    std::cout << INFO_SPEED << GetSpeed() << '\n';
    std::cout << INFO_GEAR << GetGear() << '\n';
    return true;
}

std::string Car::GetDirection() const
{
    if (GetSpeed() == 0)
    {
        return STANDING_DIRECTION;
    }
    if (GetGear() >= 0)
    {
        return FORWARD_DIRECTION;
    }

    return BACKWARD_DIRECTION;
}

bool Car::SetSpeed(const int speed)
{
    if (speed < MIN_SPEED)
    {
        std::cout << SPEED_CANT_BE_NEGATIVE;
        return false;
    }
    if (!IsTurnedOn())
    {
        std::cout << TURN_IF_NOT_RUNNING_ENGINE;
        return false;
    }
    if (GetGear() == 0 && speed > GetSpeed())
    {
        std::cout << CANT_ACCELERATE_ON_NEUTRAL;
        return false;
    }
    if (!CanChangeSpeedForGear(speed))
    {
        std::cout << SPEED_OUT_OF_RANGE;
        return false;
    }

    m_speed = speed;

    return true;

}
bool Car::CanChangeSpeedForGear(const int speed) const
{
    auto speedLimitsOpt = GetSpeedLimitForGear(GetGear());
    if (!speedLimitsOpt)
        return false;

    const auto& limits = *speedLimitsOpt;
    const int currentSpeed = GetSpeed();

    if (speed > limits.maxSpeed || speed < limits.minSpeed)
        return false;

    return true;
}


bool Car::SetGear(const int gear)
{
    if (!IsTurnedOn())
    {
        std::cout << TURN_IF_NOT_RUNNING_ENGINE;
        return false;
    }

    switch (gear)
    {
        case -1:
            if (GetSpeed() != 0)
            {
                std::cout << CANT_REVERSE_WHILE_MOVING;
                return false;
            }
            m_gear = -1;
            break;
        case 0:
            m_gear = 0;
            break;
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
            if (!CanChangeGearForSpeed(gear))
            {
                std::cout << UNSUITABLE_CURRENT_SPEED;
                return false;
            }
            m_gear = gear;
            break;
        default:
            std::cout << INVALID_GEAR;
            return false;
    }

    return true;
}

std::optional<GearLimitSpeed> Car::GetSpeedLimitForGear(const int gear) const
{
    auto it = SpeedLimitsForGears.find(gear);
    if (it != SpeedLimitsForGears.end())
        return it->second;
    else
        return std::nullopt;
}

bool Car::CanChangeGearForSpeed(const int gear) const
{
    auto speedLimitsOpt = GetSpeedLimitForGear(gear);
    if (!speedLimitsOpt)
        return false;

    const auto& limits = *speedLimitsOpt;
    const int currentSpeed = GetSpeed();

    if ((GetDirection() == BACKWARD_DIRECTION && currentSpeed != 0)
    || currentSpeed > limits.maxSpeed || currentSpeed < limits.minSpeed)
        return false;

    return true;
}

