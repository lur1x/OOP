#include "Car.h"
#include "Constants.h"
#include <iostream>

const std::unordered_map<int, GearLimitSpeed> Car::SpeedLimitsForGears =
        {
                {-1, {0, 20}},
                {0, {0, 150}},
                {1, {0, 30}},
                {2, {20, 50}},
                {3, {30, 60}},
                {4, {40, 90}},
                {5, {50, 150}},
        };

const int Car::MIN_SPEED = 0;
const int Car::MAX_SPEED = 150;

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

    return true;
}

bool Car::TurnOffEngine()
{
    if (IsTurnedOn() && GetGear() == 0 && GetSpeed() == 0 )
    {
        m_isTurnedOn = false;
    }

    return true;
}

void Car::SetDirection()
{

    if (GetSpeed() == 0)
    {
        m_direction = MoveDirection::STANDING_STILL;
        return;
    }
    if (GetGear() > 0)
    {
        m_direction = MoveDirection::FORWARD;
        return;
    }

    m_direction = MoveDirection::BACKWARD;
}

MoveDirection Car::GetDirection() const
{
    return m_direction;
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
    SetDirection();

    return true;

}
bool Car::CanChangeSpeedForGear(const int speed) const
{
    auto speedLimitsOpt = GetSpeedLimitForGear();
    if (!speedLimitsOpt)
        return false;

    const auto& limits = *speedLimitsOpt;
    const int currentSpeed = GetSpeed();

    if (speed > limits.maxSpeed || currentSpeed < limits.minSpeed)
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
            if (!CanChangeGearForSpeed())
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

std::optional<GearLimitSpeed> Car::GetSpeedLimitForGear() const
{
    auto it = SpeedLimitsForGears.find(GetGear());
    if (it != SpeedLimitsForGears.end())
        return it->second;
    else
        return std::nullopt;
}

bool Car::CanChangeGearForSpeed() const
{
    auto speedLimitsOpt = GetSpeedLimitForGear();
    if (!speedLimitsOpt)
        return false;

    const auto& limits = *speedLimitsOpt;
    const int currentSpeed = GetSpeed();

    if ((GetDirection() == MoveDirection::BACKWARD && currentSpeed != 0)
    || currentSpeed > limits.maxSpeed || currentSpeed < limits.minSpeed)
        return false;

    return true;
}

