#include "JsonParser.h"

namespace bjson {
    const static size_t NULL_LENGTH = 4;
    const static size_t TRUE_LENGTH = 4;
    const static size_t FALSE_LENGTH = 5;

    const static std::regex STRING_FINDER("\"([\\w \\t\\n\\r]|\\\\\")*\"");

    inline bool JsonParser::IsWhitespace(char c) {
        return c == ' ' || c == '\t' || c == '\n' || c == '\r';
    }

    size_t JsonParser::FindCloseBracket(const std::string &s, size_t begin, char open, char closed) {
        int32_t balance = s[begin] == open;
        bool is_literal = false;
        ++begin;
        while (begin < s.size()) {
            if (!is_literal){
                if (s[begin] == open) {
                    ++balance;
                } else if (s[begin] == closed) {
                    --balance;
                }
                if (s[begin] == closed && !balance) {
                    return begin;
                }
            }
            if (begin && s[begin - 1] == '\\' && s[begin] == '"') {
                is_literal = !is_literal;
            }
            ++begin;
        }
        return -1;
    }

    JsonObject JsonParser::ParseNull(const std::string &s, size_t begin, size_t end) {
        if (end - begin == NULL_LENGTH && s[begin] == 'n' && s[begin + 1] == 'u' && s[begin + 2] == 'l' &&
            s[begin + 3] == 'l') {
            return JsonObject::MakeNull();
        } else {
            throw JsonException("Invalid format of null!");
        }
    }

    JsonObject JsonParser::ParseBool(const std::string &s, size_t begin, size_t end) {
        if (end - begin == TRUE_LENGTH && s[begin] == 't' && s[begin + 1] == 'r' && s[begin + 2] == 'u' &&
            s[begin + 3] == 'e') {
            return JsonObject::MakeBool(true);
        } else if (end - begin == FALSE_LENGTH && s[begin] == 'f' && s[begin + 1] == 'a' && s[begin + 2] == 'l' &&
                   s[begin + 3] == 's' && s[begin + 4] == 'e') {
            return JsonObject::MakeBool(false);
        } else {
            throw JsonException("Invalid format of bool!");
        }
    }

    JsonObject JsonParser::ParseInt(const std::string &s, size_t begin, size_t end) {
        try {
            return JsonObject::MakeInt(std::stoll(s.substr(begin, end - begin)));
        } catch (std::invalid_argument e) {
            throw JsonException("Invalid format of int number!");
        } catch (std::out_of_range e) {
            throw JsonException("Int number out of range!");
        }
    }

    JsonObject JsonParser::ParseReal(const std::string &s, size_t begin, size_t end) {
        try {
            return JsonObject::MakeReal(std::stod(s.substr(begin, end - begin)));
        } catch (std::invalid_argument e) {
            throw JsonException("Invalid format of real number!");
        } catch (std::out_of_range e) {
            throw JsonException("Real number out of range!");
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
            return ParseReal(s, begin, end);
        }
    }

    JsonObject JsonParser::ParseString(const std::string &s, size_t begin, size_t end) {
        return JsonObject::MakeString(s.substr(begin, end - begin));
    }

    JsonObject JsonParser::ParseArray(const std::string &s, size_t begin, size_t end) {
        std::vector<JsonObject> v;
        while (begin < end) {
            int32_t balance = s[begin] == '[' || s[begin] == '{';
            size_t object_end = begin;
            while (object_end < end) {
                if (s[object_end] == '{' || s[object_end] == '[') {
                    ++balance;
                } else if (s[object_end] == '}' || s[object_end] == ']') {
                    --balance;
                }
                if (s[object_end] == ',' && !balance) {
                    break;
                }
                ++object_end;
            }
            v.push_back(ParseValue(s, begin, object_end));
            while (begin < end && s[begin] != ',') {
                ++begin;
            }
            ++begin;
        }
        return JsonObject::MakeArray(v);
    }

    JsonObject JsonParser::ParseObject(const std::string &s, size_t begin, size_t end) {
        std::map<std::string, JsonObject> m;
        std::string key;
        std::smatch sm;
        while (begin < end) {
            if (std::regex_search(static_cast<int64_t>(begin) + s.begin(), static_cast<int64_t>(end) + s.begin(),sm, STRING_FINDER)) {
                auto fm = *sm.begin();
                key = s.substr(fm.first - s.begin() + 1, fm.length() - 2);
                begin = fm.second - s.begin();
            } else {
                throw JsonException("Key not found!");
            }
            if (s[begin] == ':') {
                ++begin;
            } else {
                throw JsonException("Splitter not found!");
            }
            size_t object_end = begin + 1;
            bool is_literal = false;
            int32_t balance = s[begin] == '{' || s[begin] == '[';
            while (object_end < end) {
                if (!is_literal) {
                    if (s[object_end] == '{' || s[object_end] == '[') {
                        ++balance;
                    } else if (s[object_end] == '}' || s[object_end] == ']') {
                        --balance;
                    }
                    if (s[object_end] == ',' && !balance) {
                        break;
                    }
                }
                if (object_end && s[object_end - 1] != '\\' && s[object_end] == '"') {
                    is_literal = !is_literal;
                }
                ++object_end;
            }
            m[key] = ParseValue(s, begin, object_end);
            begin = object_end;
        }
        return JsonObject::MakeObject(m);
    }

    JsonObject JsonParser::ParseValue(const std::string &s, size_t begin, size_t end) {
        while (begin < end && IsWhitespace(s[begin])) {
            ++begin;
        }
        if (begin == end) {
            return JsonObject::MakeNull();
        }
        if (s[begin] == '{') {
            return ParseObject(s, begin + 1, FindCloseBracket(s, begin, '{', '}'));
        } else if (s[begin] == '[') {
            return ParseArray(s, begin + 1, FindCloseBracket(s, begin, '[', ']'));
        } else if (s[begin] == 't' || s[begin] == 'f') {
            return ParseBool(s, begin, end);
        } else if (s[begin] == 'n') {
            return ParseNull(s, begin, end);
        } else if (s[begin] == '"') {
            return ParseString(s, begin + 1, end - 1);
        } else {
            return ParseNumber(s, begin, end);
        }
    }

    std::string JsonParser::Preprocess(const std::string &s) {
        std::string result;
        auto in_literal = false;
        for (size_t i = 0; i < s.size(); ++i) {
            if (s[i] == '"' && (!i || s[i - 1] != '\\')) {
                in_literal = !in_literal;
            }
            if (in_literal) {
                result.push_back(s[i]);
            } else if (!IsWhitespace(s[i])) {
                result.push_back(s[i]);
            }
        }
        return result;
    }

    JsonParser::JsonParser(bjson::JsonParserSettings settings) : settings_(settings) {
    }

    JsonObject JsonParser::Parse(const std::string &s) {
        std::string preprocessed_s = Preprocess(s);
        return ParseValue(preprocessed_s, 0, preprocessed_s.size());
    }

    JsonObject JsonParser::ParseFile(const std::string &filepath) {
        std::ifstream file;
        file.open(filepath);
        std::stringstream s;
        s << file.rdbuf();
        return Parse(s.str());
    }
}