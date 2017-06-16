//
// Created by Nathan Bollom on 16/06/2017.
//

#include "../catch.hpp"
#include "../../common/common.h"
#include <memory>
#include <string>

TEST_CASE("JSON - Empty Document Should Fail", "[JSON]") {
    std::wstring json = L"";
    REQUIRE_THROWS_WITH(JSON::Document::Parse(json), Catch::EndsWith("Empty Document"));
}

TEST_CASE("JSON - String Root Should Fail", "[JSON]") {
    std::wstring json = L"\"Test\"";
    REQUIRE_THROWS_WITH(JSON::Document::Parse(json), Catch::EndsWith("Invalid character at root level"));
}

TEST_CASE("JSON - Number Root Should Fail", "[JSON]") {
    std::wstring json = L"42";
    REQUIRE_THROWS_WITH(JSON::Document::Parse(json), Catch::EndsWith("Invalid character at root level"));
}

TEST_CASE("JSON - Boolean Root Should Fail", "[JSON]") {
    std::wstring json = L"True";
    REQUIRE_THROWS_WITH(JSON::Document::Parse(json), Catch::EndsWith("Invalid character at root level"));
}

TEST_CASE("JSON - Null Root Should Fail", "[JSON]") {
    std::wstring json = L"null";
    REQUIRE_THROWS_WITH(JSON::Document::Parse(json), Catch::EndsWith("Invalid character at root level"));
}

TEST_CASE("JSON - Document Without JSON Should Fail", "[JSON]") {
    std::wstring json = L"blah";
    REQUIRE_THROWS_WITH(JSON::Document::Parse(json), Catch::EndsWith("Invalid character at root level"));
}

TEST_CASE("JSON - Empty Object Root", "[JSON]") {
    std::wstring json = L"{}";
    std::shared_ptr<JSON::Document> doc = JSON::Document::Parse(json);
    REQUIRE(doc != nullptr);
    std::shared_ptr<JSON::Iterable> root = doc->GetRoot();
    REQUIRE(root != nullptr);
    REQUIRE(root->IsObject());
    REQUIRE(root->Length() == 0);
}

TEST_CASE("JSON - Unterminated Object Root Should Fail", "[JSON]") {
    std::wstring json = L"{";
    REQUIRE_THROWS_WITH(JSON::Document::Parse(json), Catch::EndsWith("Object is not closed"));
}

TEST_CASE("JSON - Empty Array Root", "[JSON]") {
    std::wstring json = L"[]";
    std::shared_ptr<JSON::Document> doc = JSON::Document::Parse(json);
    REQUIRE(doc != nullptr);
    std::shared_ptr<JSON::Iterable> root = doc->GetRoot();
    REQUIRE(root != nullptr);
    REQUIRE(root->AsArray());
    REQUIRE(root->Length() == 0);
}

TEST_CASE("JSON - Unterminated Array Root Should Fail", "[JSON]") {
    std::wstring json = L"[";
    REQUIRE_THROWS_WITH(JSON::Document::Parse(json), Catch::EndsWith("Array is not closed"));
}

TEST_CASE("JSON - Multiple Roots Should Fail", "[JSON]") {
    std::wstring json = L"{}[]";
    REQUIRE_THROWS_WITH(JSON::Document::Parse(json), Catch::EndsWith("Multiple roots detected"));
}
