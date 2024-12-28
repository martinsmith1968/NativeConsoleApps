#include "pch.h"
#include "../DNX.Utils/ProcessUtils.h"
#include "../DNX.Utils/StringUtils.h"

using namespace std;
using namespace DNX::Utils;

#define TEST_GROUP ProcessUtils

TEST(TEST_GROUP, GetExecutableFileName_returns_something) {
    // Act
    const auto result = ProcessUtils::GetExecutableFileName();

    // Assert
    cout << "GetExecutableFileName: " << result << endl;
    EXPECT_NE(result, "");
}

TEST(TEST_GROUP, GetExecutableFileNameOnly_returns_something) {
    // Act
    const auto result = ProcessUtils::GetExecutableFileNameOnly();

    // Assert
    cout << "GetExecutableFileNameOnly: " << result << endl;
    EXPECT_NE(result, "");

    EXPECT_NE(ProcessUtils::GetExecutableFileName(), ProcessUtils::GetExecutableFileNameOnly());
    EXPECT_TRUE(StringUtils::EndsWith(ProcessUtils::GetExecutableFileName(), ProcessUtils::GetExecutableFileNameOnly()));
}

TEST(TEST_GROUP, GetExecutableFilePath_returns_something) {
    // Act
    const auto result = ProcessUtils::GetExecutableFilePath();

    // Assert
    cout << "GetExecutableFilePath: " << result << endl;
    EXPECT_NE(result, "");

    EXPECT_NE(ProcessUtils::GetExecutableFileName(), ProcessUtils::GetExecutableFilePath());
    EXPECT_TRUE(StringUtils::StartsWith(ProcessUtils::GetExecutableFileName(), ProcessUtils::GetExecutableFilePath()));
}
