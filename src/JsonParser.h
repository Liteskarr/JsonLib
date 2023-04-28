#ifndef JSONPARSER_JSONPARSER_H
#define JSONPARSER_JSONPARSER_H

#include <tuple>
#include <string>
#include <regex>
#include <fstream>
#include "JsonObject.h"
#include "JsonParserSettings.h"

namespace bjson {
    class JsonParser {
    private:
        JsonParserSettings settings_;

        inline static bool IsWhitespace(char c);

        inline static size_t FindCloseBracket(const std::string& s, size_t begin, char open, char closed);

        JsonObject ParseNull(const std::string &s, size_t begin, size_t end);

        JsonObject ParseBool(const std::string &s, size_t begin, size_t end);

        JsonObject ParseInt(const std::string& s, size_t begin, size_t end);

        JsonObject ParseReal(const std::string& s, size_t begin, size_t end);

        JsonObject ParseNumber(const std::string &s, size_t begin, size_t end);

        JsonObject ParseString(const std::string &s, size_t begin, size_t end);

        JsonObject ParseArray(const std::string &s, size_t begin, size_t end);

        JsonObject ParseObject(const std::string &s, size_t begin, size_t end);

        JsonObject ParseValue(const std::string &s, size_t begin, size_t end);

        std::string Preprocess(const std::string& s);

    public:
        explicit JsonParser(JsonParserSettings settings = JsonParserSettings());

        JsonObject Parse(const std::string &s);

        JsonObject ParseFile(const std::string &filepath);
    };
}

#endif
