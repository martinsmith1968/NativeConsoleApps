#include "stdafx.h"
#include "DNXAppArgumentsParser.h"
#include "DNXAppOptionsSwitchValue.h"
#include "../DNX.Utils/FileUtils.h"
#include "../DNX.Utils/StringUtils.h"

#include <iostream>
#include <fstream>
#include <iomanip>
#include <list>
#include <string>

using namespace std;
using namespace DNX::App;
using namespace DNX::Utils;

// ReSharper disable CppInconsistentNaming

void AppArgumentsParser::ParseDefaultOptionsFile(AppOptions& options)
{
    const auto defaultOptionsFileName = AppDetails::GetDefaultOptionsFileName();

    ParseOptionsFile(options, defaultOptionsFileName);
}

void AppArgumentsParser::ParseLocalOptionsFile(AppOptions& options)
{
    const auto localOptionsFileName = AppDetails::GetDefaultOptionsFileName();

    ParseOptionsFile(options, localOptionsFileName);
}

void AppArgumentsParser::ParseOptionsFile(AppOptions& options, const string& fileName)
{
    string optionName = "";

    if (FileUtils::FileExists(fileName))
    {
        auto parameter = 0;
        const auto arg = "@" + fileName;

        ParseSingleArg(arg, options, optionName, parameter);
    }
}

void AppArgumentsParser::ParseOptions(const int argc, char** argv, AppOptions& options)
{
    string optionName;
    auto parameter = 0;

    for (auto i = 1; i < argc; ++i)
    {
        const string arg = argv[i];

        // Process this argument
        ParseSingleArg(arg, options, optionName, parameter);
    }
}

void AppArgumentsParser::ReadOptions(const int argc, char* argv[], AppOptions& options, const bool processOptionsFiles)
{
    if (processOptionsFiles)
    {
        ParseDefaultOptionsFile(options);
        ParseLocalOptionsFile(options);
    }

    ParseOptions(argc, argv, options);
}

void AppArgumentsParser::Parse(const int argc, char* argv[], AppOptions& options)
{
    ReadOptions(argc, argv, options, true);

    if (!options.IsUsingDefaultOptionsFile())
    {
        options.Reset();

        ReadOptions(argc, argv, options, false);
    }

    // Validate
    ValidateRequired(options);
    ValidateValues(options);
    options.PostParseValidate();
}

void AppArgumentsParser::ParseSingleArg(string arg, AppOptions& options, string& optionName, int& parameter)
{
    // Handle file name options
    if (StringUtils::StartsWith(arg, "@"))
    {
        const auto fileName = StringUtils::RemoveStartsWith(arg, "@");

        auto lines = ReadLinesFromFile(fileName, options);

        for (auto iter = lines.begin(); iter != lines.end(); ++iter)
        {
            auto& line = *iter;

            if (StringUtils::StartsWith(line, "-") || StringUtils::StartsWith(line, "/"))
            {
                const auto spacePos = line.find(" ");
                const auto hasSpace = spacePos != string::npos;

                const auto argName = hasSpace
                    ? line.substr(0, spacePos)
                    : line;

                auto argValue = hasSpace
                    ? line.substr(spacePos + 1, string::npos)
                    : string("");

                if (StringUtils::StartsAndEndsWith(argValue, "\""))
                {
                    argValue = StringUtils::RemoveStartsAndEndsWith(argValue, "\"");
                }

                if (!argName.empty())
                {
                    ParseSingleArg(argName, options, optionName, parameter);
                }
                if (!argValue.empty())
                {
                    ParseSingleArg(argValue, options, optionName, parameter);
                }
            }
            else
            {
                ParseSingleArg(*iter, options, optionName, parameter);
            }
        }

        return;
    }

    // Handle long name options
    if (StringUtils::StartsWith(arg, "--"))
    {
        auto argNameAndValue = StringUtils::RemoveStartsWith(arg, "--");

        const auto equalsPos = argNameAndValue.find("=");
        const auto hasValue = equalsPos != string::npos;

        const auto argName = hasValue
            ? argNameAndValue.substr(0, equalsPos - 1)
            : argNameAndValue;

        const auto argValue = hasValue
            ? arg.substr(equalsPos + 1, string::npos)
            : "";

        auto& option = options.GetOptionByLongName(argName);
        if (option.IsEmpty())
        {
            options.AddError(string("Unknown option: ") + argName);
            return;
        }

        const auto shortName = option.GetShortName();
        if (hasValue)
        {
            HandleOption(options, shortName, argValue);
        }
        else
        {
            auto switchInfo = AppOptionsSwitchValue::ParseSwitchDetails(optionName);

            HandleSwitch(options, switchInfo.GetName(), switchInfo.GetValue());
        }

        return;
    }

    // Parse Option Name
    if (StringUtils::StartsWith(arg, "-") || StringUtils::StartsWith(arg, "/"))
    {
        optionName = arg.substr(1, string::npos);

        auto switchInfo = AppOptionsSwitchValue::ParseSwitchDetails(optionName);

        // Handle as a switch ?
        if (HandleSwitch(options, switchInfo.GetName(), switchInfo.GetValue()))
        {
            optionName = "";
        }
        return;
    }

    // Handle as an option or parameter ?
    if (optionName.empty())
    {
        if (HandleParameter(options, parameter, arg))
        {
            ++parameter;
        }
    }
    else
    {
        HandleOption(options, optionName, arg);
    }

    // Reset for next iteration
    optionName = "";
}

