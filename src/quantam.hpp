#ifndef TAX_QUANTAM_HPP
#define TAX_QUANTAM_HPP

#include "dpp/dpp.h"
#include "string"
using std::string;

const std::string quantam_ctxmenu_name = "Quan tâm";
const std::string khongquantam_ctxmenu_name = "Không quan tâm";
bool handle_quantam(const dpp::message_create_t& event, dpp::cluster& bot, const string& content, const string& content_lower);
bool handle_quantam_click(const dpp::button_click_t& event, dpp::cluster& bot);
bool handle_quantam_context(const dpp::message_context_menu_t& event, dpp::cluster& bot);

#endif //TAX_QUANTAM_HPP
