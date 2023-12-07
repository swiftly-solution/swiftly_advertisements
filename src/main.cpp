#include <swiftly/swiftly.h>
#include <swiftly/server.h>
#include <swiftly/configuration.h>
#include <swiftly/logger.h>
#include <swiftly/gameevents.h>
#include <common.h>
#include <string>
#include <vector>

Server *server = nullptr;
PlayerManager *g_playerManager = nullptr;
Configuration *config = nullptr;
Logger *logger = nullptr;
std::vector<Advertisement *> advertisements;

void OnProgramLoad(const char *pluginName, const char *mainFilePath)
{
    Swiftly_Setup(pluginName, mainFilePath);

    server = new Server();
    g_playerManager = new PlayerManager();
    config = new Configuration();
    logger = new Logger(mainFilePath, pluginName);
}

void OnPluginStart()
{
    LoadAdvertisements();
    logger->Write(LOGLEVEL_DEBUG, "Plugin started. Build Date: %s", __DATE__);
}

void OnPluginStop()
{
    UnloadAdvertisements();
    logger->Write(LOGLEVEL_DEBUG, "Plugin stopped.");
}

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
        std::string mmsg = message;

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

        Advertisement *ad = new Advertisement(mmsg, interval, dest);
        advertisements.push_back(ad);
    }

    logger->Write(LOGLEVEL_DEBUG, "Advertisements loaded.");
}

void UnloadAdvertisements()
{
    advertisements.clear();
    logger->Write(LOGLEVEL_DEBUG, "Advertisements unloaded.");
}

bool Advertisement::ShouldExecute(uint64_t time)
{
    return ((time - this->m_lastExecuted) >= this->m_interval);
}

void Advertisement::Execute()
{
    std::vector<std::string> messages = explode(this->m_message, "\n");
    for (std::string msg : messages)
    {
        msg = replace(msg, "{players}", std::to_string(g_playerManager->GetPlayers()));
        msg = replace(msg, "{maxplayers}", std::to_string(server->GetMaxPlayers()));
        msg = replace(msg, "{map}", server->GetMap());

        g_playerManager->SendMsg(this->m_type, msg.c_str());
    }

    this->m_lastExecuted = GetTime();
}

const char *GetPluginAuthor()
{
    return "Swiftly Solutions";
}

const char *GetPluginVersion()
{
    return "1.0.0";
}

const char *GetPluginName()
{
    return "Advertisements - Add messages to server";
}

const char *GetPluginWebsite()
{
    return "https://github.com/swiftly-solution/swiftly_advertisements";
}