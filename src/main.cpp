#include <dpp/dpp.h>
#include "string"
#include "random"
#include "execution"
#include "cctype"

std::locale botLocale("C");

int rate(long unixTimestampInSeconds, int min = 0, int max = 11)
{
    const int cycle = 60;
    std::mt19937 engine (unixTimestampInSeconds / cycle);
    auto result = (engine() % (unsigned long) (max - min + 1));
    return (int) result + min;
}

int main()
{
    auto token = getenv("DISCORD_TOKEN");
    dpp::cluster bot(token);
    bot.intents |= dpp::i_message_content;
    bot.on_log(dpp::utility::cout_logger());
    
    bot.on_message_create([](const dpp::message_create_t& event) {
        auto content = event.msg.content;
        auto content_lower = content;
        std::transform(
                std::execution::par_unseq,
                content_lower.begin(),
                content_lower.end(),
                content_lower.begin(),
                [](char c) { return std::tolower(c, botLocale); }
        );
        
        if (content_lower.starts_with("b!draken"))
        {
            auto time = (event.msg.id >> 22) + 1420070400000ULL;
            auto result = rate((long) time / 1000, 0, 11);
            auto msg = std::string("độ draken của ngày hôm nay hiện tại là **" + std::to_string(result) + "**/**10**");
            event.reply(msg);
            return;
        };
    });

    bot.on_ready([&bot](const dpp::ready_t& event) {
        bot.log(dpp::loglevel::ll_info, "we're ready!");
    });

    bot.start(dpp::st_wait);
}
