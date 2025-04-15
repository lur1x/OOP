#include "TVSet.h"
#include <algorithm>

void TVSet::TurnOn() {
    if (!isOn) {
        isOn = true;
    }
}

void TVSet::TurnOff() {
    if (isOn) {
        isOn = false;
    }
}

bool TVSet::SelectChannel(int channel) {
    if (!isOn || channel < 1 || channel > 99) {
        return false;
    }
    previousChannel = currentChannel;
    currentChannel = channel;
    return true;
}

bool TVSet::SelectChannel(const std::string& name) {
    if (!isOn) return false;

    auto it = nameToChannel.find(name);
    if (it == nameToChannel.end()) {
        return false;
    }
    return SelectChannel(it->second);
}

bool TVSet::SelectPreviousChannel() {
    if (!isOn || previousChannel == currentChannel) {
        return false;
    }
    std::swap(currentChannel, previousChannel);
    return true;
}

bool TVSet::SetChannelName(int channel, const std::string& name) {
    if (!isOn || channel < 1 || channel > 99 || name.empty()) {
        return false;
    }

    if (channelNames.count(channel) > 0) {
        nameToChannel.erase(channelNames[channel]);
    }

    channelNames[channel] = name;
    nameToChannel[name] = channel;
    return true;
}

bool TVSet::DeleteChannelName(const std::string& name) {
    if (!isOn || nameToChannel.count(name) == 0) {
        return false;
    }

    int channel = nameToChannel[name];
    channelNames.erase(channel);
    nameToChannel.erase(name);
    return true;
}

std::string TVSet::GetInfo() const {
    if (isOn) {
        return "TV is on. Channel: " + std::to_string(currentChannel);
    }
    return "TV is off";
}

std::vector<std::string> TVSet::GetChannelInfo() const {
    std::vector<std::string> info;
    for (const auto& [channel, name] : channelNames) {
        info.push_back(std::to_string(channel) + " - " + name);
    }
    // Сортировка по номеру канала
    std::sort(info.begin(), info.end(), [](const auto& a, const auto& b) {
        return std::stoi(a.substr(0, a.find(' '))) < std::stoi(b.substr(0, b.find(' ')));
    });
    return info;
}

std::string TVSet::GetChannelName(int channel) const {
    if (!isOn || channelNames.count(channel) == 0) {
        return "";
    }
    return channelNames.at(channel);
}

int TVSet::GetChannelByName(const std::string& name) const {
    if (!isOn || nameToChannel.count(name) == 0) {
        return 0;
    }
    return nameToChannel.at(name);
}