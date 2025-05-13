#ifndef CAR_CAR_H
#define CAR_CAR_H
#include <map>

class Car
{
public:

    enum class MoveDirection
    {
        FORWARD,
        BACKWARD,
        STAY,
    };

    bool IsTurnedOn() const;
    bool TurnOnEngine();
    bool TurnOffEngine();

    MoveDirection GetDirection() const;

    int GetSpeed() const;
    bool SetSpeed(int speed);

    int GetGear() const;
    bool SetGear(int gear);

private:
    bool m_isEngineOn = false;
    int m_speed = 0;
    int m_gear = 0;
};


#endif //CAR_CAR_H
