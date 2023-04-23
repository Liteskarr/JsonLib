#include "JsonParserStateMachine.h"

namespace bjson::utils {
    static bool is_json_whitespace(char c) {
        return c == ' ' || c == '\n' || c == '\t' || c == '\r';
    }

    JsonParserStateMachine::JsonParserStateMachine(JsonParserSettings settings) : _settings(settings) {
        _states = std::stack<JsonParserStateMachineStates>();
        _states.push(JsonParserStateMachineStates::Init);
    }

    void JsonParserStateMachine::_add_char_init(char c) {
        if (is_json_whitespace(c)) {
            return;
        } else if (c == '{') {
            _states.push(JsonParserStateMachineStates::Object);
        } else if (c == '[') {
            _states.push(JsonParserStateMachineStates::Array);
        } else {
            _exceptionString = "Unexpected symbol at!";
        }
    }

    void JsonParserStateMachine::add_char(char c) {
        if (has_error()) {
            throw JsonException(_exceptionString);
        }
        JsonParserStateMachineStates state = _states.top();
        if (state == JsonParserStateMachineStates::Init) {
            _add_char_init(c);
        } else if (state == JsonParserStateMachineStates::NumberSign ||
                   state == JsonParserStateMachineStates::NumberBody ||
                   state == JsonParserStateMachineStates::NumberFraction ||
                   state == JsonParserStateMachineStates::NumberExponent) {
            _add_char_number(c);
        }
        _line_index++;
        if (c == '\n') {
            _line_index = 1;
            _line_count++;
        }
    }

    bool JsonParserStateMachine::has_error() const {
        return !_exceptionString.empty();
    }
}