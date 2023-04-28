#ifndef JSONPARSER_JSONFORMATSETTINGS_H
#define JSONPARSER_JSONFORMATSETTINGS_H

#include <cstdint>

namespace bjson {
    class JsonFormatterSettings {
    public:
        bool PrettyFormat = false;
        size_t TabSize = 4;
    };
}

#endif
