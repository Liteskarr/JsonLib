#ifndef JSONPARSER_JSONFUNCTIONS_H
#define JSONPARSER_JSONFUNCTIONS_H

#include <optional>
#include "JsonObject.h"
#include "JsonParser.h"
#include "JsonFormatter.h"
#include "JsonParserSettings.h"
#include "JsonFormatterSettings.h"

namespace bjson {
    /// Returns JsonObject from json string
    /// @param s Raw json string
    /// @param settings Settings for parsing
    JsonObject ParseString(const std::string &s, JsonParserSettings settings = JsonParserSettings());

    /// Returns JsonObject from json file
    /// @param filename Path to json file
    /// @param settings Settings for parsing
    JsonObject ParseFile(const std::string& filename, JsonParserSettings settings = JsonParserSettings());

    /// Returns string representation of JsonObject
    /// @param obj JsonObject for representation
    /// @param settings Settings for formatting
    std::string ToString(JsonObject obj, JsonFormatterSettings settings = JsonFormatterSettings());

    /// Saves representation of JsonObject to file
    /// @param filename Path to file with result
    /// @param settings Settings for formatting
    void SaveToFile(const std::string& filename, JsonObject obj, JsonFormatterSettings settings = JsonFormatterSettings());
}

#endif