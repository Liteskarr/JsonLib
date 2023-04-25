#ifndef JSONPARSER_JSONPARSER_H
#define JSONPARSER_JSONPARSER_H

#include <tuple>
#include <string>
#include "JsonObject.h"
#include "JsonParserSettings.h"

namespace bjson {
    class JsonParser {
    private:
        JsonParserSettings settings_;

        inline static bool IsWhitespace(char c);

        JsonObject ParseNull(const std::string &s, size_t begin, size_t end);

        JsonObject ParseBoolean(const std::string &s, size_t begin, size_t end);

        JsonObject ParseInt(const std::string& s, size_t begin, size_t end);

        JsonObject ParseFloat(const std::string& s, size_t begin, size_t end);

        JsonObject ParseNumber(const std::string &s, size_t begin, size_t end);

        JsonObject ParseString(const std::string &s, size_t begin, size_t end);

        JsonObject ParseArray(const std::string &s, size_t begin, size_t end);

        JsonObject ParseObject(const std::string &s, size_t begin, size_t end);

        JsonObject ParseValue(const std::string &s, size_t begin, size_t end);

    public:
        JsonParser();

        explicit JsonParser(JsonParserSettings settings);

        JsonObject Parse(const std::string &s);

        JsonObject ParseFile(const std::string &filepath);
    };
}

#endif
