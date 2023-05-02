#include <Json.h>
#include <gtest/gtest.h>

using bjson::JsonObject;
using bjson::ToString;

TEST(FormatTests, PrettyObjectFormatTest1) {
    const std::string expected_string = "{\n"
                                        "    \"hello\": 32,\n"
                                        "    \"key\": [\n"
                                        "        1,\n"
                                        "        2\n"
                                        "    ],\n"
                                        "    \"world\": \"string\"\n"
                                        "}";
    const int32_t int1 = 32;
    auto obj = JsonObject::MakeObject();
    auto &obj_map = obj.AsObject();
    obj_map["hello"] = JsonObject::MakeInt(int1);
    obj_map["world"] = JsonObject::MakeString("string");
    obj_map["key"] = JsonObject::MakeArray(*new std::vector<JsonObject>{
            JsonObject::MakeInt(1),
            JsonObject::MakeInt(2)
    });
    ASSERT_EQ(ToString(obj, {.PrettyFormat = true}), expected_string);
}

TEST(FormatTests, NonPrettyObjectFormatTest1) {
    const std::string expected_string = "{\"hello\":32,\"world\":\"string\"}";
    const int32_t int1 = 32;
    auto obj = JsonObject::MakeObject();
    auto &obj_map = obj.AsObject();
    obj_map["hello"] = JsonObject::MakeInt(int1);
    obj_map["world"] = JsonObject::MakeString("string");
    ASSERT_EQ(ToString(obj, {.PrettyFormat = false}), expected_string);
}

TEST(FormatTests, PrettyArrayFormatTest1) {
    const std::string expected_string = "[\n"
                                        "    1,\n"
                                        "    null,\n"
                                        "    {\n"
                                        "        \"hello\": \"world\"\n"
                                        "    },\n"
                                        "    false,\n"
                                        "    \"text\"\n"
                                        "]";
    std::vector<JsonObject> v = {
            JsonObject::MakeInt(1ll),
            JsonObject::MakeNull(),
            JsonObject::MakeObject(*new std::map<std::string, JsonObject>{
                    {"hello", JsonObject::MakeString("world")}
            }),
            JsonObject::MakeBool(false),
            JsonObject::MakeString("text")
    };
    auto obj = JsonObject::MakeArray(v);
    ASSERT_EQ(ToString(obj, {.PrettyFormat = true}), expected_string);
}

TEST(FormatTests, NonPrettyArrayFromatTest1) {
    const std::string expected_string = "[1,null,{\"hello\":\"world\"},false,\"text\"]";
    std::vector<JsonObject> v = {
            JsonObject::MakeInt(1ll),
            JsonObject::MakeNull(),
            JsonObject::MakeObject(*new std::map<std::string, JsonObject>{
                    {"hello", JsonObject::MakeString("world")}
            }),
            JsonObject::MakeBool(false),
            JsonObject::MakeString("text")
    };
    auto obj = JsonObject::MakeArray(v);
    ASSERT_EQ(ToString(obj, {.PrettyFormat = false}), expected_string);
}