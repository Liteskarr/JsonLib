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

    class JsonObject {
    private:
        std::variant<JNull, JInt, JReal, JBool, JString, JArray, JObject> container_;

    public:
        static JsonObject MakeNull();

        static JsonObject MakeInt(int64_t x);

        static JsonObject MakeReal(double x);

        static JsonObject MakeBool(bool x);

        static JsonObject MakeString(const std::string &s);

        static JsonObject MakeArray();

        static JsonObject MakeArray(std::vector<JsonObject>& v);

        static JsonObject MakeObject();

        static JsonObject MakeObject(std::map<std::string, JsonObject> &m);

        bool IsNull() const;

        bool IsInt() const;

        bool IsReal() const;

        bool IsBool() const;

        bool IsString() const;

        bool IsObject() const;

        bool IsArray() const;

        int64_t &AsInt() const;

        double &AsReal() const;

        bool &AsBool() const;

        std::string &AsString() const;

        std::vector<JsonObject> &AsArray() const;

        std::map<std::string, JsonObject> &AsObject() const;

        JsonObject &operator[](size_t key) const;

        JsonObject &operator[](const std::string &key) const;

        JsonObject& operator=(const JsonObject& other);
    };
}

#endif
