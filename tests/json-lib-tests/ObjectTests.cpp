#include <Json.h>
#include <gtest/gtest.h>

using bjson::JsonObject;

TEST(ObjectTests, ObjectBaseConstructor) {
    bjson::JsonObject obj;
    ASSERT_EQ(obj.IsNull(), true);
}

TEST(ObjectTests, ObjectMakeNull) {
    auto obj = JsonObject::MakeNull();
    ASSERT_EQ(obj.IsNull(), true);
}

TEST(ObjectTests, ObjectMakeInt) {
    const int64_t x = 32ll;
    const int64_t y = 64ll;
    auto obj = JsonObject::MakeInt(x);
    ASSERT_EQ(obj.IsInt(), true);
    ASSERT_EQ(obj.AsInt(), x);
    obj.AsInt() = y;
    ASSERT_EQ(obj.AsInt(), y);
}

TEST(ObjectTests, ObjectMakeReal) {
    const double x = 2.718281828;
    const double y = 3.1415628;
    auto obj = JsonObject::MakeReal(x);
    ASSERT_EQ(obj.IsReal(), true);
    ASSERT_EQ(obj.AsReal(), x);
    obj.AsReal() = y;
    ASSERT_EQ(obj.AsReal(), y);
}

TEST(ObjectTests, ObjectMakeBool) {
    auto obj = JsonObject::MakeBool(false);
    ASSERT_EQ(obj.IsBool(), true);
    ASSERT_EQ(obj.AsBool(), false);
}

TEST(ObjectTests, ObjectMakeString) {
    std::string value = "Hello, World!";
    auto obj = JsonObject::MakeString(value);
    ASSERT_EQ(obj.IsString(), true);
    ASSERT_EQ(obj.AsString(), value);
}

TEST(ObjectTests, ObjectMakeEmptyArray) {
    const size_t expected_array_size = 7;
    auto obj = JsonObject::MakeArray();
    ASSERT_EQ(obj.IsArray(), true);
    auto& v = obj.AsArray();
    v.push_back(JsonObject::MakeNull());
    v.push_back(JsonObject::MakeBool(true));
    v.push_back(JsonObject::MakeInt(0));
    v.push_back(JsonObject::MakeReal(0));
    v.push_back(JsonObject::MakeString("Lol"));
    v.push_back(JsonObject::MakeArray());
    v.push_back(JsonObject::MakeObject());
    ASSERT_EQ(obj.AsArray().size(), expected_array_size);
    ASSERT_EQ(obj[0], JsonObject::MakeNull());
    ASSERT_EQ(obj[4], JsonObject::MakeString("Lol"));
}

TEST(ObjectTests, ObjectMakeEmptyObject) {
    auto obj = JsonObject::MakeObject();
    ASSERT_EQ(obj.IsObject(), true);

}
