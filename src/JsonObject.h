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
        JsonObjectType _type;

        union Container {
            double *_real = nullptr;
            bool *_boolean;
            int64_t *_int;
            std::string *_string;
            std::vector <JsonObject> *_array;
            std::map <std::string, JsonObject> *_object;
        } _container;

    public:
        JsonObject();

        explicit JsonObject(JsonObjectType type);

        JsonObject(bool x);

        JsonObject(double x);

        JsonObject(int64_t x);

        JsonObject(const std::string_view &s);

        [[nodiscard]]
        bool is_null() const;

        [[nodiscard]]
        bool is_int() const;

        [[nodiscard]]
        bool is_real() const;

        [[nodiscard]]
        bool is_bool() const;

        [[nodiscard]]
        bool is_string() const;

        [[nodiscard]]
        bool is_object() const;

        [[nodiscard]]
        bool is_array() const;

        [[nodiscard]]
        int64_t &as_int() const;

        [[nodiscard]]
        double &as_real() const;

        [[nodiscard]]
        bool &as_bool() const;

        [[nodiscard]]
        std::string &as_string() const;

        [[nodiscard]]
        std::vector <JsonObject> &as_array() const;

        [[nodiscard]]
        std::map <std::string, JsonObject> &as_object() const;

        [[nodiscard]]
        JsonObject &operator[](size_t key) const;

        [[nodiscard]]
        JsonObject &operator[](const std::string &key) const;

        ~JsonObject();
    };
}

#endif
