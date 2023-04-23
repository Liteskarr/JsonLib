cmake_minimum_required(VERSION 3.23)
project(JsonParser VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)

include_directories(src)

include(FetchContent)

add_library(JsonParser STATIC
        src/JsonException.cpp
        src/JsonObject.cpp
        src/JsonParser.cpp
        src/JsonParserSettings.cpp
        src/utils/JsonParserStateMachine.cpp)

option(COMPILE_TESTS "Compile lib's tests" False)
if (${COMPILE_TESTS})
    enable_testing()
    add_subdirectory(tests)
endif ()
