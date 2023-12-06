#ifndef _common_h
#define _common_h
#pragma once

#include <vector>
#include <string>

void LoadAdvertisements();
void UnloadAdvertisements();
void ExecuteAdvertisementsCheck();

enum HudDestination;

class Advertisement
{
private:
    std::string m_message;
    int m_interval;
    HudDestination m_type;
    uint64_t m_lastExecuted = 0;

public:
    Advertisement(std::string message, int interval, HudDestination advType) : m_message(message), m_interval(interval), m_type(advType) {}

    bool ShouldExecute(uint64_t time);
    void Execute();
};

extern std::vector<Advertisement *> advertisements;
std::string replace(std::string str, const std::string from, const std::string to);
std::vector<std::string> explode(std::string s, std::string delimiter);

#endif