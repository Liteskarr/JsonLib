#ifndef JSONPARSER_JSONPARSER_H
#define JSONPARSER_JSONPARSER_H

#include "JsonObject.h"
#include "JsonParserSettings.h"

namespace bjson {
    class JsonParser {
    private:
        JsonParserSettings _settings;

    public:
        JsonParser();

        explicit JsonParser(JsonParserSettings settings);

        JsonObject parse_string(const std::string_view& s);

        JsonObject parse_file(const std::string_view& filepath);
    };
}

#endif
