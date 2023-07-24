#ifndef COMMAND_RATE
#define COMMAND_RATE

#include "string"
#include "random"
#include "execution"
#include "dpp/dpp.h"
#include "response.hpp"

using std::string;

int rate(long unixTimestampInSeconds, int min = 0, int max = 11)
{
    const int cycle = 60;
    std::mt19937 engine (unixTimestampInSeconds / cycle);
    auto result = (engine() % (unsigned long) (max - min + 1));
    return (int) result + min;
}

namespace tax
{
    PresetCommand DrakenCommand
    {
        .command = std::vector<string> { "draken" },
        .enable_ctxmenu = false,
        .enable_button = false,
        .follow_reference = false,
        .format_message = [](const dpp::message_create_t& ev, dpp::cluster& bot, const string& content, const string& content_lower) {
            auto time = (ev.msg.id >> 22) + 1420070400000ULL;
            auto result = rate((long) time / 1000, 0, 11);
            return std::string("độ draken của ngày hôm nay hiện tại là **" + std::to_string(result) + "**/**10**");
        }
    };
    PresetCommand BritenCommand
    {
        .command = std::vector<string> { "briten" },
        .enable_ctxmenu = false,
        .enable_button = false,
        .follow_reference = false,
        .format_message = [](const dpp::message_create_t& ev, dpp::cluster& bot, const string& content, const string& content_lower) {
            auto time = (ev.msg.id >> 22) + 1420070400000ULL;
            auto result = 11 - rate((long) time / 1000, 0, 11);
            return std::string("độ briten của ngày hôm nay hiện tại là **" + std::to_string(result) + "**/**10**");
        }
    };
    PresetCommand HailongCommand
    {
        .command = std::vector<string> { "hailong" },
        .enable_ctxmenu = false,
        .enable_button = false,
        .follow_reference = false,
        .format_message = [](const dpp::message_create_t& ev, dpp::cluster& bot, const string& content, const string& content_lower) {
            auto time = (ev.msg.id >> 22) + 1420070400000ULL;
            auto uid = ev.msg.author.id.operator uint64_t();
            auto seed = uid / 1000 + time / 1000;
            auto result = 11 - rate((long) seed, 0, 11);
            return std::string("độ hài lòng của <@" + std::to_string(uid) + "> là **" + std::to_string(result) + "**/**10** ");
        }
    };
    PresetCommand KhonghailongCommand
    {
        .command = std::vector<string> { "khonghailong" },
        .enable_ctxmenu = false,
        .enable_button = false,
        .follow_reference = false,
        .format_message = [](const dpp::message_create_t& ev, dpp::cluster& bot, const string& content, const string& content_lower) {
            auto time = (ev.msg.id >> 22) + 1420070400000ULL;
            auto uid = ev.msg.author.id.operator uint64_t();
            auto seed = uid / 1000 + time / 1000;
            auto result = rate((long) seed, 0, 11);
            return std::string("độ không hài lòng của <@" + std::to_string(uid) + "> là **" + std::to_string(result) + "**/**10** ");
        }
    };
}

#endif