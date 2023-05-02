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
        /// Settings of parser
        JsonParserSettings settings_;

        /// Checks what symbol is whitespace
        /// @param c Symbol for checking
        inline static bool IsWhitespace(char c);

        /// Find first non-literal closed bracket
        /// @param s String for searching
        /// @param begin Start of searching
        /// @param end Exclude end of searching
        /// @param opened Opened bracket
        /// @param closed Closed bracket
        inline static size_t FindCloseBracket(const std::string& s, size_t begin, size_t end, char opened, char closed);

        /// Returns JsonObject from string as null
        /// @param s String with null
        /// @param begin Start of null
        /// @param end Exclude end of null
        JsonObject ParseNull(const std::string &s, size_t begin, size_t end);

        /// Returns JsonObject from string as bool
        /// @param s String with bool
        /// @param begin Start of bool
        /// @param end Exclude end of bool
        JsonObject ParseBool(const std::string &s, size_t begin, size_t end);

        /// Returns JsonObject from string as int
        /// @param s String with int
        /// @param begin Start of int
        /// @param end Exclude end of int
        JsonObject ParseInt(const std::string& s, size_t begin, size_t end);

        /// Returns JsonObject from string as real
        /// @param s String with real
        /// @param begin Start of real
        /// @param end Exclude end of real
        JsonObject ParseReal(const std::string& s, size_t begin, size_t end);

        /// Returns JsonObject from string as int or real
        /// @param s String with int or real
        /// @param begin Start of int or real
        /// @param end Exclude end of int or real
        JsonObject ParseNumber(const std::string &s, size_t begin, size_t end);

        /// Returns JsonObject from string
        /// @param s String with string
        /// @param begin Start of string
        /// @param end Exclude end of string
        JsonObject ParseString(const std::string &s, size_t begin, size_t end);

        /// Returns JsonObject from string as array
        /// @param s String with array
        /// @param begin Start of array
        /// @param end Exclude end of array
        JsonObject ParseArray(const std::string &s, size_t begin, size_t end);

        /// Returns JsonObject from string as object
        /// @param s String with object
        /// @param begin Start of object
        /// @param end Exclude end of object
        JsonObject ParseObject(const std::string &s, size_t begin, size_t end);

        /// Returns JsonObject from string as value
        /// @param s String with value
        /// @param begin Start of value
        /// @param end Exclude end of value
        JsonObject ParseValue(const std::string &s, size_t begin, size_t end);

        /// Returns string without non-literal whitespaces
        /// @param s Input string
        std::string Preprocess(const std::string& s);

    public:
        /// @param settings Settings for parser
        explicit JsonParser(JsonParserSettings settings = JsonParserSettings());

        /// Returns string representation of JsonObject
        /// @param obj JsonObject for representation
        /// @param settings Settings for formatting
        JsonObject Parse(const std::string &s);

        /// Saves representation of JsonObject to file
        /// @param filename Path to file with result
        /// @param settings Settings for formatting
        JsonObject ParseFile(const std::string &filepath);
    };
}

#endif
