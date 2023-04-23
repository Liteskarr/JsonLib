#include "JsonParser.h"

namespace bjson {
    JsonParser::JsonParser() : _settings(JsonParserSettings::GetDefault()) {
    }

    JsonParser::JsonParser(bjson::JsonParserSettings settings) : _settings(settings) {
    }

    JsonObject JsonParser::parse_string(const std::string_view &s) {

    }
}