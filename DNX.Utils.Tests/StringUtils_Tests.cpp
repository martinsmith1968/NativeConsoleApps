#include "pch.h"

#include "../DNX.Utils/StringUtils.h"

using namespace std;
using namespace DNX::Utils;

TEST(Trim, RTrim_single_character_removes_found_target_returns_as_expected) {
    EXPECT_EQ(StringUtils::RTrim("...text...", '.'), "...text");
    EXPECT_EQ(StringUtils::RTrim("...text...", ' '), "...text...");
    EXPECT_EQ(StringUtils::RTrim(". .text. .", '.'), ". .text. ");
    EXPECT_EQ(StringUtils::RTrim(". .text. .", ' '), ". .text. .");
}

TEST(Trim, LTrim_single_character_removes_found_target_returns_as_expected) {
    EXPECT_EQ(StringUtils::LTrim("...text...", '.'), "text...");
    EXPECT_EQ(StringUtils::LTrim("...text...", ' '), "...text...");
    EXPECT_EQ(StringUtils::LTrim(". .text. .", '.'), " .text. .");
    EXPECT_EQ(StringUtils::LTrim(". .text. .", ' '), ". .text. .");
}

TEST(Trim, Trim_single_character_removes_found_target_returns_as_expected) {
    EXPECT_EQ(StringUtils::Trim("...text...", '.'), "text");
    EXPECT_EQ(StringUtils::Trim("...text...", ' '), "...text...");
    EXPECT_EQ(StringUtils::Trim(". .text. .", '.'), " .text. ");
    EXPECT_EQ(StringUtils::Trim(". .text. .", ' '), ". .text. .");
}

TEST(Trim, RTrim_text_removes_found_target_returns_as_expected) {
    EXPECT_EQ(StringUtils::RTrim("...text...", "."), "...text");
    EXPECT_EQ(StringUtils::RTrim("#{text}#", "}#"), "#{text");
    EXPECT_EQ(StringUtils::RTrim("...text...", " "), "...text...");
    EXPECT_EQ(StringUtils::RTrim(". .text. .", ". "), ". .text. .");
    EXPECT_EQ(StringUtils::RTrim(". .text. .", " ."), ". .text.");
}


TEST(Substringing, After_returns_as_expected) {
    EXPECT_EQ(StringUtils::After("This is some text", "some"), " text");
    EXPECT_EQ(StringUtils::After("This is some text", "bob"), "");
    EXPECT_EQ(StringUtils::After("This is some [[Red]]text[[/Red]]", "[["), "Red]]text[[/Red]]");
    EXPECT_EQ(StringUtils::After("This is some text", " "), "is some text");
    EXPECT_EQ(StringUtils::After("This is some text", ""), "");
    EXPECT_EQ(StringUtils::After("This is some text", ""), "");
    EXPECT_EQ(StringUtils::After("", "o"), "");
}

TEST(Substringing, Before_returns_as_expected) {
    EXPECT_EQ(StringUtils::Before("This is some text", "some"), "This is ");
    EXPECT_EQ(StringUtils::Before("This is some text", "bob"), "");
    EXPECT_EQ(StringUtils::Before("This is some [[Red]]text[[/Red]]", "[["), "This is some ");
    EXPECT_EQ(StringUtils::Before("This is some text", " "), "This");
    EXPECT_EQ(StringUtils::Before("This is some text", ""), "");
    EXPECT_EQ(StringUtils::Before("This is some text", ""), "");
    EXPECT_EQ(StringUtils::Before("", "o"), "");
}


/*
 *
        [TestCase("This is some text", "some", ExpectedResult = "This is ")]
        [TestCase("This is some text", "bob", ExpectedResult = null)]
        [TestCase("This is some [[Red]]text[[/Red]]", "[[", ExpectedResult = "This is some ")]
        [TestCase("This is some text", " ", ExpectedResult = "This")]
        [TestCase("This is some text", "", ExpectedResult = null)]
        [TestCase("This is some text", null, ExpectedResult = null)]
        [TestCase(null, "o", ExpectedResult = null)]
 *
 */
