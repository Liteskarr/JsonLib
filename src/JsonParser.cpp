#include "JsonParser.h"

namespace bjson {
    const static size_t NULL_LENGTH = 4;
    const static size_t TRUE_LENGTH = 4;
    const static size_t FALSE_LENGTH = 5;

    inline bool JsonParser::IsWhitespace(char c) {
        return c == ' ' || c == '\t' || c == '\n' || c == '\r';
    }

    JsonObject JsonParser::ParseNull(const std::string &s, size_t begin, size_t end) {
        if (end - begin == NULL_LENGTH && s[begin] == 'n' && s[begin + 1] == 'u' && s[begin + 2] == 'l' &&
            s[begin + 3] == 'l') {
            return JsonObject(JsonObjectType::Null);
        } else {
            throw JsonException();
        }
    }

    JsonObject JsonParser::ParseBoolean(const std::string &s, size_t begin, size_t end) {
        if (end - begin == TRUE_LENGTH && s[begin] == 't' && s[begin + 1] == 'r' && s[begin + 2] == 'u' &&
            s[begin + 3] == 'e') {
            return {true};
        } else if (end - begin == FALSE_LENGTH && s[begin] == 'f' && s[begin + 1] == 'a' && s[begin + 2] == 'l' &&
                   s[begin + 3] == 's' && s[begin + 4] == 'e') {
            return {false};
        } else {
            throw JsonException();
        }
    }

    JsonObject ParseInt(const std::string& s, size_t begin, size_t end) {
        try {
            return JsonObject(std::stoll(s.substr(begin, end - begin)));
        } catch (std::invalid_argument e) {
            throw JsonException();
        } catch (std::out_of_range e) {
            throw JsonException();
        }
    }

    JsonObject ParseReal(const std::string& s, size_t begin, size_t end) {
        try {
            return JsonObject(std::stod(s.substr(begin, end - begin)));
        } catch (std::invalid_argument e) {
            throw JsonException();
        } catch (std::out_of_range e) {
            throw JsonException();
        }
    }

    JsonObject JsonParser::ParseNumber(const std::string &s, size_t begin, size_t end) {
        auto is_int = !settings_.AllNumbersAsFloats;
        for (size_t i = begin; is_int && i != end; ++i) {
            is_int &= std::isdigit(s[i]) || s[i] == '-' || s[i] == '+';
        }
        if (is_int) {
            return ParseInt(s, begin, end);
        } else {
            return ParseFloat(s, begin, end);
        }
    }

    JsonObject JsonParser::ParseString(const std::string &s, size_t begin, size_t end) {
        return JsonObject(s.substr(begin, end - begin));
    }

    JsonObject JsonParser::ParseArray(const std::string &s, size_t begin, size_t end) {

    }

    JsonObject JsonParser::ParseObject(const std::string &s, size_t begin, size_t end) {

    }

    JsonObject JsonParser::ParseValue(const std::string &s, size_t begin, size_t end) {
        while (begin < end && IsWhitespace(s[begin])) {
            ++begin;
        }
        if (begin == end) {
            throw JsonException();
        }
        while (IsWhitespace(s[end - 1])) {
            --end;
        }
        if (s[begin] == '{' && s[end - 1] == '}') {
            return ParseObject(s, begin + 1, end - 1);
        } else if (s[begin] == '[' && s[end - 1] == ']') {
            return ParseArray(s, begin + 1, end - 1);
        } else if (s[begin] == 't' && s[end - 1] == 'e' || s[begin] == 'f' && s[end - 1] == 'e') {
            return ParseBoolean(s, begin, end);
        } else if (s[begin] == 'n' && s[end - 1] == 'l') {
            return ParseNull(s, begin, end);
        } else if (s[begin] == '"' && s[end - 1] == '"') {
            return ParseString(s, begin + 1, end - 1);
        } else {
            return ParseNumber(s, begin, end);
        }
    }

    JsonParser::JsonParser() : settings_(JsonParserSettings::GetDefault()) {
    }

    JsonParser::JsonParser(bjson::JsonParserSettings settings) : settings_(settings) {
    }

    JsonObject JsonParser::Parse(const std::string& s) {
        return ParseValue(s, 0, s.size());
    }

    JsonObject JsonParser::ParseFile(const std::string &filepath) {
        return JsonObject(JsonObjectType::Null);
    }
}