#include "response.hpp"

using dpp::snowflake;

dpp::message PresetCommand::create_message(const std::string& content, snowflake author_id, snowflake channel_id, dpp::message::message_ref ref) const
{
    auto res = dpp::message(channel_id, content);
    if (this->enable_button)
    {
        res = res.add_component(
            dpp::component()
                .add_component(
                    dpp::component().set_label(this->button_text)
                        .set_type(dpp::cot_button)
                        .set_style(this->button_style)
                        .set_id(this->button_id)
                )
        );
    }
        

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

void PresetCommand::handle_message(const dpp::message_create_t &event, dpp::cluster &bot, const std::string &content,
                                   const std::string &content_lower)
{
    auto ref = event.msg.message_reference;
    std::string c = this->format_message ? this->format_message(event, bot, content, content_lower): "";
    auto msg = this->create_message(c, event.msg.author.id, event.msg.channel_id, ref);
    if (ref.message_id.empty() || !this->follow_reference)
    {
        event.reply(msg, true);
    }
    else
    {
        bot.message_create(msg);
    }
}

void PresetCommand::handle_click(const dpp::button_click_t &event, dpp::cluster &bot)
{
    auto comm = event.command;
    auto author_id = comm.get_issuing_user().id;
    if (event.custom_id == this->button_id)
    {
        std::string c = this->format_click ? this->format_click(event, bot): "";
        auto msg = create_message(c, author_id, comm.channel_id, comm.msg.message_reference);
        event.reply();
        bot.message_create(msg);
    }
}

void PresetCommand::handle_context(const dpp::message_context_menu_t &event, dpp::cluster &bot)
{
    auto author_id = event.command.get_issuing_user().id;
    auto c = event.command;
    dpp::message::message_ref dummy_ref;
    dummy_ref.channel_id = c.channel_id;
    dummy_ref.guild_id = event.command.guild_id;
    dummy_ref.message_id = event.ctx_message.id;
    if (event.command.get_command_name() == this->ctxmenu_name)
    {
        std::string content = this->format_context ? this->format_context(event, bot) : "";
        auto msg = create_message(content, author_id, c.channel_id, dummy_ref);
        msg.allowed_mentions.replied_user = true;
        event.reply(dpp::message("từ từ, đợi tí").set_flags(dpp::m_ephemeral));
        bot.message_create(msg);
    }
}