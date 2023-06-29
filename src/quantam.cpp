#include <dpp/message.h>
#include "quantam.hpp"

#include "dpp/dpp.h"
#include "string"

using std::string;
using dpp::snowflake;

const ulong my_server = 1027866055856619550ULL;
const std::string quantam_id = "b!quantam_1";
const std::string khongquantam_id = "b!khongquantam_1";

dpp::message create_quantam(snowflake author_id, snowflake channel_id, dpp::message::message_ref ref, bool quantam = true)
{
    auto res = dpp::message(
            channel_id,
            std::string("<@") + std::to_string(author_id) + "> đã "
            + (quantam ? "thể hiện sự quan tâm." : "đéo hỏi.")
    )
            .add_component(
                    dpp::component()
                            .add_component(
                                    dpp::component().set_label(quantam ? "Thể hiện sự quan tâm của bạn" : "Yêu cầu tìm ra người đã hỏi")
                                            .set_type(dpp::cot_button)
                                            .set_style(quantam ? dpp::cos_success : dpp::cos_danger)
                                            .set_id(quantam ? quantam_id : khongquantam_id)
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

bool handle_quantam(const dpp::message_create_t& event, dpp::cluster& bot, const string& content, const string& content_lower)
{
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
        return true;
    }

    if (content_lower.starts_with("b!khongquantam") || content_lower.starts_with("b!kqt"))
    {
        auto ref = event.msg.message_reference;
        auto msg = create_quantam(event.msg.author.id, event.msg.channel_id, ref, false);
        if (ref.message_id.empty())
        {
            event.reply(msg, true);
        }
        else
        {
            bot.message_create(msg);
        }
        return true;
    }
    
    return false;
}

bool handle_quantam_click(const dpp::button_click_t& event, dpp::cluster& bot)
{
    auto command = event.command;
    auto author_id = command.get_issuing_user().id;
    if (event.custom_id == quantam_id)
    {
        auto msg = create_quantam(author_id, command.channel_id, command.msg.message_reference);
        msg = msg.set_content(std::string("<@") + std::to_string(author_id) + "> cũng đã thể hiện sự quan tâm.");
        if (msg.guild_id == my_server)
        {
            msg.allowed_mentions.replied_user = true;
        }
        event.reply();
        bot.message_create(msg);
        return true;
    }

    if (event.custom_id == khongquantam_id)
    {
        auto msg = create_quantam(author_id, command.channel_id, command.msg.message_reference, false);
        msg = msg.set_content(std::string("<@") + std::to_string(author_id) + "> cũng đã đéo hỏi.");
        if (msg.guild_id == my_server)
        {
            msg.allowed_mentions.replied_user = true;
        }
        event.reply();
        bot.message_create(msg);
        return true;
    }
    
    return false;
}

bool handle_quantam_context(const dpp::message_context_menu_t& event, dpp::cluster& bot)
{
    auto author_id = event.command.get_issuing_user().id;
    auto command = event.command;
    dpp::message::message_ref dummy_ref;
    dummy_ref.channel_id = command.channel_id;
    dummy_ref.guild_id = event.command.guild_id;
    dummy_ref.message_id = event.ctx_message.id;
    if (event.command.get_command_name() == quantam_ctxmenu_name)
    {
        auto msg = create_quantam(author_id, command.channel_id, dummy_ref);
        msg.allowed_mentions.replied_user = true;
        event.reply(dpp::message("đợi tí").set_flags(dpp::m_ephemeral));
        bot.message_create(msg);
        return true;
    }

    if (event.command.get_command_name() == khongquantam_ctxmenu_name)
    {
        auto msg = create_quantam(author_id, command.channel_id, dummy_ref, false);
        msg.allowed_mentions.replied_user = true;
        event.reply(dpp::message("cứ từ từ").set_flags(dpp::m_ephemeral));
        bot.message_create(msg);
        return true;
    }
    
    return false;
}