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
#include "JsonException.h"

namespace bjson {
    enum JsonObjectType {
        Null,
        Int,
        Bool,
        Real,
        String,
        Array,
        Object
    };

    class JsonObject {
    private:
        JsonObjectType type_;

        union Container {
            double *real_ = nullptr;
            bool *boolean_;
            int64_t *int_;
            std::string *string_;
            std::vector<JsonObject> *array_;
            std::map<std::string, JsonObject> *object_;
        } container_;

    public:
        JsonObject();

        explicit JsonObject(JsonObjectType type);

        JsonObject(bool x);

        JsonObject(double x);

        JsonObject(int64_t x);

        JsonObject(const std::string_view &s);

        [[nodiscard]]
        bool IsNull() const;

        [[nodiscard]]
        bool IsInt() const;

        [[nodiscard]]
        bool IsReal() const;

        [[nodiscard]]
        bool IsBool() const;

        [[nodiscard]]
        bool IsString() const;

        [[nodiscard]]
        bool IsObject() const;

        [[nodiscard]]
        bool IsArray() const;

        [[nodiscard]]
        int64_t &AsInt() const;

        [[nodiscard]]
        double &AsReal() const;

        [[nodiscard]]
        bool &AsBool() const;

        [[nodiscard]]
        std::string &AsString() const;

        [[nodiscard]]
        std::vector<JsonObject> &AsArray() const;

        [[nodiscard]]
        std::map<std::string, JsonObject> &AsObject() const;

        [[nodiscard]]
        JsonObject &operator[](size_t key) const;

        [[nodiscard]]
        JsonObject &operator[](const std::string &key) const;

        ~JsonObject();
    };
}

#endif
