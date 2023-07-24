#ifndef TAX_RESPONSE_HPP
#define TAX_RESPONSE_HPP

#include "string"
#include "vector"
#include "dpp/dpp.h"
#include "functional"
using std::string;
using std::vector;
using std::function;
using dpp::snowflake;

class PresetCommand
{
public:
    vector<string> command;
    string ctxmenu_name;
    bool enable_ctxmenu = true;
    bool enable_button = true;
    bool follow_reference = true;
    
    string button_id;
    string button_text;
    dpp::component_style button_style;

    function<string(const dpp::message_create_t&, dpp::cluster&, const string&, const string&)> format_message;
    function<string(const dpp::message_context_menu_t&, dpp::cluster&)> format_context;
    function<string(const dpp::button_click_t&, dpp::cluster&)> format_click;
    
    void handle_message(const dpp::message_create_t& event, dpp::cluster& bot, const string& content, const string& content_lower);
    void handle_click(const dpp::button_click_t& event, dpp::cluster& bot);
    void handle_context(const dpp::message_context_menu_t& event, dpp::cluster& bot);

private:
    [[nodiscard]] dpp::message create_message(const std::string& content, snowflake author_id, snowflake channel_id, dpp::message::message_ref ref) const;
};

#endif //TAX_RESPONSE_HPP
