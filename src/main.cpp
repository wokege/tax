#include <dpp/dpp.h>
#include "string"
#include "random"
#include "execution"
#include "cctype"

using dpp::snowflake;

std::locale botLocale("C");
const std::string quantam_id = "b!quantam_1";
const std::string quantam_ctxmenu_name = "Quan tâm";

int rate(long unixTimestampInSeconds, int min = 0, int max = 11)
{
    const int cycle = 60;
    std::mt19937 engine (unixTimestampInSeconds / cycle);
    auto result = (engine() % (unsigned long) (max - min + 1));
    return (int) result + min;
}

dpp::message create_quantam(snowflake author_id, snowflake channel_id, dpp::message::message_ref ref)
{
    auto res = dpp::message(
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

    if (!ref.message_id.empty()) {
        res = res
                .set_reference(ref.message_id, ref.guild_id, ref.channel_id, false)
                .set_allowed_mentions(
                        true,
                        false,
                        false,
                        false,
                        std::vector<dpp::snowflake>{}, std::vector<dpp::snowflake>{}
                );
    }
    return res;
}

int main()
{
    auto token = getenv("DISCORD_TOKEN");
    dpp::cluster bot(token);
    bot.intents |= dpp::i_message_content;
    bot.on_log(dpp::utility::cout_logger());
    
    bot.on_message_create([&bot](const dpp::message_create_t& event) {
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
        
        if (content_lower.starts_with("b!quantam") || content_lower.starts_with("b!qt"))
        {
            auto ref = event.msg.message_reference;
            auto msg = create_quantam(event.msg.author.id, event.msg.channel_id, ref);
            if (ref.message_id.empty())
            {
                event.reply(msg, true);
            }
            else
            {
                bot.message_create(msg);
            }
            return;
        }
    });

    bot.on_button_click([&bot](const dpp::button_click_t& event) {
        if (event.custom_id == quantam_id)
        {
            auto command = event.command;
            auto author_id = command.get_issuing_user().id;
            auto msg = create_quantam(author_id, command.channel_id, command.msg.message_reference);
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
                "We're ready! Logged in as " + me.username + "#" + std::string(discrim_string) + '.'
        );
        delete[] discrim_string;

        if (dpp::run_once<struct register_bot_commands>())
        {
            bot.global_command_create(
                dpp::slashcommand()
                    .set_type(dpp::ctxm_message)
                    .set_name(quantam_ctxmenu_name)
                    .set_application_id(bot.me.id)
            );
        }
    });
    
    bot.on_message_context_menu([&bot](const dpp::message_context_menu_t& event) {
        if (event.command.get_command_name() == quantam_ctxmenu_name)
        {
            auto author_id = event.command.get_issuing_user().id;
            auto command = event.command;
            dpp::message::message_ref dummy_ref;
            dummy_ref.channel_id = command.channel_id;
            dummy_ref.guild_id = event.command.guild_id;
            dummy_ref.message_id = event.ctx_message.id;
            auto msg = create_quantam(author_id, command.channel_id, dummy_ref);
            msg = msg.set_content(std::string("<@") + std::to_string(author_id) + "> cũng đã thể hiện sự quan tâm.");
            
            event.reply(dpp::message("đợi tí").set_flags(dpp::m_ephemeral));
            bot.message_create(msg);
        }
    });
    bot.start(dpp::st_wait);
}
