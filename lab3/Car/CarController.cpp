#include "CarController.h"
#include "Car.h"
#include <iostream>

bool PrintInfo(Car& car)
{
    car.DisplayInfo();
    return true;
}

bool HandleEngineOnCommand(Car& car)
{
    car.TurnOnEngine();
    return true;
}

bool HandleEngineOffCommand(Car& car)
{
    if (!car.TurnOffEngine())
    {
        std::cout << INVALID_TURNOFF_ENGINE;
        return false;
    }
    return true;
}

bool HandleSetGearCommand(Car& car)
{
    int value;
    if (!(std::cin >> value))
    {
        std::cout << INVALID_COMMAND_ARGUMENT;
        return false;
    }
    else
        car.SetGear(value);
    return true;
}

bool HandleSetSpeedCommand(Car& car)
{
    int value;
    if (!(std::cin >> value))
    {
        std::cout << INVALID_COMMAND_ARGUMENT;
        return false;
    }
    else
        car.SetSpeed(value);
    return true;
}

void RunCarController()
{
    Car car;

    std::string command;
    while (std::cin >> command)
    {
        if (command == INFO_COMMAND)
        {
            PrintInfo(car);
        }
        else if (command == ENGINE_ON_COMMAND)
        {
            HandleEngineOnCommand(car);
        }
        else if (command == ENGINE_OFF_COMMAND)
        {
            HandleEngineOffCommand(car);
        }
        else if (command == SET_GEAR_COMMAND)
        {
            HandleSetGearCommand(car);
        }
        else if (command == SET_SPEED_COMMAND)
        {
            HandleSetSpeedCommand(car);
        }
        else if (command == EXIT_COMMAND)
        {
            break;
        }
        else
        {
            std::cout << UNKNOWN_COMMAND;
        }
    }

    return;
}