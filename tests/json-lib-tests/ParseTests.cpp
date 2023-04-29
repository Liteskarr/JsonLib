#include <Json.h>
#include <gtest/gtest.h>

using bjson::JsonObject;
using bjson::ParseString;
using bjson::ParseFile;

TEST(ParseTests, ParseTest1) {
    const std::string json_string = "{\"hello\":1}";
    auto obj = ParseString(json_string);
    ASSERT_EQ(obj.IsObject(), true);
    ASSERT_EQ(obj["hello"].IsInt(), true);
    ASSERT_EQ(obj["hello"].AsInt(), 1ll);
}

TEST(ParseTests, ParseTest2) {
    const std::string json_string = "[1, null, \"hello\", {\"world\":1}]";
    auto obj = ParseString(json_string);
    ASSERT_EQ(obj.IsArray(), true);
    ASSERT_EQ(obj[0].IsInt(), true);
    ASSERT_EQ(obj[0].AsInt(), 1ll);
    ASSERT_EQ(obj[1].IsNull(), true);
    ASSERT_EQ(obj[1], JsonObject::MakeNull());
    ASSERT_EQ(obj[2].IsString(), true);
    ASSERT_EQ(obj[2], JsonObject::MakeString("hello"));
    ASSERT_EQ(obj[3].IsObject(), true);
    ASSERT_EQ(obj[3]["world"].IsInt(), true);
    ASSERT_EQ(obj[3]["world"].AsInt(), 1ll);
}
