#pragma once
#include "stdafx.h"
#include "../DNX.Utils/StringUtils.h"
#include "../DNX.App/Arguments.h"
#include <string>
#include <chrono>

// ReSharper disable CppInconsistentNaming
// ReSharper disable CppClangTidyClangDiagnosticHeaderHygiene
// ReSharper disable CppTooWideScopeInitStatement
// ReSharper disable CppClangTidyCppcoreguidelinesAvoidConstOrRefDataMembers

using namespace DNX::Utils;

enum class CommandType : uint8_t
{
    LIST,
    START,
    STOP,
    ELAPSED,
    DELETE,
};

class CommandTypeText : public EnumTextResolver<CommandType>
{
public:
    CommandTypeText()
    {
        SetText(CommandType::LIST, "List");
        SetText(CommandType::START, "Start");
        SetText(CommandType::STOP, "Stop");
        SetText(CommandType::ELAPSED, "Elapsed");
        SetText(CommandType::DELETE, "Delete");
    }
};

//------------------------------------------------------------------------------
// Arguments
class AppArguments final : public Arguments
{
    CommandTypeText CommandTypeTextConverter;

    const string ArgumentNameCommand   = "command";
    const string ArgumentNameTimerName = "timer-name";
    const string ArgumentNameQuiet     = "quiet";

public:
    AppArguments()
    {
        AddParameter(ValueType::STRING, 1, ArgumentNameCommand, "", "The command to execute", true, CommandTypeTextConverter.GetAllText());
        AddParameter(ValueType::STRING, 2, ArgumentNameTimerName, "", "The command to execute", true);



        AddSwitch("q", ArgumentNameQuiet, "false", "Disable/Enable output messages", false);
    }

    string GetCommand()
    {
        return GetOptionValue(ArgumentNameCommand);
    }

    string GetTimerName()
    {
        return GetOptionValue(ArgumentNameTimerName);
    }

    bool GetQuiet()
    {
        return GetSwitchValue(ArgumentNameQuiet);
    }

    void PostParseValidate() override
    {
    }
};
