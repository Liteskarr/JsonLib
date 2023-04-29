add_executable(
        JsonLibTests
        ObjectTests.cpp
        ParseTests.cpp
)
target_link_libraries(JsonLibTests PRIVATE GTest::GTest JsonLib)
target_include_directories(JsonLibTests PRIVATE ../src/)

add_test(ObjectTests JsonLibTests)
add_test(ParseTests JsonLibTests)
