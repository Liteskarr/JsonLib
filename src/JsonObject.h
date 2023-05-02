#ifndef JSONPARSER_JSONOBJECT_H
#define JSONPARSER_JSONOBJECT_H

#include <map>
#include <vector>
#include <iterator>
#include <string>
#include <string_view>
#include <iomanip>
#include <cstdint>
#include <cstdbool>
#include <cstdlib>
#include <memory>
#include <variant>
#include "JsonException.h"

namespace bjson {
    class JsonObject;

    using JNull = std::nullptr_t;
    using JInt = std::shared_ptr<std::int64_t>;
    using JBool = std::shared_ptr<bool>;
    using JReal = std::shared_ptr<double>;
    using JString = std::shared_ptr<std::string>;
    using JArray = std::shared_ptr<std::vector<JsonObject>>;
    using JObject = std::shared_ptr<std::map<std::string, JsonObject>>;

    /// JsonObject as class representation
    class JsonObject {
    private:
        std::variant<JNull, JInt, JReal, JBool, JString, JArray, JObject> container_;

    public:
        /// Returns null JsonObject
        static JsonObject MakeNull();

        /// Returns int JsonObject
        /// @param x Value of int JsonObject
        static JsonObject MakeInt(int32_t x);

        /// Returns int JsonObject
        /// @param x Value of int JsonObject
        static JsonObject MakeInt(int64_t x);

        /// Returns real JsonObject
        /// @param x Value of real JsonObject
        static JsonObject MakeReal(double x);

        /// Returns bool JsonObject
        /// @param x Value of bool JsonObject
        static JsonObject MakeBool(bool x);

        /// Returns string JsonObject
        /// @param s Value of string JsonObject
        static JsonObject MakeString(const std::string &s);

        /// Returns empty json array
        static JsonObject MakeArray();

        /// Returns json array by input vector of JsonObjects
        /// @param v Input vector of JsonObjects
        static JsonObject MakeArray(std::vector<JsonObject> v);

        /// Returns empty json object
        static JsonObject MakeObject();

        /// Returns json object by input map of pairs of strings and JsonObjects
        /// @param m Input map of pairs of strings and JsonObjects
        static JsonObject MakeObject(std::map<std::string, JsonObject> m);

        /// Checks what JsonObject contains null
        /// @return true if contains null else false
        bool IsNull() const;

        /// Checks what JsonObject contains int
        /// @return true if contains int else false
        bool IsInt() const;

        /// Checks what JsonObject contains real
        /// @return true if contains real else false
        bool IsReal() const;

        /// Checks what JsonObject contains bool
        /// @return true if contains bool else false
        bool IsBool() const;

        /// Checks what JsonObject contains string
        /// @return true if contains string else false
        bool IsString() const;

        /// Checks what JsonObject contains object
        /// @return true if contains object else false
        bool IsObject() const;

        /// Checks what JsonObject contains array
        /// @return true if contains array else false
        bool IsArray() const;

        /// Returns reference to content int
        int64_t &AsInt() const;

        /// Returns reference to content real
        double &AsReal() const;

        /// Returns reference to content bool
        bool &AsBool() const;

        /// Returns reference to content string
        std::string &AsString() const;

        /// Returns reference to content array as vector of JsonObjects
        std::vector<JsonObject> &AsArray() const;

        /// Returns reference to content object as map of pairs of strings and JsonObjects
        std::map<std::string, JsonObject> &AsObject() const;

        /// Returns reference to JsonObject by index 'key' in json array
        JsonObject &operator[](size_t key) const;

        /// Returns reference to JsonObject by string 'key; in json object
        JsonObject &operator[](const std::string &key) const;

        JsonObject &operator=(const JsonObject &other);

        bool operator==(const JsonObject &other) const;
    };
}

#endif
