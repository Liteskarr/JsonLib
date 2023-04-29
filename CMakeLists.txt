cmake_minimum_required(VERSION 3.23)
project(JsonLib VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)

# ######
# GLOBAL
# ######
include_directories(src)

# #######
# LIBRARY
# #######
add_library(JsonLib STATIC
        src/JsonException.cpp
        src/JsonObject.cpp
        src/JsonParser.cpp
        src/JsonFormatter.cpp
        src/JsonParserSettings.cpp
        src/JsonFormatterSettings.cpp
        src/JsonFunctions.cpp)
set_target_properties(JsonLib PROPERTIES PREFIX "")
set_target_properties(JsonLib PROPERTIES OUTPUT_NAME "bjson")
set_target_properties(JsonLib PROPERTIES SUFFIX ".lib")

# #####
# TESTS
# #####
option(WITH_TESTS "Includes tests in building" Yes)

if (${WITH_TESTS})
    enable_testing()
    add_subdirectory(tests)
endif ()