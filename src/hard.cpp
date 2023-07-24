#include "dpp/dpp.h"
#include "string"
#include "hard.hpp"

namespace tax
{
    PresetCommand HardCommand
    {
        .command = std::vector<string> { "hard", "kho" },
        .ctxmenu_name = "Thể hiện sự bất lực",
        .button_id = "b!hard_1",
        .button_text = "Thể hiện sự bất lực của bạn",
        .button_style = dpp::cos_success,
        .format_message = [](const dpp::message_create_t& ev, dpp::cluster& bot, const string& content, const string& content_lower) {
            std::string a = ev.msg.id % 2 ? "đã cảm thấy bất lực." : "thấy thế này hơi khó.";
            return std::string("<@") + std::to_string(ev.msg.author.id) + "> " + a;
        },
        .format_context = [](const dpp::message_context_menu_t& ev, dpp::cluster& bot) {
            std::string a = ev.ctx_message.id % 2 ? "cũng thấy hơi bất lực." : "cũng thấy khó.";
            return std::string("<@") + std::to_string(ev.command.get_issuing_user().id) + "> " + a;
        },
        .format_click = [](const dpp::button_click_t& ev, dpp::cluster& bot) {
            std::string a = ((int64_t) ev.command.get_creation_time()) % 2 ? "cũng thấy hơi bất lực." : "cũng thấy khó.";
            return std::string("<@") + std::to_string(ev.command.get_issuing_user().id) + "> " + a;
        }
    };
}