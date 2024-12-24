#include "pch.h"

#include "../DNX.App/DNXAppOptions.h"
#include "../DNX.App/DNXAppArgumentsParser.h"
#include "Options1.h"
#include "Options2.h"

// ReSharper disable CppClangTidyPerformanceUnnecessaryCopyInitialization

using namespace std;
using namespace DNX::App;

TEST(Parse, single_positional_arguments_assigns_correctly) {
    char* argv[] = {
        "",
        "bob",
    };
    const auto argc = 2;

    Options1 options;

    // Act
    AppArgumentsParser::Parse(argc, argv, options);

    // Assert
    EXPECT_TRUE(options.IsValid());
    EXPECT_EQ("bob", options.GetMessageText());
}

TEST(Parse, single_positional_argument_with_shortname_option_after_and_switch_assigns_correctly) {
    char* argv[] = {
        "",
        "bob",
        "-t",
        "5",
        "-x",
    };
    const auto argc = 5;

    Options1 options;

    // Act
    AppArgumentsParser::Parse(argc, argv, options);

    // Assert
    EXPECT_TRUE(options.IsValid());
    EXPECT_EQ("bob", options.GetMessageText());
    EXPECT_EQ(5, options.GetTimeoutSeconds());
    EXPECT_EQ(true, options.GetDebug());
}

TEST(Parse, single_positional_argument_with_shortname_option_before_and_switch_assigns_correctly) {
    char* argv[] = {
        "",
        "-t",
        "5",
        "bob",
        "-x",
    };
    const auto argc = 5;

    Options1 options;

    // Act
    AppArgumentsParser::Parse(argc, argv, options);

    // Assert
    EXPECT_TRUE(options.IsValid());
    EXPECT_EQ("bob", options.GetMessageText());
    EXPECT_EQ(5, options.GetTimeoutSeconds());
    EXPECT_EQ(true, options.GetDebug());
}

TEST(Parse, single_positional_argument_with_shortname_options_before_and_after_and_switch_assigns_correctly) {
    char* argv[] = {
        "",
        "-t",
        "5",
        "bob",
        "-x",
        "-s",
        "500",
    };
    const auto argc = 7;

    Options1 options;

    // Act
    AppArgumentsParser::Parse(argc, argv, options);

    // Assert
    EXPECT_TRUE(options.IsValid());
    EXPECT_EQ("bob", options.GetMessageText());
    EXPECT_EQ(5, options.GetTimeoutSeconds());
    EXPECT_EQ(500, options.GetSleepMilliseconds());
    EXPECT_EQ(true, options.GetDebug());
}

TEST(IsValid, options_without_any_required_arguments_returns_successfully) {
    char* argv[] = {
        "",
    };
    const auto argc = 1;

    Options1 options;

    // Act
    AppArgumentsParser::Parse(argc, argv, options);

    // Assert
    EXPECT_TRUE(options.IsValid());
}

TEST(IsValid, options_with_required_arguments_returns_successfully) {
    char* argv[] = {
        "",
    };
    const auto argc = 1;

    Options2 options;

    // Act
    AppArgumentsParser::Parse(argc, argv, options);

    // Assert
    EXPECT_FALSE(options.IsValid());
}

//TEST(IsValid, options_with_option_shortname_without_value_returns_successfully) {
//    char* argv[] = {
//        "",
//        "-t",
//    };
//    const auto argc = 2;
//
//    Options1 options;
//
//    // Act
//    AppArgumentsParser::Parse(argc, argv, options);
//
//    // Assert
//    EXPECT_FALSE(options.IsValid());
//}
//
//TEST(IsValid, options_with_option_longname_without_value_returns_successfully) {
//    char* argv[] = {
//        "",
//        "--timeout",
//    };
//    const auto argc = 2;
//
//    Options1 options;
//
//    // Act
//    AppArgumentsParser::Parse(argc, argv, options);
//
//    // Assert
//    EXPECT_FALSE(options.IsValid());
//}
