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
    Car(std::ostream &output) : m_output(output){};

    bool IsTurnedOn() const;

    int GetSpeed() const;
    int GetGear() const;

    std::string GetDirection() const;

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
    std::ostream &m_output;

    bool CanChangeGearForSpeed(const int gear) const;
    bool CanChangeSpeedForGear(const int speed) const;
    std::optional<GearLimitSpeed> GetSpeedLimitForGear(const int gear) const;
};

#endif //CAR_CAR_H
