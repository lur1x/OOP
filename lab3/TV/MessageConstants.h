#pragma once
#include <string>


namespace Message {
    const std::string TV_TURNED_ON = "TV is turned on\n";
    const std::string TV_TURNED_OFF = "TV is turned off\n";

    const std::string CHANNEL_SWITCHED = "Channel switched to: ";
    const std::string SWITCHED_TO_PREVIOUS = "Switched to previous channel\n";

    const std::string CHANNEL_NAME_SET = "Channel name set: ";
    const std::string CHANNEL_NAME_DELETED = "Channel name deleted: ";
    const std::string CHANNEL_IS = "Channel is: ";

    const std::string ERROR = "ERROR\n";
}