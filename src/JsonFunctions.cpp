#include "JsonFunctions.h"

namespace bjson {
    JsonObject ParseString(const std::string &s, JsonParserSettings settings) {
        auto parser = JsonParser(settings);
        return parser.Parse(s);
    }

    JsonObject ParseFile(const std::string& filename, JsonParserSettings settings) {
        auto parser = JsonParser(settings);
        return parser.ParseFile(filename);
    }

    std::string ToString(JsonObject obj, JsonFormatterSettings settings) {
        auto formatter = JsonFormatter(settings);
        return formatter.ToString(obj);
    }

    void SaveToFile(const std::string& filename, JsonObject obj, JsonFormatterSettings settings) {
        auto formatter = JsonFormatter(settings);
        formatter.SaveToFile(filename, obj);
    }
}