# JsonLib

## What is?

This is small library for C++ parsing of json-files.

Warning! Library does not support any languages but english.

## Examples

Some examples to API understanding.

#### Objects creation
```c++
JsonObject::MakeNull(); // Creates equivalent to 'null'
JsonObject::MakeBool(true); // Creates equivalent to 'true'
JsonObject::MakeBool(false); // Creates equivalent to 'false'
JsonObject::MakeInt(32); // Creates equivalent to '32'
JsonObject::MakeReal(3.1415926); // Creates equivalent to '3.1415926'
JsonObject::MakeString("Hello, Json!"); // Creates equivalent to "Hello, Json!"

JsonObject::MakeArray(); // Creates equivalent to '[]'
JsonObject::MakeArray({
    JsonObject::MakeNull(), 
    JsonObject::MakeBool(false),
    JsonObject::MakeString("I love minecraft!"),
}); // Creates equivalent to [null, false, "I love minecraft!"]
JsonObject::MakeObject(); // Creates equivalent to '{}'

JsonObject::MakeObject({
    {"PI": JsonObject::MakeReal(3.14)},
    {"E": JsonObejct::MakeReal(2.71)},
    {"values": JsonObject::MakeArray(
        JsonObject::MakeInt(32),
        JsonObject::MakeInt(64),
        JsonObject::MakeBool(true)
    )}
}); // Creates equivalent to {"PI": 3.14, "E": 2.71, "values": [32, 64, true]}
```

#### Strings parsing
```c++
// Strings parsing
ParseString("{\"Example\": \"The best json library\"}");

// Files parsing
ParseFile("dataset.json");
```

#### Json formatting
```c++
auto obj = JsonObject::MakeArray({
    JsonObject::MakeInt(1ll),
    JsonObject::MakeNull(),
    JsonObject::MakeObject({
           {"hello", JsonObject::MakeString("world")}
    }),
    JsonObject::MakeBool(false),
    JsonObject::MakeString("text")
});

ToString(obj, {.PrettyFormat = false});
// [1,null,{"hello":"world"},false,"text"]

ToString(obj, {.PrettyFromat = true});
// [
//    1,
//    null,
//    {
//         "hello": "world"
//    },
//    false,
//    "text"
// ]

SaveToFile("result.json", obj, {.PrettyFormat = false}); 
// Saves obj to "result.json" wihtout pretty format

SaveToFile("result.json", obj, {.PrettyFormat = true});
// Saves obj to "result.json" wiht pretty format
```

## Motivation

This is study project for improving my skills in C++ and CMake.