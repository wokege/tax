#ifndef COMMAND_RATE
#define COMMAND_RATE

#include "dpp/dpp.h"
#include "string"
using std::string;
bool handleRNG(const dpp::message_create_t& event, const string& content, const string& content_lower);

#endif
