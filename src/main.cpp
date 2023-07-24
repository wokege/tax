#include "rate.hpp"
#include "quantam.hpp"
#include "hard.hpp"
#include "response.hpp"
#include <dpp/dpp.h>
#include "string"
#include "random"
#include "execution"
#include "vector"

using dpp::snowflake;
using namespace tax;

std::locale botLocale("C");

int main()
{
    std::vector<PresetCommand> Commands { 
        HardCommand,
        QuantamCommand, KhongquantamCommand,
        DrakenCommand, BritenCommand, HailongCommand, KhonghailongCommand
    };
    
    auto token = getenv("DISCORD_TOKEN");
    dpp::cluster bot(token);
    bot.intents |= dpp::i_message_content;
    bot.on_log(dpp::utility::cout_logger());
    
    bot.on_message_create([&bot, &Commands](const dpp::message_create_t& event) {
        auto content = event.msg.content;
        auto content_lower = content;
        std::transform(
            std::execution::par_unseq,
            content_lower.begin(),
            content_lower.end(),
            content_lower.begin(),
            [](char c) { return std::tolower(c, botLocale); }
        );
        
        if (content_lower.starts_with("b!"))
        {
            auto command = std::string_view(content_lower.begin() + 2, content_lower.end());
            for (auto cmd : Commands)
            {
                for (const auto& alias : cmd.command)
                {
                    if (command.starts_with(alias))
                    {
                        auto rest = std::string_view(command.begin() + alias.length());
                        if (rest.length() == 0 || rest[0] == ' ')
                        {
                            cmd.handle_message(event, bot, content, content_lower);
                            return;
                        }
                    }
                }
            }
        }
    });

    bot.on_button_click([&bot, &Commands](const dpp::button_click_t& event) {
        for (auto cmd : Commands)
        {
            if (!cmd.enable_button) continue;
            if (cmd.button_id == event.custom_id)
            {
                cmd.handle_click(event, bot);
                return;
            }    
        }
    });
    
    bot.on_ready([&bot, &Commands](const dpp::ready_t& event) {
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
            for (auto cmd : Commands)
            {
                if (cmd.enable_ctxmenu)
                {
                    bot.global_command_create(
                        dpp::slashcommand()
                            .set_type(dpp::ctxm_message)
                            .set_name(cmd.ctxmenu_name)
                            .set_application_id(bot.me.id)
                    );
                }
            }
        }
    });
    
    bot.on_message_context_menu([&bot, &Commands](const dpp::message_context_menu_t& event) {
        for (auto cmd : Commands)
        {
            if (!cmd.enable_ctxmenu) continue;
            if (cmd.ctxmenu_name == event.command.get_command_name())
            {
                cmd.handle_context(event, bot);
                return;
            }
        }
    });
    bot.start(dpp::st_wait);
}
