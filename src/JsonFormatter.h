#ifndef JSONLIB_JSONFORMATTER_H
#define JSONLIB_JSONFORMATTER_H

#include <string>
#include <fstream>
#include "JsonObject.h"
#include "JsonFormatterSettings.h"

namespace bjson {
    /// Class for JsonObject's formatting
    class JsonFormatter {
        /// Settings of formatter
        JsonFormatterSettings settings_;

        /// Returns string representation of json array
        /// @param obj Json array
        /// @param depth Depth for pretty format
        std::string JsonArrayToString(JsonObject obj, size_t depth = 0);

        /// Returns string representation of json object
        /// @param obj Json object
        /// @param depth Depth for pretty format
        std::string JsonObjectToString(JsonObject obj, size_t depth = 0);

    public:
        /// @param settings Settings of formatter
        explicit JsonFormatter(JsonFormatterSettings settings = JsonFormatterSettings());

        /// Returns string representation of JsonObject
        /// @param obj JsonObject for representation
        /// @param depth Depth for pretty format
        std::string ToString(JsonObject obj, size_t depth = 0);

        /// Saves to file representation of JsonObject
        /// @param filename Path to file with result
        /// @param obj JsonObject for representation
        void SaveToFile(const std::string& filename, JsonObject obj);
    };
}

#endif
