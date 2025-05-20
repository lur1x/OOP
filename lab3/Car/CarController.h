#ifndef CAR_CARCONTROLLER_H
#define CAR_CARCONTROLLER_H
#include "Car.h"

class CarController
{
public:
    CarController(std::istream &input, std::ostream &output) : m_input(input), m_output(output), m_car(output){};
    bool Run();

private:
    Car m_car;
    std::istream &m_input;
    std::ostream &m_output;

    bool ActionPrintInfo();
    bool ActionEngineOn();
    bool ActionEngineOff();
    bool ActionSetGear();
    bool ActionSetSpeed();
};

#endif //CAR_CARCONTROLLER_H
