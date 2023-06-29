#ifndef COMMAND_RATE
#define COMMAND_RATE

#include "string"
#include "random"
#include "execution"
#include "dpp/dpp.h"

using std::string;

int rate(long unixTimestampInSeconds, int min = 0, int max = 11)
{
    const int cycle = 60;
    std::mt19937 engine (unixTimestampInSeconds / cycle);
    auto result = (engine() % (unsigned long) (max - min + 1));
    return (int) result + min;
}

bool handleRNG(const dpp::message_create_t& event, const string& content, const string& content_lower) {
    auto time = (event.msg.id >> 22) + 1420070400000ULL;
    
    if (content_lower.starts_with("b!draken"))
    {
        auto result = rate((long) time / 1000, 0, 11);
        auto msg = std::string("độ draken của ngày hôm nay hiện tại là **" + std::to_string(result) + "**/**10**");
        event.reply(msg);
        return true;
    }

    if (content_lower.starts_with("b!briten"))
    {
        auto result = 11 - rate((long) time / 1000, 0, 11);
        auto msg = std::string("độ briten của ngày hôm nay hiện tại là **" + std::to_string(result) + "**/**10**");
        event.reply(msg);
        return true;
    }

    if (content_lower.starts_with("b!hailong"))
    {
        auto uid = event.msg.author.id.operator uint64_t();
        auto seed = uid / 1000 + time / 1000;
        auto result = 11 - rate((long) seed, 0, 11);
        auto msg = std::string("độ hài lòng của <@" + std::to_string(uid) + "> là **" + std::to_string(result) + "**/**10** ");
        event.reply(msg, true);
        return true;
    }

    if (content_lower.starts_with("b!khonghailong"))
    {
        auto uid = event.msg.author.id.operator uint64_t();
        auto seed = uid / 1000 + time / 1000;
        auto result = rate((long) seed, 0, 11);
        auto msg = std::string("độ không hài lòng của <@" + std::to_string(uid) + "> là **" + std::to_string(result) + "**/**10** ");
        event.reply(msg, true);
        return true;
    }
    
    return false;
}

#endif