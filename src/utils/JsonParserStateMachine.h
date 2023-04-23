#ifndef JSONPARSER_JSONPARSERSTATEMACHINE_H
#define JSONPARSER_JSONPARSERSTATEMACHINE_H

#include "../JsonObject.h"
#include "../JsonParserSettings.h"
#include <stack>

namespace bjson::utils {
    enum JsonParserStateMachineStates {
        Init,
        Object,
        Array,
        String,
        NumberSign,
        NumberBody,
        NumberFraction,
        NumberExponent,
        Null_n,
        Null_u,
        Null_l1,
        Null_l2,
    };

    class JsonParserStateMachine {
    private:
        JsonParserSettings _settings;

        JsonObject _result;

        uint32_t _line_count = 1;

        uint32_t _line_index = 1;

        std::string _exceptionString;

        std::stack<JsonParserStateMachineStates> _states;

        void _add_char_init(char c);

        void _add_char_null(char c);

        void _add_char_number(char c);

        void _add_char_string(char c);

        void _add_char_array(char c);

        void _add_char_object(char c);

    public:
        explicit JsonParserStateMachine(JsonParserSettings settings);

        void add_char(char c);

        bool is_ready_result() const;

        JsonObject get_result() const;

        bool has_error() const;

        std::string get_error() const;
    };

}

#endif
