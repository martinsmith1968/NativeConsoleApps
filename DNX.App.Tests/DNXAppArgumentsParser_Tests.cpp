#include "pch.h"
#include "../DNX.App/DNXAppOptions.h"
#include "../DNX.App/DNXAppArgumentsParser.h"
#include "Options1.h"
#include "Options2.h"
// ReSharper disable CppClangTidyPerformanceUnnecessaryCopyInitialization
// ReSharper disable CppInconsistentNaming
// ReSharper disable CppClangTidyMiscUseAnonymousNamespace
// ReSharper disable CppClangTidyPerformanceAvoidEndl
// ReSharper disable CppStringLiteralToCharPointerConversion
// ReSharper disable CppClangTidyClangDiagnosticWritableStrings

using namespace std;
using namespace DNX::App;

#define TEST_GROUP AppArgumentsParser

static void ShowErrors(const AppOptions& options)
{
    cout << "Error Count: " << options.GetErrors().size() << endl;
    for (const auto& error : options.GetErrors())
    {
        cout << "Error: " << error << endl;
    }
}

TEST(TEST_GROUP, ParseArguments_single_positional_arguments_assigns_correctly)
{
    constexpr auto argc = 2;
    char* argv[argc] = {
        "",
        "bob",
    };

    Options1 options;

    // Act
    AppArgumentsParser::ParseArguments(argc, argv, options);
    ShowErrors(options);

    // Assert
    EXPECT_TRUE(options.IsValid());
    EXPECT_EQ("bob", options.GetMessageText());
}

TEST(TEST_GROUP, ParseArguments_single_positional_argument_with_shortname_option_after_and_switch_assigns_correctly)
{
    constexpr auto argc = 5;
    char* argv[argc] = {
        "",
        "bob",
        "-t",
        "5",
        "-x",
    };

    Options1 options;

    // Act
    AppArgumentsParser::ParseArguments(argc, argv, options);
    ShowErrors(options);

    // Assert
    EXPECT_TRUE(options.IsValid());
    EXPECT_EQ("bob", options.GetMessageText());
    EXPECT_EQ(5, options.GetTimeoutSeconds());
    EXPECT_EQ(true, options.IsDebug());
}

TEST(TEST_GROUP, ParseArguments_single_positional_argument_with_shortname_option_before_and_switch_assigns_correctly)
{
    constexpr auto argc = 5;
    char* argv[argc] = {
        "",
        "-t",
        "5",
        "bob",
        "-x",
    };

    Options1 options;

    // Act
    AppArgumentsParser::ParseArguments(argc, argv, options);
    ShowErrors(options);

    // Assert
    EXPECT_TRUE(options.IsValid());
    EXPECT_EQ("bob", options.GetMessageText());
    EXPECT_EQ(5, options.GetTimeoutSeconds());
    EXPECT_EQ(true, options.IsDebug());
}

TEST(TEST_GROUP, ParseArguments_single_positional_argument_with_shortname_options_before_and_after_and_switch_assigns_correctly)
{
    constexpr auto argc = 7;
    char* argv[argc] = {
        "",
        "-t",
        "5",
        "bob",
        "-x",
        "-s",
        "500",
    };

    Options1 options;

    // Act
    AppArgumentsParser::ParseArguments(argc, argv, options);
    ShowErrors(options);

    // Assert
    EXPECT_TRUE(options.IsValid());
    EXPECT_EQ("bob", options.GetMessageText());
    EXPECT_EQ(5, options.GetTimeoutSeconds());
    EXPECT_EQ(500, options.GetSleepMilliseconds());
    EXPECT_EQ(true, options.IsDebug());
}

TEST(TEST_GROUP, IsValid_options_without_any_required_arguments_returns_successfully)
{
    constexpr auto argc = 1;
    char* argv[argc] = {
        "",
    };

    Options1 options;

    // Act
    AppArgumentsParser::ParseArguments(argc, argv, options);
    ShowErrors(options);

    // Assert
    EXPECT_TRUE(options.IsValid());
}

TEST(TEST_GROUP, IsValid_options_with_required_arguments_returns_successfully)
{
    constexpr auto argc = 1;
    char* argv[argc] = {
        "",
    };

    Options2 options;

    // Act
    AppArgumentsParser::ParseArguments(argc, argv, options);
    ShowErrors(options);

    // Assert
    EXPECT_FALSE(options.IsValid());
}

TEST(TEST_GROUP, IsValid_options_with_option_shortname_without_value_returns_successfully)
{
    constexpr auto argc = 2;
    char* argv[argc] = {
        "",
        "-t",
    };

    Options1 options;

    // Act
    AppArgumentsParser::ParseArguments(argc, argv, options);
    ShowErrors(options);

    // Assert
    EXPECT_FALSE(options.IsValid());
}

TEST(TEST_GROUP, IsValid_options_with_option_longname_without_value_returns_successfully)
{
    constexpr auto argc = 2;
    char* argv[argc] = {
        "",
        "--timeout",
    };

    Options1 options;

    // Act
    AppArgumentsParser::ParseArguments(argc, argv, options);
    ShowErrors(options);

    // Assert
    EXPECT_FALSE(options.IsValid());
}

TEST(TEST_GROUP, IsValid_options_with_option_longname_with_invalid_value_returns_successfully)
{
    constexpr auto argc = 3;
    char* argv[argc] = {
        "",
        "--timeout",
        "abc",
    };

    Options1 options;

    // Act
    AppArgumentsParser::ParseArguments(argc, argv, options);
    ShowErrors(options);

    // Assert
    EXPECT_FALSE(options.IsValid());
}
