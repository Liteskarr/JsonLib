#include "JsonObject.h"

namespace bjson {
    JsonObject::JsonObject() : _type(JsonObjectType::Null) {
    }

    JsonObject::JsonObject(bool x) : _type(JsonObjectType::Bool) {
        _container._boolean = x;
    }

    JsonObject::JsonObject(double x) : _type(JsonObjectType::Real) {
        _container._real = x;
    }

    JsonObject::JsonObject(int64_t x) : _type(JsonObjectType::Int) {
        _container._int = x;
    }

    JsonObject::JsonObject(const std::string_view &s) : _type(JsonObjectType::String) {
        _container._string = new std::string(s.begin(), s.end());
    }

    bool JsonObject::is_null() const {
        return _type == JsonObjectType::Null;
    }

    bool JsonObject::is_int() const {
        return _type == JsonObjectType::Int;
    }

    bool JsonObject::is_real() const {
        return _type == JsonObjectType::Real;
    }

    bool JsonObject::is_bool() const {
        return _type == JsonObjectType::Bool;
    }

    bool JsonObject::is_string() const {
        return _type == JsonObjectType::String;
    }

    bool JsonObject::is_array() const {
        return _type == JsonObjectType::Array;
    }

    bool JsonObject::is_object() const {
        return _type == JsonObjectType::Object;
    }

    int64_t& JsonObject::as_int() {
        if (!is_int()) {
            throw JsonException("JsonObject must be integer type!");
        }
        return _container._int;
    }

    double& JsonObject::as_real() {
        if (!is_real()) {
            throw JsonException("JsonObject must be real type!");
        }
        return _container._real;
    }

    bool& JsonObject::as_bool() {
        if (!is_bool()) {
            throw JsonException("JsonObject must be boolean type!");
        }
        return _container._boolean;
    }

    std::string& JsonObject::as_string() {
        if (!is_string()) {
            throw JsonException("JsonObject must be string type!");
        }
        return *_container._string;
    }
}