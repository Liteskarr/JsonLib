#include "JsonObject.h"

namespace bjson {
    JsonObject JsonObject::MakeNull() {
        JsonObject obj;
        obj.container_ = nullptr;
        return obj;
    }

    JsonObject JsonObject::MakeBool(bool x) {
        JsonObject obj;
        obj.container_ = std::make_shared<bool>(x);
        return obj;
    }

    JsonObject JsonObject::MakeInt(int64_t x) {
        JsonObject obj;
        obj.container_ = std::make_shared<int64_t>(x);
        return obj;
    }

    JsonObject JsonObject::MakeReal(double x) {
        JsonObject obj;
        obj.container_ = std::make_shared<double>(x);
        return obj;
    }

    JsonObject JsonObject::MakeString(const std::string &s) {
        JsonObject obj;
        obj.container_ = std::make_shared<std::string>(s);
        return obj;
    }

    JsonObject JsonObject::MakeArray() {
        JsonObject obj;
        obj.container_ = std::make_shared<std::vector<JsonObject>>();
        return obj;
    }

    JsonObject JsonObject::MakeArray(std::vector<JsonObject> &v) {
        JsonObject obj;
        obj.container_ = std::make_shared<std::vector<JsonObject>>(v);
        return obj;
    }

    JsonObject JsonObject::MakeObject() {
        JsonObject obj;
        obj.container_ = std::make_shared<std::map<std::string, JsonObject>>();
        return obj;
    }

    JsonObject JsonObject::MakeObject(std::map<std::string, JsonObject> &m) {
        JsonObject obj;
        obj.container_ = std::make_shared<std::map<std::string, JsonObject>>(m);
        return obj;
    }

    bool JsonObject::IsNull() const {
        return std::holds_alternative<JNull>(container_);
    }

    bool JsonObject::IsInt() const {
        return std::holds_alternative<JInt>(container_);
    }

    bool JsonObject::IsReal() const {
        return std::holds_alternative<JReal>(container_);
    }

    bool JsonObject::IsBool() const {
        return std::holds_alternative<JBool>(container_);
    }

    bool JsonObject::IsString() const {
        return std::holds_alternative<JString>(container_);
    }

    bool JsonObject::IsArray() const {
        return std::holds_alternative<JArray>(container_);
    }

    bool JsonObject::IsObject() const {
        return std::holds_alternative<JObject>(container_);
    }

    int64_t &JsonObject::AsInt() const {
        if (!IsInt()) {
            throw JsonException("JsonObject must be integer type!");
        }
        return *std::get<JInt>(container_);
    }

    double &JsonObject::AsReal() const {
        if (!IsReal()) {
            throw JsonException("JsonObject must be real type!");
        }
        return *std::get<JReal>(container_);
    }

    bool &JsonObject::AsBool() const {
        if (!IsBool()) {
            throw JsonException("JsonObject must be boolean type!");
        }
        return *std::get<JBool>(container_);
    }

    std::string &JsonObject::AsString() const {
        if (!IsString()) {
            throw JsonException("JsonObject must be string type!");
        }
        return *std::get<JString>(container_);
    }

    std::vector<JsonObject> &JsonObject::AsArray() const {
        if (!IsArray()) {
            throw JsonException("JsonObject must be array type!");
        }
        return *std::get<JArray>(container_);
    }

    std::map<std::string, JsonObject> &JsonObject::AsObject() const {
        if (!IsObject()) {
            throw JsonException("JsonObject must be object type!");
        }
        return *std::get<JObject>(container_);
    }

    JsonObject &JsonObject::operator[](size_t key) const {
        if (!IsArray()) {
            throw JsonException("JsonObject must be array type!");
        }
        auto& obj = AsArray();
        if (key < obj.size()) {
            return obj[key];
        } else {
            throw JsonException("JsonObject's index out of range!");
        }
    }

    JsonObject &JsonObject::operator[](const std::string &key) const {
        if (!IsObject()) {
            throw JsonException("JsonObject must be object type!");
        }
        auto& obj = AsObject();
        auto it = obj.find(key);
        if (it != obj.end()) {
            return it->second;
        } else {
            throw JsonException("JsonObject does not contains key!");
        }
    }

    JsonObject &JsonObject::operator=(const bjson::JsonObject &other) {
        if (this == &other) {
            return *this;
        }
        this->container_ = other.container_;
        return *this;
    }
}