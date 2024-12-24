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
        auto const defaultDebug = "false";

        AddOption(OptionType::PARAMETER, ValueType::STRING, "", "message-text", "", "The Text to display", true, 0);
        AddOption(OptionType::OPTION, ValueType::INT, "t", "timeout", defaultTimeout, "The timeout to wait for in seconds", false);
        AddOption(OptionType::OPTION, ValueType::INT, "s", "sleep", defaultSleep, "The timeout to sleep for between checks for in milliseconds", false);
        AddOption(OptionType::SWITCH, ValueType::BOOL, "x", "debug", defaultDebug, "Debug execution details", false);

        SetOptionValue("timeout", defaultTimeout);
        SetOptionValue("sleep", defaultSleep);
        SetOptionValue("debug", defaultDebug);
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

    bool GetDebug()
    {
        return ValueConverter::ToBool(GetOptionValue("debug"));
    }
};
