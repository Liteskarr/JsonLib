#include "JsonObject.h"

namespace bjson {
    JsonObject::JsonObject() : _type(JsonObjectType::Null) {
    }

    JsonObject::JsonObject(JsonObjectType type) : _type(type) {
        if (_type == JsonObjectType::Bool) {
            _container._boolean = new bool(false);
        } else if (_type == JsonObjectType::Int) {
            _container._int = new int64_t(0);
        } else if (_type == JsonObjectType::Real) {
            _container._real = new double(0);
        } else if (_type == JsonObjectType::String) {
            _container._string = new std::string();
        } else if (_type == JsonObjectType::Array) {
            _container._array = new std::vector<JsonObject>();
        } else if (_type == JsonObjectType::Object) {
            _container._object = new std::map<std::string, JsonObject>();
        }
    }

    JsonObject::JsonObject(bool x) : _type(JsonObjectType::Bool) {
        _container._boolean = new bool(x);
    }

    JsonObject::JsonObject(double x) : _type(JsonObjectType::Real) {
        _container._real = new double(x);
    }

    JsonObject::JsonObject(int64_t x) : _type(JsonObjectType::Int) {
        _container._int = new int64_t(x);
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

    int64_t &JsonObject::as_int() const {
        if (!is_int()) {
            throw JsonException("JsonObject must be integer type!");
        }
        return *_container._int;
    }

    double &JsonObject::as_real() const {
        if (!is_real()) {
            throw JsonException("JsonObject must be real type!");
        }
        return *_container._real;
    }

    bool &JsonObject::as_bool() const {
        if (!is_bool()) {
            throw JsonException("JsonObject must be boolean type!");
        }
        return *_container._boolean;
    }

    std::string &JsonObject::as_string() const {
        if (!is_string()) {
            throw JsonException("JsonObject must be string type!");
        }
        return *_container._string;
    }

    std::vector <JsonObject> &JsonObject::as_array() const {
        if (!is_array()) {
            throw JsonException("JsonObject must be array type!");
        }
        return *_container._array;
    }

    std::map <std::string, JsonObject> &JsonObject::as_object() const {
        if (!is_object()) {
            throw JsonException("JsonObject must be object type!");
        }
        return *_container._object;
    }

    JsonObject &JsonObject::operator[](size_t key) const {
        if (!is_array()) {
            throw JsonException("JsonObject must be array type!");
        }
        if (key < _container._array->size()) {
            return (*_container._array)[key];
        } else {
            throw JsonException("JsonObject's index out of range!");
        }
    }

    JsonObject &JsonObject::operator[](const std::string &key) const {
        if (!is_object()) {
            throw JsonException("JsonObject must be object type!");
        }
        auto it = _container._object->find(key);
        if (it != _container._object->end()) {
            return it->second;
        } else {
            throw JsonException("JsonObject does not contains key!");
        }
    }

    JsonObject::~JsonObject() {
        if (_type == JsonObjectType::Int) {
            delete _container._int;
        } else if (_type == JsonObjectType::Bool) {
            delete _container._boolean;
        } else if (_type == JsonObjectType::Real) {
            delete _container._real;
        } else if (_type == JsonObjectType::String) {
            delete _container._string;
        } else if (_type == JsonObjectType::Array) {
            delete _container._array;
        } else if (_type == JsonObjectType::Object){
            delete _container._object;
        }
    }
}