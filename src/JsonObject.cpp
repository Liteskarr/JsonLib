#include "JsonObject.h"

namespace bjson {
    JsonObject::JsonObject() : type_(JsonObjectType::Null) {
    }

    JsonObject::JsonObject(JsonObjectType type) : type_(type) {
        if (type == JsonObjectType::Bool) {
            container_.boolean_ = new bool(false);
        } else if (type_ == JsonObjectType::Int) {
            container_.int_ = new int64_t(0);
        } else if (type_ == JsonObjectType::Real) {
            container_.real_ = new double(0);
        } else if (type_ == JsonObjectType::String) {
            container_.string_ = new std::string();
        } else if (type_ == JsonObjectType::Array) {
            container_.array_ = new std::vector<JsonObject>();
        } else if (type_ == JsonObjectType::Object) {
            container_.object_ = new std::map<std::string, JsonObject>();
        }
    }

    JsonObject::JsonObject(bool x) : type_(JsonObjectType::Bool) {
        container_.boolean_ = new bool(x);
    }

    JsonObject::JsonObject(double x) : type_(JsonObjectType::Real) {
        container_.real_ = new double(x);
    }

    JsonObject::JsonObject(int64_t x) : type_(JsonObjectType::Int) {
        container_.int_ = new int64_t(x);
    }

    JsonObject::JsonObject(const std::string_view &s) : type_(JsonObjectType::String) {
        container_.string_ = new std::string(s.begin(), s.end());
    }

    bool JsonObject::IsNull() const {
        return type_ == JsonObjectType::Null;
    }

    bool JsonObject::IsInt() const {
        return type_ == JsonObjectType::Int;
    }

    bool JsonObject::IsReal() const {
        return type_ == JsonObjectType::Real;
    }

    bool JsonObject::IsBool() const {
        return type_ == JsonObjectType::Bool;
    }

    bool JsonObject::IsString() const {
        return type_ == JsonObjectType::String;
    }

    bool JsonObject::IsArray() const {
        return type_ == JsonObjectType::Array;
    }

    bool JsonObject::IsObject() const {
        return type_ == JsonObjectType::Object;
    }

    int64_t &JsonObject::AsInt() const {
        if (!IsInt()) {
            throw JsonException("JsonObject must be integer type!");
        }
        return *container_.int_;
    }

    double &JsonObject::AsReal() const {
        if (!IsReal()) {
            throw JsonException("JsonObject must be real type!");
        }
        return *container_.real_;
    }

    bool &JsonObject::AsBool() const {
        if (!IsBool()) {
            throw JsonException("JsonObject must be boolean type!");
        }
        return *container_.boolean_;
    }

    std::string &JsonObject::AsString() const {
        if (!IsString()) {
            throw JsonException("JsonObject must be string type!");
        }
        return *container_.string_;
    }

    std::vector<JsonObject> &JsonObject::AsArray() const {
        if (!IsArray()) {
            throw JsonException("JsonObject must be array type!");
        }
        return *container_.array_;
    }

    std::map<std::string, JsonObject> &JsonObject::AsObject() const {
        if (!IsObject()) {
            throw JsonException("JsonObject must be object type!");
        }
        return *container_.object_;
    }

    JsonObject &JsonObject::operator[](size_t key) const {
        if (!IsArray()) {
            throw JsonException("JsonObject must be array type!");
        }
        if (key < container_.array_->size()) {
            return (*container_.array_)[key];
        } else {
            throw JsonException("JsonObject's index out of range!");
        }
    }

    JsonObject &JsonObject::operator[](const std::string &key) const {
        if (!IsObject()) {
            throw JsonException("JsonObject must be object type!");
        }
        auto it = container_.object_->find(key);
        if (it != container_.object_->end()) {
            return it->second;
        } else {
            throw JsonException("JsonObject does not contains key!");
        }
    }

    JsonObject::~JsonObject() {
        if (type_ == JsonObjectType::Int) {
            delete container_.int_;
        } else if (type_ == JsonObjectType::Bool) {
            delete container_.boolean_;
        } else if (type_ == JsonObjectType::Real) {
            delete container_.real_;
        } else if (type_ == JsonObjectType::String) {
            delete container_.string_;
        } else if (type_ == JsonObjectType::Array) {
            delete container_.array_;
        } else if (type_ == JsonObjectType::Object) {
            delete container_.object_;
        }
    }
}