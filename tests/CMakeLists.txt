include(FetchContent)

FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.13.0
)
FetchContent_MakeAvailable(googletest)
add_library(GTest::GTest INTERFACE IMPORTED)
target_link_libraries(GTest::GTest INTERFACE gtest_main)

add_executable(bjson_tests BjsonTests.cpp)
target_link_libraries(bjson_tests PRIVATE GTest::GTest JsonParser)

add_test(bjson_gtests bjson_tests)
