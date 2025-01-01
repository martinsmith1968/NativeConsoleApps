#pragma once
#include "stdafx.h"
#include "Arguments.h"
#include "Command.h"

// ReSharper disable CppInconsistentNaming
// ReSharper disable CppClangTidyClangDiagnosticHeaderHygiene
// ReSharper disable CppTooWideScopeInitStatement
// ReSharper disable CppClangTidyCppcoreguidelinesAvoidConstOrRefDataMembers

namespace DNX::App
{
    //------------------------------------------------------------------------------
    // CommandArguments
    class CommandArguments final : public Arguments
    {
        const string CommandNameLongName = "command-name";

        const string CommandNameDescription = "The command to execute";

    public:
        CommandArguments();

        void BuildFromCommands(list<Command> commands)
        {
            Reset();
            AddStandardArguments();

            list<string> command_name_value_list;
            for (auto iter = commands.begin(); iter != commands.end(); ++iter)
            {
                command_name_value_list.emplace_back(iter->GetName());
            }

            AddParameter(ValueType::STRING, 1, CommandNameLongName, "", CommandNameDescription, true, command_name_value_list);
        }

        string GetCommandNameValue()
        {
            return GetOptionValue(CommandNameLongName);
        }
    };
}
