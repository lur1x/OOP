#ifndef CAR_CONSTANTS_H
#define CAR_CONSTANTS_H

#include <string>

const std::string ENGINE_ON = "EngineOn";
const std::string ENGINE_OFF = "EngineOff";
const std::string INFO = "Info";
const std::string SET_GEAR = "SetGear";
const std::string SET_SPEED = "SetSpeed";

//const std::string FORWARD_DIRECTION = "forward";
//const std::string BACKWARD_DIRECTION = "backward";
//const std::string STANDING_DIRECTION = "standing still";

const std::string INFO_ENGINE = "Engine: ";
const std::string INFO_DIRECTION = "Direction: ";
const std::string INFO_SPEED = "Speed: ";
const std::string INFO_GEAR = "Gear: ";
const std::string INFO_ON = "on";
const std::string INFO_OFF = "off";

const std::string UNKNOWN_COMMAND = "Unknown command\n";
const std::string INVALID_COMMAND_ARGUMENT = "Invalid command argument\n";
const std::string INVALID_TURNOFF_ENGINE = "Car must be stopped and in neutral gear\n";
const std::string INVALID_GEAR = "Invalid gear\n";
const std::string TURN_IF_NOT_RUNNING_ENGINE = "Cannot set gear while engine is off\n";
const std::string UNSUITABLE_CURRENT_SPEED = "Unsuitable current speed\n";
const std::string CANT_REVERSE_WHILE_MOVING = "Cannot reverse while moving\n";
const std::string SPEED_CANT_BE_NEGATIVE = "Speed cannot be negative\n";
const std::string CANT_SET_SPEED_ENGINE_OFF = "Cannot set speed while engine is off\n";
const std::string CANT_ACCELERATE_ON_NEUTRAL = "Cannot accelerate on neutral\n";
const std::string SPEED_OUT_OF_RANGE = "Speed is out of gear range\n";

#endif //CAR_CONSTANTS_H


