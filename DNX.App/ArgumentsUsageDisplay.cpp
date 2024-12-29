#include "stdafx.h"
#include "ArgumentsUsageDisplay.h"
#include "../DNX.Utils/ConsoleUtils.h"
#include "../DNX.Utils/FileUtils.h"
#include "../DNX.Utils/StringUtils.h"
#include <iomanip>
#include <iostream>
#include <ostream>

// ReSharper disable CppClangTidyPerformanceAvoidEndl
// ReSharper disable CppInconsistentNaming

using namespace DNX::App;
using namespace DNX::Utils;

string ArgumentsUsageDisplay::ErrorLinePrefix = "ERROR";

void ArgumentsUsageDisplay::ShowUsage(const Arguments& arguments, const AppDetails& appDetails)
{
    auto parameters = arguments.GetArgumentsByType(ArgumentType::PARAMETER);
    parameters.sort(Argument::CompareByPosition);

    const auto optionsAndSwitchesTypes = { ArgumentType::PARAMETER, ArgumentType::OPTION, ArgumentType::SWITCH };
    auto optionsAndSwitches = arguments.GetArgumentsByTypes(optionsAndSwitchesTypes);
    optionsAndSwitches.sort(Argument::CompareByTypeAndPosition);

    const auto hasOptions = !optionsAndSwitches.empty();

    string argumentText;
    for (auto iter = parameters.begin(); iter != parameters.end(); ++iter)
    {
        argumentText
            .append(" [")
            .append(iter->GetLongName())
            .append("]");
    }

    if (hasOptions)
    {
        if (!argumentText.empty())
        {
            argumentText.append(" ");
        }

        argumentText.append("[OPTIONS]");
    }

    cout << appDetails.GetHeaderLine() << std::endl;
    if (!appDetails.Copyright.empty())
    {
        cout << appDetails.Copyright << std::endl;
    }
    cout << std::endl;
    cout << "Usage:" << std::endl;
    cout << AppDetails::GetApplicationName() << argumentText << std::endl;

    if (hasOptions)
    {
        cout << std::endl;
        cout << "OPTIONS:" << std::endl;

        list<tuple<Argument, string, string>> optionDescriptions;

        size_t maxOptionDescriptionLength = 0;
        for (auto iter = optionsAndSwitches.begin(); iter != optionsAndSwitches.end(); ++iter)
        {
            string optionDesc;
            if (iter->GetArgumentType() == ArgumentType::PARAMETER)
            {
                optionDesc = "[" + iter->GetLongName() + "]";
            }
            else
            {
                optionDesc = "-" + iter->GetShortName();
                if (iter->HasLongName())
                {
                    optionDesc += ", --" + iter->GetLongName();
                }
            }
            optionDesc += " " + ValueTypeTextConverter.GetText(iter->GetValueType());

            maxOptionDescriptionLength = std::max(optionDesc.length(), maxOptionDescriptionLength);

            auto textDesc = iter->GetDescription();

            list<string> textDescParts;

            if (iter->GetRequired())
            {
                textDescParts.emplace_back("Required");
            }
            if (!iter->GetDefaultValue().empty())
            {
                textDescParts.push_back("Default:" + iter->GetDefaultValue());
            }
            if (!iter->GetValueList().empty())
            {
                const auto valueListText = StringUtils::JoinText(iter->GetValueList(), ", ");

                textDescParts.push_back("Values: " + valueListText);
            }

            if (!textDescParts.empty())
            {
                textDesc += " (";

                auto index = 0;
                for (auto textPart = textDescParts.begin(); textPart != textDescParts.end(); ++textPart)
                {
                    if (index > 0)
                    {
                        textDesc += ", ";
                    }

                    textDesc += *textPart;

                    ++index;
                }

                textDesc += ")";
            }

            const auto optionAndDesc = tuple<Argument, string, string>(*iter, optionDesc, textDesc);

            optionDescriptions.push_back(optionAndDesc);
        }

        for (auto iter = optionDescriptions.begin(); iter != optionDescriptions.end(); ++iter)
        {
            auto paddedWidth = maxOptionDescriptionLength + 2;

            std::cout << std::left << std::setfill(' ') << std::setw(static_cast<streamsize>(paddedWidth)) << std::get<1>(*iter)
                << std::get<2>(*iter)
                << std::endl;
        }
    }

    list<string> argument_file_lines;
    if (FileUtils::FileExists(AppDetails::GetDefaultArgumentsFileName()))
    {
        argument_file_lines.push_back("Default arguments file: " + AppDetails::GetDefaultArgumentsFileName());
    }
    if (FileUtils::FileExists(AppDetails::GetLocalArgumentsFileName()))
    {
        if (AppDetails::GetLocalArgumentsFileName() != AppDetails::GetDefaultArgumentsFileName())
        {
            argument_file_lines.push_back("Local arguments file: " + AppDetails::GetLocalArgumentsFileName());
        }
    }

    if (!argument_file_lines.empty())
    {
        cout << std::endl;
        for (const auto& line : argument_file_lines)
            cout << line << std::endl;
    }
}

void ArgumentsUsageDisplay::ShowErrors(const Arguments& arguments, const int blankLinesBefore, const int blankLinesAfter)
{
    ConsoleUtils::ShowBlankLines(blankLinesBefore);

    auto errors = arguments.GetErrors();
    for (auto iter = errors.begin(); iter != errors.end(); ++iter)
    {
        cout << ErrorLinePrefix << ": " << *iter << endl;
    }

    ConsoleUtils::ShowBlankLines(blankLinesAfter);
}
