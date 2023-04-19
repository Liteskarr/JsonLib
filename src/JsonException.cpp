#include "JsonException.h"

JsonException::JsonException() : _message("Json exception!") {
}

JsonException::JsonException(const std::string_view &message) : _message(message) {
}

const char *JsonException::what() const noexcept {
    return _message.c_str();
}
