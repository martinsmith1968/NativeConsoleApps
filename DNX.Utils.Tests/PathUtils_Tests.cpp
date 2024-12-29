#include "pch.h"
#include "../DNX.Utils/PathUtils.h"

using namespace std;
using namespace DNX::Utils;

// ReSharper disable CppClangTidyPerformanceAvoidEndl

#define TEST_GROUP PathUtils

TEST(TEST_GROUP, GetCurrentDirectory_returns_something)
{
    // Act
    const auto result = PathUtils::GetCurrentDirectory();

    // Assert
    cout << "GetCurrentDirectory: " << result << endl;
    EXPECT_NE(result, "");
}

TEST(TEST_GROUP, Combine_returns_appropriate_combined_value)
{
    EXPECT_EQ(PathUtils::Combine("", ""), "");
    EXPECT_EQ(PathUtils::Combine("", "b"), "b");
    EXPECT_EQ(PathUtils::Combine("a", ""), "a");
    EXPECT_EQ(PathUtils::Combine("a", "b"), "a" + PathUtils::PATH_SEPARATOR + "b");
    EXPECT_EQ(PathUtils::Combine("a" + PathUtils::PATH_SEPARATOR + "b", "c"), "a" + PathUtils::PATH_SEPARATOR + "b" + PathUtils::PATH_SEPARATOR + "c");
    EXPECT_EQ(PathUtils::Combine("a" + PathUtils::PATH_SEPARATOR + "b" + PathUtils::PATH_SEPARATOR, "c"), "a" + PathUtils::PATH_SEPARATOR + "b" + PathUtils::PATH_SEPARATOR + "c");
}
