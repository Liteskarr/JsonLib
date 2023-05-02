#include "JsonException.h"

namespace bjson {
    JsonException::JsonException() : message_("Json exception!") {
    }

    JsonException::JsonException(const std::string_view &message) : message_(message) {
    }

    const char *JsonException::what() const noexcept {
        return message_.c_str();
    }
}