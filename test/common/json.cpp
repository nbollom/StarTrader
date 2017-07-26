//
// Created by Nathan Bollom on 16/06/2017.
//

#include "../catch.hpp"
#include "../../common/common.h"
#include <memory>
#include <string>

template <typename T,unsigned S>
inline unsigned arraysize(const T (&v)[S]) { return S; }

TEST_CASE("JSON - Empty document should fail", "[JSON]") {
    std::wstring json = L"";
    REQUIRE_THROWS_WITH(JSON::Document::Parse(json), Catch::EndsWith("Empty document"));
}

TEST_CASE("JSON - String root should fail", "[JSON]") {
    std::wstring json = L"\"Test\"";
    REQUIRE_THROWS_WITH(JSON::Document::Parse(json), Catch::EndsWith("Invalid character at root level"));
}

TEST_CASE("JSON - Number root should fail", "[JSON]") {
    std::wstring json = L"42";
    REQUIRE_THROWS_WITH(JSON::Document::Parse(json), Catch::EndsWith("Invalid character at root level"));
}

TEST_CASE("JSON - Boolean root should fail", "[JSON]") {
    std::wstring json = L"True";
    REQUIRE_THROWS_WITH(JSON::Document::Parse(json), Catch::EndsWith("Invalid character at root level"));
}

TEST_CASE("JSON - Null root should fail", "[JSON]") {
    std::wstring json = L"null";
    REQUIRE_THROWS_WITH(JSON::Document::Parse(json), Catch::EndsWith("Invalid character at root level"));
}

TEST_CASE("JSON - Document without JSON should fail", "[JSON]") {
    std::wstring json = L"blah";
    REQUIRE_THROWS_WITH(JSON::Document::Parse(json), Catch::EndsWith("Invalid character at root level"));
}

TEST_CASE("JSON - Empty object root", "[JSON]") {
    std::wstring json = L"{}";
    std::shared_ptr<JSON::Document> doc = JSON::Document::Parse(json);
    REQUIRE(doc != nullptr);
    std::shared_ptr<JSON::Iterable> root = doc->GetRoot();
    REQUIRE(root != nullptr);
    REQUIRE(root->IsObject());
    REQUIRE(root->Length() == 0);
}

TEST_CASE("JSON - Unterminated object root should fail", "[JSON]") {
    std::wstring json = L"{";
    REQUIRE_THROWS_WITH(JSON::Document::Parse(json), Catch::EndsWith("Object is not closed"));
}

TEST_CASE("JSON - Empty array root", "[JSON]") {
    std::wstring json = L"[]";
    std::shared_ptr<JSON::Document> doc = JSON::Document::Parse(json);
    REQUIRE(doc != nullptr);
    std::shared_ptr<JSON::Iterable> root = doc->GetRoot();
    REQUIRE(root != nullptr);
    REQUIRE(root->AsArray());
    REQUIRE(root->Length() == 0);
}

TEST_CASE("JSON - Unterminated array root should fail", "[JSON]") {
    std::wstring json = L"[";
    REQUIRE_THROWS_WITH(JSON::Document::Parse(json), Catch::EndsWith("Array is not closed"));
}

TEST_CASE("JSON - Multiple roots should fail", "[JSON]") {
    std::wstring json = L"{}[]";
    REQUIRE_THROWS_WITH(JSON::Document::Parse(json), Catch::EndsWith("Multiple roots detected"));
}

TEST_CASE("JSON - Object with empty array", "[JSON]") {
    std::wstring json = L"{\"array\": []}";
    std::shared_ptr<JSON::Document> doc = JSON::Document::Parse(json);
    REQUIRE(doc != nullptr);
    std::shared_ptr<JSON::Iterable> root = doc->GetRoot();
    REQUIRE(root != nullptr);
    REQUIRE(root->IsObject());
    REQUIRE(root->Length() == 1);
    std::shared_ptr<JSON::Object> obj = std::dynamic_pointer_cast<JSON::Object>(root);
    REQUIRE(obj->HasKey(L"array"));
    std::shared_ptr<JSON::Value> value = obj->Get(L"array");
    REQUIRE(value->IsArray());
    std::shared_ptr<JSON::Array> array = std::dynamic_pointer_cast<JSON::Array>(value);
    REQUIRE(array->Length() == 0);
}

TEST_CASE("JSON - Array with empty object", "[JSON]") {
    std::wstring json = L"[{}]";
    std::shared_ptr<JSON::Document> doc = JSON::Document::Parse(json);
    REQUIRE(doc != nullptr);
    std::shared_ptr<JSON::Iterable> root = doc->GetRoot();
    REQUIRE(root != nullptr);
    REQUIRE(root->IsArray());
    REQUIRE(root->Length() == 1);
    std::shared_ptr<JSON::Array> array = std::dynamic_pointer_cast<JSON::Array>(root);
    std::shared_ptr<JSON::Value> value = array->Get(0);
    REQUIRE(value->IsObject());
    std::shared_ptr<JSON::Object> obj = std::dynamic_pointer_cast<JSON::Object>(value);
    REQUIRE(obj->Length() == 0);
}

