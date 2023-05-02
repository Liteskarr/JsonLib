cmake_minimum_required(VERSION 3.23)
project(JsonLib VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)

# #######
# LIBRARY
# #######
add_library(JsonLib STATIC
        src/JsonException.cpp
        src/JsonObject.cpp
        src/JsonParser.cpp
        src/JsonFormatter.cpp
        src/JsonFunctions.cpp)
set_target_properties(JsonLib PROPERTIES PREFIX "")
set_target_properties(JsonLib PROPERTIES OUTPUT_NAME "bjson")
set_target_properties(JsonLib PROPERTIES SUFFIX ".lib")
file(COPY src/Json.h DESTINATION ../include/Json)
file(COPY src/JsonException.h DESTINATION ../include/Json)
file(COPY src/JsonFormatter.h DESTINATION ../include/Json)
file(COPY src/JsonFormatterSettings.h DESTINATION ../include/Json)
file(COPY src/JsonFunctions.h DESTINATION ../include/Json)
file(COPY src/JsonObject.h DESTINATION ../include/Json)
file(COPY src/JsonParser.h DESTINATION ../include/Json)
file(COPY src/JsonParserSettings.h DESTINATION ../include/Json)

# #####
# TESTS
# #####
option(WITH_TESTS "Includes tests in building" No)

if (${WITH_TESTS})
    enable_testing()
    add_subdirectory(tests)
endif ()