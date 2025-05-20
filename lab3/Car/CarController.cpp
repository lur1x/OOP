#include "CarController.h"
#include "Car.h"
#include <iostream>

bool CarController::Run()
{
    std::string command;
    while (m_input >> command)
    {
        if (command == INFO_COMMAND)
        {
            ActionPrintInfo();
        }
        else if (command == ENGINE_ON_COMMAND)
        {
            ActionEngineOn();
        }
        else if (command == ENGINE_OFF_COMMAND)
        {
            ActionEngineOff();
        }
        else if (command == SET_GEAR_COMMAND)
        {
            ActionSetGear();
        }
        else if (command == SET_SPEED_COMMAND)
        {
            ActionSetSpeed();
        }
        else if (command == EXIT_COMMAND)
        {
            break;
        }
        else
        {
            m_output << UNKNOWN_COMMAND;
        }
    }

    return true;
}


bool CarController::ActionPrintInfo()
{
    m_output << INFO_ENGINE << (m_car.IsTurnedOn() ? INFO_ON : INFO_OFF) << '\n';
    m_output << INFO_DIRECTION << m_car.GetDirection() << '\n';
    m_output << INFO_SPEED << m_car.GetSpeed() << '\n';
    m_output << INFO_GEAR << m_car.GetGear() << '\n';
    return true;
}

bool CarController::ActionEngineOn()
{
    m_car.TurnOnEngine();
    return true;
}

bool CarController::ActionEngineOff()
{
    if (!m_car.TurnOffEngine())
    {
        m_output << INVALID_TURNOFF_ENGINE;
        return false;
    }
    return true;
}

bool CarController::ActionSetGear()
{
    int value;
    if (!(m_input >> value))
    {
        m_output << INVALID_COMMAND_ARGUMENT;
        return false;
    }
    else
        m_car.SetGear(value);
    return true;
}

bool CarController::ActionSetSpeed()
{
    int value;
    if (!(m_input >> value))
    {
        m_output << INVALID_COMMAND_ARGUMENT;
        return false;
    }
    else
        m_car.SetSpeed(value);
    return true;
}