TEST_CASE("JSON - Object with missing value should fail", "[JSON]") {
    std::wstring json = L"{\"empty\":}";
    REQUIRE_THROWS_WITH(JSON::Document::Parse(json), Catch::EndsWith("Value expected"));
}

TEST_CASE("JSON - Object with missing comma between pairs should fail", "[JSON]") {
    std::wstring json = L"{\"key1\":[] \"key2\":[]}";
    REQUIRE_THROWS_WITH(JSON::Document::Parse(json), Catch::EndsWith("Missing comma"));
}

TEST_CASE("JSON - Object with missing pair should fail", "[JSON]") {
    std::wstring json = L"{,}";
    REQUIRE_THROWS_WITH(JSON::Document::Parse(json), Catch::EndsWith("Missing key:value pair"));
}

TEST_CASE("JSON - Array with missing comma between values should fail", "[JSON]") {
    std::wstring json = L"[[][]]";
    REQUIRE_THROWS_WITH(JSON::Document::Parse(json), Catch::EndsWith("Missing comma"));
}

TEST_CASE("JSON - Array with missing value should fail", "[JSON]") {
    std::wstring json = L"[,]";
    REQUIRE_THROWS_WITH(JSON::Document::Parse(json), Catch::EndsWith("Value expected"));
}

TEST_CASE("JSON - String literals", "[JSON]") {
    std::wstring json = L"[True, true, TRUE, tRuE, False, false, FALSE, fAlSe, Null, null, NULL, nUlL]";
    std::shared_ptr<JSON::Document> doc = JSON::Document::Parse(json);
    REQUIRE(doc != nullptr);
    std::shared_ptr<JSON::Iterable> root = doc->GetRoot();
    REQUIRE(root != nullptr);
    REQUIRE(root->IsArray());
    REQUIRE(root->Length() == 12);
    std::shared_ptr<JSON::Array> array = std::dynamic_pointer_cast<JSON::Array>(root);
    for (int i = 0; i < 4; ++i) {
        std::shared_ptr<JSON::Value> value = array->Get(i);
        REQUIRE(value->IsBool());
        std::shared_ptr<JSON::Boolean> boolean = std::dynamic_pointer_cast<JSON::Boolean>(value);
        REQUIRE(boolean->BooleanValue());
    }
    for (int i = 4; i < 8; ++i) {
        std::shared_ptr<JSON::Value> value = array->Get(i);
        REQUIRE(value->IsBool());
        std::shared_ptr<JSON::Boolean> boolean = std::dynamic_pointer_cast<JSON::Boolean>(value);
        REQUIRE(!boolean->BooleanValue());
    }
    for (int i = 8; i < 12; ++i) {
        std::shared_ptr<JSON::Value> value = array->Get(i);
        REQUIRE(value->IsNull());
    }
}


TEST_CASE("JSON - Standard Numbers", "[JSON]") {
    std::wstring json = L"[1, 0, -1, 50000, -50000, 0.5, -0.5, 0.00005, -0.00005, 999999.999, -999999.999]";
    double values[] = {1, 0, -1, 50000, -50000, 0.5, -0.5, 0.00005, -0.00005, 999999.999, -999999.999};
    std::shared_ptr<JSON::Document> doc = JSON::Document::Parse(json);
    REQUIRE(doc != nullptr);
    std::shared_ptr<JSON::Iterable> root = doc->GetRoot();
    REQUIRE(root != nullptr);
    REQUIRE(root->IsArray());
    REQUIRE(root->Length() == arraysize(values));
    std::shared_ptr<JSON::Array> array = std::dynamic_pointer_cast<JSON::Array>(root);
    for (int i = 0; i < arraysize(values); ++i) {
        std::shared_ptr<JSON::Value> value = array->Get(i);
        REQUIRE(value->IsNumber());
        std::shared_ptr<JSON::Number> number = std::dynamic_pointer_cast<JSON::Number>(value);
        REQUIRE(number->NumberValue() == values[i]);
    }
}

TEST_CASE("JSON - Exponantial Numbers", "[JSON]") {
    std::wstring json = L"[1e10, -1e10, 1e-10, -1e-10]";
    double values[] = {1e10, -1e10, 1e-10, -1e-10};
    std::shared_ptr<JSON::Document> doc = JSON::Document::Parse(json);
    REQUIRE(doc != nullptr);
    std::shared_ptr<JSON::Iterable> root = doc->GetRoot();
    REQUIRE(root != nullptr);
    REQUIRE(root->IsArray());
    REQUIRE(root->Length() == arraysize(values));
    std::shared_ptr<JSON::Array> array = std::dynamic_pointer_cast<JSON::Array>(root);
    for (int i = 0; i < arraysize(values); ++i) {
        std::shared_ptr<JSON::Value> value = array->Get(i);
        REQUIRE(value->IsNumber());
        std::shared_ptr<JSON::Number> number = std::dynamic_pointer_cast<JSON::Number>(value);
        REQUIRE(number->NumberValue() == values[i]);
    }
}
