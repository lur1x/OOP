#ifndef CAR_CAR_H
#define CAR_CAR_H
#include "Constants.h"
#include <unordered_map>
#include <optional>

struct GearLimitSpeed
{
    int minSpeed;
    int maxSpeed;
};

class Car
{
public:
    bool TurnOnEngine();
    bool TurnOffEngine();
    bool SetSpeed(const int speed);
    bool SetGear(const int gear);

private:
    static const std::unordered_map<int, GearLimitSpeed> SpeedLimitsForGears;
    static const int MIN_SPEED;
    static const int MAX_SPEED;

    bool m_isTurnedOn = false;
    int m_speed = 0;
    int m_gear = 0;

    bool IsTurnedOn() const;
    int GetSpeed() const;
    int GetGear() const;
    std::string GetDirection() const;
    bool CanChangeGearForSpeed() const;
    bool CanChangeSpeedForGear(const int speed) const;
    std::optional<GearLimitSpeed> GetSpeedLimitForGear() const;
};

#endif //CAR_CAR_H
