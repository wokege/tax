#include <dpp/dpp.h>
#include "string"
#include "random"
#include "execution"
#include "cctype"

std::locale botLocale("C");
const std::string quantam_id = "b!quantam_1";

int rate(long unixTimestampInSeconds, int min = 0, int max = 11)
{
    const int cycle = 60;
    std::mt19937 engine (unixTimestampInSeconds / cycle);
    auto result = (engine() % (unsigned long) (max - min + 1));
    return (int) result + min;
}

dpp::message createQuantam(dpp::snowflake channel_id, dpp::snowflake author_id)
{
    return dpp::message(
            channel_id,
            std::string("<@") + std::to_string(author_id) + "> đã thể hiện sự quan tâm."
    )
            .add_component(
                    dpp::component().add_component(
                            dpp::component().set_label("Thể hiện sự quan tâm của bạn")
                                    .set_type(dpp::cot_button)
                                    .set_style(dpp::cos_success)
                                    .set_id(quantam_id)
                    )
            );
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
        auto time = (event.msg.id >> 22) + 1420070400000ULL;
        std::transform(
                std::execution::par_unseq,
                content_lower.begin(),
                content_lower.end(),
                content_lower.begin(),
                [](char c) { return std::tolower(c, botLocale); }
        );
        
        if (content_lower.starts_with("b!draken"))
        {
            auto result = rate((long) time / 1000, 0, 11);
            auto msg = std::string("độ draken của ngày hôm nay hiện tại là **" + std::to_string(result) + "**/**10**");
            event.reply(msg);
            return;
        }

        if (content_lower.starts_with("b!briten"))
        {
            auto result = 11 - rate((long) time / 1000, 0, 11);
            auto msg = std::string("độ briten của ngày hôm nay hiện tại là **" + std::to_string(result) + "**/**10**");
            event.reply(msg);
            return;
        }

        if (content_lower.starts_with("b!hailong"))
        {
            auto uid = event.msg.author.id.operator uint64_t();
            auto seed = uid / 1000 + time / 1000;
            auto result = 11 - rate((long) seed, 0, 11);
            auto msg = std::string("độ hài lòng của <@" + std::to_string(uid) + "> là **" + std::to_string(result) + "**/**10** ");
            event.reply(msg, true);
            return;
        }
        
        if (content_lower.starts_with("b!quantam"))
        {
            auto msg = createQuantam(event.msg.channel_id, event.msg.author.id);
            event.reply(msg, true);
            return;
        }
    });

    bot.on_button_click([&bot](const dpp::button_click_t& event) {
        if (event.custom_id == quantam_id)
        {
            auto command = event.command;
            auto author_id = command.get_issuing_user().id;
            auto msg = createQuantam(event.command.channel_id, event.command.get_issuing_user().id);
            msg = msg
                    .set_reference(
                        command.msg.message_reference.message_id,
                        command.msg.message_reference.guild_id,
                        command.msg.message_reference.channel_id,
                        false
                    );
            msg = msg.set_content(std::string("<@") + std::to_string(author_id) + "> cũng đã thể hiện sự quan tâm.");
            event.reply();
            bot.message_create(msg);
        }
    });
    
    bot.on_ready([&bot](const dpp::ready_t& event) {
        auto me = bot.me;
        auto discrim_string = new char[5];
        asprintf(&discrim_string, "%04d", me.discriminator);
        bot.log(
                dpp::loglevel::ll_info,
                "We're ready! Logged in as " + me.username + "#" + std::string(discrim_string)
        );
        delete[] discrim_string;
    });

    bot.start(dpp::st_wait);
}
