#include "../include/IShape.h"
#include <sstream>
#include <iomanip>
#include <iostream>

std::string IShape::GetColorHex(const uint32_t color) const
{
    std::stringstream ss;
    ss << std::setfill('0') << std::setw(8) << std::hex << color;
    return ss.str();
}