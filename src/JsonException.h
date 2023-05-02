#ifndef JSONPARSER_JSONEXCEPTION_H
#define JSONPARSER_JSONEXCEPTION_H

#include <string>
#include <string_view>
#include <exception>

namespace bjson {
    /// Base exception for JsonLib
    class JsonException : std::exception {
    private:
        std::string message_;

    public:
        JsonException();

        explicit JsonException(const std::string_view &message);

        const char *what() const noexcept override;
    };
}


#endif