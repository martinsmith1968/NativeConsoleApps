#pragma once
#include "stdafx.h"
#include "../DNX.Utils/StringUtils.h"
#include "../DNX.App/ValueConverter.h"
#include "../DNX.App/ArgumentType.h"
#include "../DNX.App/Arguments.h"
#include <string>
#include <chrono>

// ReSharper disable CppInconsistentNaming
// ReSharper disable CppClangTidyClangDiagnosticHeaderHygiene

using namespace DNX::Utils;

//------------------------------------------------------------------------------
// AppOptions
class Options final : public Arguments
{
public:
    Options()
    {

        auto const defaultMessageText = "Press any key to continue (or wait {timeout} seconds) . . . ";
        auto const defaultTimeout     = std::to_string(30);
        auto const defaultSleep       = std::to_string(200);

        AddArgument(ArgumentType::PARAMETER, ValueType::STRING, "", "message-text", defaultMessageText, "The Text to display", false, 0);
        AddArgument(ArgumentType::OPTION, ValueType::INT, "t", "timeout", defaultTimeout, "The timeout to wait for in seconds", false);
        AddArgument(ArgumentType::OPTION, ValueType::INT, "s", "sleep", defaultSleep, "The timeout to sleep for between checks for in milliseconds", false);

        SetOptionValue("message-text", defaultMessageText);
        SetOptionValue("timeout", defaultTimeout);
        SetOptionValue("sleep", defaultSleep);
    }

    string GetMessageText()
    {
        return GetOptionValue("message-text");
    }

    int GetTimeoutSeconds()
    {
        return ValueConverter::ToInt(GetOptionValue("timeout"));
    }

    int GetSleepMilliseconds()
    {
        return ValueConverter::ToInt(GetOptionValue("sleep"));
    }

    string GetFormattedMessageText()
    {
        auto replace_timeout = [](Options& options, const string& text)
            {
                return StringUtils::ReplaceString(text, "{timeout}", std::to_string(options.GetTimeoutSeconds()));
            };
        auto replace_sleep= [](Options& options, const string& text)
            {
                return StringUtils::ReplaceString(text, "{sleep}", std::to_string(options.GetSleepMilliseconds()));
            };

        return replace_sleep(*this, replace_timeout(*this, GetMessageText()));
    }

    void PostParseValidate() override
    {
        auto const timeout_time = std::chrono::seconds(GetTimeoutSeconds());
        auto const sleep_time = std::chrono::milliseconds(GetSleepMilliseconds());

        if (sleep_time >= timeout_time)
        {
            AddError("Sleep time must be less than Timeout");
        }
    }
};