list<string> AppArgumentsParser::ReadLinesFromFile(const string& fileName, AppOptions& options)
{
    list<string> lines;

    try
    {
        ifstream in(fileName);

        if (in)
        {
            string line;

            while (std::getline(in, line))
            {
                lines.push_back(line);
            }

            in.close();
        }
    }
    catch (exception ex)
    {
        options.AddError(ex.what());
        lines.clear();
    }

    return lines;
}

void AppArgumentsParser::ShowBlankLines(const int count)
{
    for (auto iter = 0; iter < count; ++iter)
    {
        cout << endl;
    }
}

void AppArgumentsParser::ShowUsage(const AppOptions& options, const AppDetails& appDetails)
{
    auto parameters = options.GetOptionsByType(OptionType::PARAMETER);
    parameters.sort(AppOption::CompareByPosition);

    const auto optionsAndSwitchesTypes = { OptionType::PARAMETER, OptionType::OPTION, OptionType::SWITCH };
    auto optionsAndSwitches = options.GetOptionsByTypes(optionsAndSwitchesTypes);
    optionsAndSwitches.sort(AppOption::CompareByTypeAndPosition);

    const auto hasOptions = !optionsAndSwitches.empty();

    string parameterText;
    for (auto iter = parameters.begin(); iter != parameters.end(); ++iter)
    {
        parameterText
            .append(" [")
            .append(iter->GetLongName())
            .append("]");
    }

    if (hasOptions)
    {
        if (!parameterText.empty())
        {
            parameterText.append(" ");
        }

        parameterText.append("[OPTIONS]");
    }

    cout << appDetails.GetHeaderLine() << std::endl;
    if (!appDetails.Copyright.empty())
    {
        cout << appDetails.Copyright << std::endl;
    }
    cout << std::endl;
    cout << "Usage:" << std::endl;
    cout << appDetails.Name << parameterText << std::endl;

    if (hasOptions)
    {
        cout << std::endl;
        cout << "OPTIONS:" << std::endl;

        list<tuple<AppOption, string, string>> optionDescriptions;

        size_t maxOptionDescriptionLength = 0;
        for (auto iter = optionsAndSwitches.begin(); iter != optionsAndSwitches.end(); ++iter)
        {
            string optionDesc;
            if (iter->GetOptionType() == OptionType::PARAMETER)
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

            if (optionDesc.length() > maxOptionDescriptionLength)
            {
                maxOptionDescriptionLength = optionDesc.length();
            }

            auto textDesc = iter->GetDescription();

            list<string> textDescParts;

            if (iter->GetRequired())
            {
                textDescParts.push_back("Required");
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

            const auto optionAndDesc = tuple<AppOption, string, string>(*iter, optionDesc, textDesc);

            optionDescriptions.push_back(optionAndDesc);
        }

        for (auto iter = optionDescriptions.begin(); iter != optionDescriptions.end(); ++iter)
        {
            std::cout << std::left << std::setfill(' ') << std::setw(maxOptionDescriptionLength + 2) << std::get<1>(*iter)
                << std::get<2>(*iter)
                << std::endl;
        }
    }
}

void AppArgumentsParser::ShowErrors(const AppOptions& options, const int blankLinesBefore, const int blankLinesAfter)
{
    ShowBlankLines(blankLinesBefore);

    auto errors = options.GetErrors();
    for (auto iter = errors.begin(); iter != errors.end(); ++iter)
    {
        cout << "Error: " << *iter << endl;
    }

    ShowBlankLines(blankLinesAfter);
}

bool AppArgumentsParser::HandleParameter(AppOptions& options, const int position, const string& value)
{
    const auto optionName = to_string(position);

    const auto& parameter = options.GetOptionByShortName(optionName);
    if (parameter.IsEmpty())
    {
        options.AddError(string("Unexpected parameter at position: " + optionName));
        return false;
    }
    if (parameter.GetOptionType() != OptionType::PARAMETER)
    {
        return false;
    }

    options.SetOptionValue(optionName, value);

    return true;
}

void AppArgumentsParser::HandleOption(AppOptions& options, const string& optionName, const string& value)
{
    const auto& option = options.GetOptionByShortName(optionName);
    if (option.IsEmpty())
    {
        options.AddError(string("Unknown option: " + optionName));
        return;
    }
    if (option.GetOptionType() != OptionType::OPTION)
    {
        return;
    }

    options.SetOptionValue(optionName, value);
}

bool AppArgumentsParser::HandleSwitch(AppOptions& options, const string& optionName, const bool switchOn)
{
    const auto& option = options.GetOptionByShortName(optionName);
    if (option.IsEmpty())
    {
        options.AddError(string("Unknown switch: " + optionName));
        return true;
    }
    if (option.GetOptionType() != OptionType::SWITCH)
    {
        return false;
    }

    options.SetOptionValue(optionName, StringUtils::BoolToString(switchOn));

    return true;
}

void AppArgumentsParser::ValidateRequired(AppOptions& options)
{
    auto requiredOptions = options.GetRequiredOptions();

    for (auto iter = requiredOptions.begin(); iter != requiredOptions.end(); ++iter)
    {
        if (!options.HasOptionValue(iter->GetShortName()))
        {
            options.AddError(iter->GetNameDescription() + " is required");
        }
    }
}

void AppArgumentsParser::ValidateValues(AppOptions& options)
{
    auto optionList = options.GetOptions();

    for (auto iter = optionList.begin(); iter != optionList.end(); ++iter)
    {
        const auto optionValue = options.GetOptionValue(iter->GetShortName());
        if (!ValueConverter::IsValueValid(optionValue, iter->GetValueType()))
        {
            if (!(iter->GetRequired() && optionValue.empty()))
            {
                options.AddError(iter->GetNameDescription() + " value is invalid (" + optionValue + ")");
            }
        }
    }
}
