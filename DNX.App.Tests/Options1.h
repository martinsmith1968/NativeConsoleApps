#pragma once

#include "pch.h"
#include "../DNX.App/Arguments.h"

// ReSharper disable CppInconsistentNaming

class Options1 final : public Arguments
{
public:
    Options1()
    {
        const auto defaultMessageText = "Press any key to continue (or wait {timeout} seconds) . . . ";
        const auto defaultTimeout = std::to_string(30);
        const auto defaultSleep = std::to_string(200);

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
};
