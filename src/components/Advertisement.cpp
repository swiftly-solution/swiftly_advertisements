#include <common.h>
#include <swiftly/server.h>
#include <string>
#include <vector>

std::vector<std::string> explode(std::string s, std::string delimiter)
{
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    std::string token;
    std::vector<std::string> res;

    while ((pos_end = s.find(delimiter, pos_start)) != std::string::npos)
    {
        token = s.substr(pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back(token);
    }

    res.push_back(s.substr(pos_start));
    return res;
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

        g_playerManager->SendMsg(this->m_type, this->m_message.c_str());
    }

    this->m_lastExecuted = GetTime();
}