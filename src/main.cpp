#include "rate.hpp"
#include "quantam.hpp"
#include <dpp/dpp.h>
#include "string"
#include "random"
#include "execution"
#include "cctype"

using dpp::snowflake;

std::locale botLocale("C");
const ulong my_server = 1027866055856619550ULL;
const std::string quantam_id = "b!quantam_1";
const std::string khongquantam_id = "b!khongquantam_1";

int main()
{
    auto token = getenv("DISCORD_TOKEN");
    dpp::cluster bot(token);
    bot.intents |= dpp::i_message_content;
    bot.on_log(dpp::utility::cout_logger());
    
    bot.on_message_create([&bot](const dpp::message_create_t& event) {
        auto content = event.msg.content;
        auto content_lower = content;
        std::transform(
                std::execution::par_unseq,
                content_lower.begin(),
                content_lower.end(),
                content_lower.begin(),
                [](char c) { return std::tolower(c, botLocale); }
        );
        
        if (handleRNG(event, content, content_lower)) {
            return;
        }

        if (handle_quantam(event, bot, content, content_lower)) {
            return;
        }
        
        if (content_lower.starts_with("b!xinloi")) {
            
        }
    });

    bot.on_button_click([&bot](const dpp::button_click_t& event) {
        if (handle_quantam_click(event, bot)) {
            return;
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

            bot.global_command_create(
                    dpp::slashcommand()
                            .set_type(dpp::ctxm_message)
                            .set_name(khongquantam_ctxmenu_name)
                            .set_application_id(bot.me.id)
            );
        }
    });
    
    bot.on_message_context_menu([&bot](const dpp::message_context_menu_t& event) {
        if (handle_quantam_context(event, bot)) {
            return;
        }
    });
    bot.start(dpp::st_wait);
}
