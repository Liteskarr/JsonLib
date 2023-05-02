#ifndef JSONPARSER_JSONPARSERSETTINGS_H
#define JSONPARSER_JSONPARSERSETTINGS_H

#include <vector>

namespace bjson {
    class JsonParserSettings {
    public:
        /// Setting for loading all numbers as real
        bool AllNumbersAsReal = false;
    };
}

#endif