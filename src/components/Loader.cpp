#include <common.h>
#include <swiftly/swiftly.h>
#include <swiftly/logger.h>
#include <swiftly/configuration.h>
#include <vector>

void LoadAdvertisements()
{
    uint32_t advs = config->FetchArraySize("advertisements.messages");
    for (uint32_t i = 0; i < advs; i++)
    {
        if (!config->Exists("advertisements.messages[%d].message", i))
        {
            logger->Write(LOGLEVEL_ERROR, "Couldn't load advertisement #%d because the message is not present in configuration file.", i);
            continue;
        }
        if (!config->Exists("advertisements.messages[%d].interval", i))
        {
            logger->Write(LOGLEVEL_ERROR, "Couldn't load advertisement #%d because the interval is not present in configuration file.", i);
            continue;
        }
        if (!config->Exists("advertisements.messages[%d].type", i))
        {
            logger->Write(LOGLEVEL_ERROR, "Couldn't load advertisement #%d because the type is not present in configuration file.", i);
            continue;
        }

        const char *message = config->Fetch<const char *>("advertisements.messages[%d].message", i);
        if (message == nullptr)
        {
            logger->Write(LOGLEVEL_ERROR, "Couldn't load advertisement #%d because the message is not a string.", i);
            continue;
        }

        int interval = config->Fetch<int>("advertisements.messages[%d].interval", i);
        if (interval < 500)
        {
            logger->Write(LOGLEVEL_ERROR, "Couldn't load advertisement #%d because the interval between messages needs to be greater or equal than 500ms.", i);
            continue;
        }

        const char *baseType = config->Fetch<const char *>("advertisements.messages[%d].type", i);
        if (baseType == nullptr)
        {
            logger->Write(LOGLEVEL_ERROR, "Couldn't load advertisement #%d because the type is not a string.", i);
            continue;
        }

        std::string type = baseType;
        if (type != "chat" && type != "center" && type != "notify")
        {
            logger->Write(LOGLEVEL_ERROR, "Couldn't load advertisement #%d because the type needs to be \"chat\" or \"center\". Current: \"%s\"", i, type.c_str());
            continue;
        }

        HudDestination dest = HUD_PRINTCONSOLE;
        if (type == "chat")
            dest = HUD_PRINTTALK;
        else if (type == "center")
            dest = HUD_PRINTCENTER;
        else if (type == "notify")
            dest = HUD_PRINTNOTIFY;

        Advertisement *ad = new Advertisement(message, interval, dest);
        advertisements.push_back(ad);
    }

    logger->Write(LOGLEVEL_DEBUG, "Advertisements loaded.");
}

void UnloadAdvertisements()
{
    advertisements.clear();
    logger->Write(LOGLEVEL_DEBUG, "Advertisements unloaded.");
}