#include "../src/JsonObject.h"
#include <gtest/gtest.h>

TEST(Test, NullJsonObjectTest) {
    bjson::JsonObject obj;
    ASSERT_EQ(obj.is_null(), true);
}