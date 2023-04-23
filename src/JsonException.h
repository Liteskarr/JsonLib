#ifndef JSONPARSER_JSONEXCEPTION_H
#define JSONPARSER_JSONEXCEPTION_H

#include <string>
#include <string_view>
#include <exception>

namespace bjson {
    class JsonException : std::exception {
    private:
        std::string _message;

    public:
        JsonException();

        JsonException(const std::string_view &message);

        const char *what() const

        noexcept;
    };
}


#endif