#include <swiftly/swiftly.h>
#include <common.h>

void OnGameTick(bool simulating, bool bFirstTick, bool bLastTick)
{
    uint64_t time = GetTime();

    for (uint32_t i = 0; i < advertisements.size(); i++)
    {
        Advertisement *ad = advertisements.at(i);
        if (ad == nullptr)
            continue;

        if (ad->ShouldExecute(time))
            ad->Execute();
    }
}