#include <dpp/message.h>
#include "quantam.hpp"

#include "dpp/dpp.h"
#include "string"
#include "vector"
#include "response.hpp"

using std::string;
using dpp::snowflake;

namespace tax
{
    PresetCommand QuantamCommand
    {
        .command = std::vector<string> { "qt", "quantam" },
        .ctxmenu_name = "Quan tâm",
        .button_id = "b!quantam_1",
        .button_text = "Thể hiện sự quan tâm của bạn",
        .button_style = dpp::cos_success,
        .format_message = [](const dpp::message_create_t& ev, dpp::cluster& bot, const string& content, const string& content_lower) {
            return std::string("<@") + std::to_string(ev.msg.author.id) + "> đã thể hiện sự quan tâm.";
        },
        .format_context = [](const dpp::message_context_menu_t& ev, dpp::cluster& bot) {
            return std::string("<@") + std::to_string(ev.command.get_issuing_user().id) + "> đã thể hiện sự quan tâm.";
        },
        .format_click = [](const dpp::button_click_t& ev, dpp::cluster& bot) {
            return std::string("<@") + std::to_string(ev.command.get_issuing_user().id) + "> cũng đã thể hiện sự quan tâm.";
        }
    };

    PresetCommand KhongquantamCommand
    {
        .command = std::vector<string> { "kqt", "khongquantam" },
        .ctxmenu_name = "Không quan tâm",
        .button_id = "b!khongquantam_1",
        .button_text = "Yêu cầu tìm ra người đã hỏi",
        .button_style = dpp::cos_danger,
        .format_message = [](const dpp::message_create_t& ev, dpp::cluster& bot, const string& content, const string& content_lower) {
            return std::string("<@") + std::to_string(ev.msg.author.id) + "> đã đéo hỏi.";
        },
        .format_context = [](const dpp::message_context_menu_t& ev, dpp::cluster& bot) {
            return std::string("<@") + std::to_string(ev.command.get_issuing_user().id) + "> đã đéo hỏi.";
        },
        .format_click = [](const dpp::button_click_t& ev, dpp::cluster& bot) {
            return std::string("<@") + std::to_string(ev.command.get_issuing_user().id) + "> cũng đã đéo hỏi.";
        }
    };
}