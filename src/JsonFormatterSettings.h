#ifndef JSONPARSER_JSONFORMATSETTINGS_H
#define JSONPARSER_JSONFORMATSETTINGS_H

#include <cstdint>

namespace bjson {
    /// Settings for JsonFormatter
    class JsonFormatterSettings {
    public:
        /// Enable pretty format
        bool PrettyFormat = false;
        /// Count of spaces by depth
        size_t TabSize = 4;
    };
}

#endif
