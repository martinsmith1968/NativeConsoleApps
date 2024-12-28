#pragma once

#include "pch.h"
#include "../DNX.App/DNXAppOptions.h"

class Options2 final : public AppOptions
{
public:
    Options2()
    {
        auto const defaultTimeout = std::to_string(30);
        auto const defaultSleep = std::to_string(200);

        AddArgument(OptionType::PARAMETER, ValueType::STRING, "", "message-text", "", "The Text to display", true, 0);
        AddArgument(OptionType::OPTION, ValueType::INT, "t", "timeout", defaultTimeout, "The timeout to wait for in seconds", false);
        AddArgument(OptionType::OPTION, ValueType::INT, "s", "sleep", defaultSleep, "The timeout to sleep for between checks for in milliseconds", false);

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
