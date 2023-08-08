//
// Created by cipher on 8/8/23.
//

#include "wish.hpp"
namespace tax
{
    PresetCommand WishCommand
    {
        .command = std::vector<string> { "uoc", "wish", "ước" },
        .ctxmenu_name = "Ước",
        .button_id = "b!uoc_1",
        .button_text = "Ước",
        .button_style = dpp::cos_success,
        .format_message = [](const dpp::message_create_t& ev, dpp::cluster& bot, const string& content, const string& content_lower) {
            return std::string("<@") + std::to_string(ev.msg.author.id) + "> chỉ biết ước.";
        },
        .format_context = [](const dpp::message_context_menu_t& ev, dpp::cluster& bot) {
            return std::string("<@") + std::to_string(ev.command.get_issuing_user().id) + "> chỉ biết ước.";
        },
        .format_click = [](const dpp::button_click_t& ev, dpp::cluster& bot) {
            return std::string("<@") + std::to_string(ev.command.get_issuing_user().id) + "> cũng chỉ biết ước.";
        }
    };
}
