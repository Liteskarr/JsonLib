#ifndef JSONPARSER_JSONOBJECT_H
#define JSONPARSER_JSONOBJECT_H

#include <map>
#include <vector>
#include <string>
#include <string_view>
#include <cstdint>
#include <cstdbool>
#include <cstdlib>
#include "ObjectContainer.h"
#include "ArrayContainer.h"
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
            double _real;
            bool _boolean;
            int64_t _int = 0;
            std::string *_string;
            ObjectContainer *_object;
            ArrayContainer *_array;
        } _container;

    public:
        JsonObject();

        JsonObject(bool x);

        JsonObject(double x);

        JsonObject(int64_t x);

        JsonObject(const std::string_view &s);

        bool is_null() const;

        bool is_int() const;

        bool is_real() const;

        bool is_bool() const;

        bool is_string() const;

        bool is_object() const;

        bool is_array() const;

        int64_t& as_int();

        double& as_real();

        bool& as_bool();

        std::string& as_string();
    };
}

#endif
