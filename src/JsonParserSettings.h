#ifndef JSONPARSER_JSONPARSERSETTINGS_H
#define JSONPARSER_JSONPARSERSETTINGS_H

#include <vector>

namespace bjson {
    class JsonParserSettings {
    public:
        JsonParserSettings();

        static JsonParserSettings GetDefault();
    };
}

#endif