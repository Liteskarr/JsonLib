#include "JsonFormatter.h"

namespace bjson {
    JsonFormatter::JsonFormatter(bjson::JsonFormatterSettings settings) : settings_(settings) {
    }

    std::string JsonFormatter::JsonArrayToString(bjson::JsonObject obj, size_t depth) {
        std::string result = "[";
        auto v = obj.AsArray();
        for (auto it = v.begin(); it != v.end(); ++it) {
            for (size_t i = 0; i < depth * settings_.TabSize && settings_.PrettyFormat; ++i) {
                result += ' ';
            }
            result += ToString(*it, depth + 1);
            if (it != v.end() - 1) {
                result += ',';
                if (settings_.PrettyFormat) {
                    result += '\n';
                }
            }
        }
        for (size_t i = 0; i < depth * settings_.TabSize && settings_.PrettyFormat; ++i) {
            result += ' ';
        }
        result += ']';
        return result;
    }

    std::string JsonFormatter::JsonObjectToString(bjson::JsonObject obj, size_t depth) {
        std::string result = "{";
        auto v = obj.AsObject();
        for (auto it = v.begin(); it != v.end(); ++it) {
            for (size_t i = 0; i < depth * settings_.TabSize && settings_.PrettyFormat; ++i) {
                result += ' ';
            }
            result += it->first;
            result += (settings_.PrettyFormat ? ": " : ":");
            result += ToString(it->second, depth + 1);
            if (it != prev(v.end())) {
                result += ',';
                if (settings_.PrettyFormat) {
                    result += '\n';
                }
            }
        }
        for (size_t i = 0; i < depth * settings_.TabSize && settings_.PrettyFormat; ++i) {
            result += ' ';
        }
        result += '}';
        return result;
    }

    std::string JsonFormatter::ToString(bjson::JsonObject obj, size_t depth) {
        std::string result;
        if (obj.IsNull()) {
            return "null";
        } else if (obj.IsBool()) {
            return obj.AsBool() ? "true" : "false";
        } else if (obj.IsInt()) {
            return std::to_string(obj.AsInt());
        } else if (obj.IsReal()) {
            return std::to_string(obj.AsReal());
        } else if (obj.IsString()) {
            return obj.AsString();
        } else if (obj.IsArray()) {
            return JsonArrayToString(obj, depth + 1);
        } else if (obj.IsObject()) {
            return JsonObjectToString(obj, depth + 1);
        }
        return result;
    }

    void JsonFormatter::SaveToFile(const std::string &filename, bjson::JsonObject obj) {
        std::ofstream file;
        file.open(filename);
        file << ToString(obj);
    }
}