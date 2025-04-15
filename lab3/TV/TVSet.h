#pragma once
#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>

class TVSet {
public:
    void TurnOn();
    void TurnOff();

    bool SelectChannel(int channel);
    bool SelectChannel(const std::string& name);
    bool SelectPreviousChannel();

    bool SetChannelName(int channel, const std::string& name);
    bool DeleteChannelName(const std::string& name);

    std::string GetInfo() const;
    //std::vector<std::string> GetChannelInfo() const;

private:
    bool isOn = false;
    int currentChannel = 1;
    int previousChannel = 1;

    std::unordered_map<int, std::string> channelNames;
    std::unordered_map<std::string, int> nameToChannel;

    bool IsTurnedOn() const
    {
        return isOn;
    }
    int GetChannel() const
    {
        return isOn ? currentChannel : 0;
    }
    std::string GetChannelName(int channel) const;
    int GetChannelByName(const std::string& name) const;
};