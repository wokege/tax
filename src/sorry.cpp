#include "sorry.hpp"

namespace tax
{
    std::string SorryPresetResponses[] = {
        "đã thể hiện sự hối lỗi",
        "mong được thứ lỗi"
    };
    
    PresetCommand SorryCommand
    {
        .command = std::vector<string> { "xinloi", "sorry" },
        .ctxmenu_name = "Thể hiện sự hối lỗi",
        .button_id = "b!sorry",
        .button_text = "Thể hiện sự hối lỗi của bạn",
        .button_style = dpp::cos_success,
        .format_message = [](const dpp::message_create_t& ev, dpp::cluster& bot, const string& content, const string& content_lower) {
            auto msg = SorryPresetResponses[ev.msg.id % 2];
            return std::string("<@") + std::to_string(ev.msg.author.id) + "> " + msg + ".";
        },
        .format_context = [](const dpp::message_context_menu_t& ev, dpp::cluster& bot) {
            auto msg = SorryPresetResponses[ev.ctx_message.id % 2];
            return std::string("<@") + std::to_string(ev.command.get_issuing_user().id) + "> " + msg + ".";
        },
        .format_click = [](const dpp::button_click_t& ev, dpp::cluster& bot) {
            auto msg = SorryPresetResponses[ev.command.msg.id % 2];
            return std::string("<@") + std::to_string(ev.command.get_issuing_user().id) + "> cũng " + msg + ".";
        }
    };
}