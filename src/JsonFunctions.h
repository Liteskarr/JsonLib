#ifndef JSONPARSER_JSONFUNCTIONS_H
#define JSONPARSER_JSONFUNCTIONS_H

#include <optional>
#include "JsonObject.h"
#include "JsonParser.h"
#include "JsonFormatter.h"
#include "JsonParserSettings.h"
#include "JsonFormatterSettings.h"

namespace bjson {
    JsonObject ParseString(const std::string &s, JsonParserSettings settings = JsonParserSettings());

    JsonObject ParseFile(const std::string& filename, JsonParserSettings settings = JsonParserSettings());

    std::string ToString(JsonObject obj, JsonFormatterSettings settings = JsonFormatterSettings());

    void SaveToFile(const std::string& filename, JsonObject obj, JsonFormatterSettings = JsonFormatterSettings());
}

#endif