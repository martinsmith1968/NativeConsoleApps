#include "stdafx.h"
#include <string>
#include <chrono>
#include "../DNX.Utils/StringUtils.h"
#include "../DNX.App/DNXValueConverter.h"
#include "../DNX.App/DNXOptionType.h"
#include "../DNX.App/DNXAppOptions.h"

// ReSharper disable CppInconsistentNaming

using namespace DNX::Utils;

//------------------------------------------------------------------------------
// AppOptions
class Options final : public AppOptions
{
public:
    Options()
    {
        auto const defaultMessageText = "Press any key to continue (or wait {timeout} seconds) . . . ";
        auto const defaultTimeout = std::to_string(30);
        auto const defaultSleep = std::to_string(200);

        AddOption(OptionType::PARAMETER, ValueType::STRING, "", "message-text", defaultMessageText, "The Text to display", false, 0);
        AddOption(OptionType::OPTION, ValueType::INT, "t", "timeout", defaultTimeout, "The timeout to wait for in seconds", false);
        AddOption(OptionType::OPTION, ValueType::INT, "s", "sleep", defaultSleep, "The timeout to sleep for between checks for in milliseconds", false);

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
        return StringUtils::ReplaceString(
            StringUtils::ReplaceString(
                GetMessageText(),
                "{timeout}",
                std::to_string(GetTimeoutSeconds())
                ),
            "{sleep}",
            std::to_string(GetSleepMilliseconds()
            )
        );
    }

    void PostParseValidate() override
    {
        auto const timeout_time = std::chrono::seconds(GetTimeoutSeconds());
        auto const sleep_time = std::chrono::milliseconds(GetSleepMilliseconds());

        if (sleep_time >= timeout_time)
        {
            AddError("Sleep time must be less than Timeout");
        }
    };
};
