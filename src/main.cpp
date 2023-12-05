#include <swiftly/swiftly.h>
#include <swiftly/server.h>
#include <swiftly/configuration.h>
#include <swiftly/logger.h>
#include <common.h>
#include <set>
#include <string>

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

void OnMapLoad(const char *mapName)
{
    LoadAdvertisements();
}

void OnMapUnload(const char *mapName)
{
    UnloadAdvertisements();
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