#ifndef JSONLIB_JSONFORMATTER_H
#define JSONLIB_JSONFORMATTER_H

#include <string>
#include <fstream>
#include "JsonObject.h"
#include "JsonFormatterSettings.h"

namespace bjson {
    class JsonFormatter {
        JsonFormatterSettings settings_;

        std::string JsonArrayToString(JsonObject obj, size_t depth = 0);

        std::string JsonObjectToString(JsonObject obj, size_t depth = 0);

    public:
        explicit JsonFormatter(JsonFormatterSettings settings = JsonFormatterSettings());

        std::string ToString(JsonObject obj, size_t depth = 0);

        void SaveToFile(const std::string& filename, JsonObject obj);
    };
}

#endif
