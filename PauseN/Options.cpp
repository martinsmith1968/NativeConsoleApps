#include "stdafx.h"
#include <string>
#include "../DNX.Utils/StringUtils.h"
#include "../DNX.App/DNXValueConverter.h"
#include "../DNX.App/DNXOptionType.h"
#include "../DNX.App/DNXAppOptions.h"

// ReSharper disable CppInconsistentNaming

//------------------------------------------------------------------------------
// AppOptions
class Options final : public AppOptions
{
public:
    Options()
    {
        AddOption(OptionType::PARAMETER, ValueType::STRING, "m", "message-text", "", "The Text to display", true);
        AddOption(OptionType::OPTION, ValueType::INT, "t", "timeout", "30", "The timeout to wait for in seconds", false);

        SetOptionValue("message-text", "Press any key to continue (or wait {timeout} seconds) . . . ");
        SetOptionValue("timeout", "30");
    }

    string GetMessageText()
    {
        return GetOptionValue("message-text");
    }

    int GetTimeoutSeconds()
    {
        return ValueConverter::ToInt(GetOptionValue("timeout"));
    }

    string GetFormattedMessageText()
    {
        return ReplaceString(GetMessageText(), "{timeout}", std::to_string(GetTimeoutSeconds()));
    }
};
