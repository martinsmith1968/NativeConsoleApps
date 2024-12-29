#include "stdafx.h"
#include "ArgumentsParser.h"
#include "../DNX.Utils/FileUtils.h"
#include "../DNX.Utils/ListUtils.h"
#include "../DNX.Utils/StringUtils.h"
#include <fstream>
#include <list>
#include <string>

// ReSharper disable CppInconsistentNaming
// ReSharper disable CppClangTidyPerformanceAvoidEndl
// ReSharper disable CppClangTidyBugproneNarrowingConversions
// ReSharper disable CppClangTidyModernizePassByValue

using namespace std;
using namespace DNX::App;
using namespace DNX::Utils;

//-----------------------------------------------------------------------------
// Internal methods
string ArgumentsParser::SanitizeText(const string& text)
{
    const auto double_quote = "\"";

    auto value = StringUtils::Trim(text);
    value = StringUtils::RemoveStartsAndEndsWith(value, double_quote);

    return value;
}

list<string> ArgumentsParser::ConvertLinesToRawArguments(const list<string>& lines)
{
    list<string> raw_arguments;

    for (auto& line : lines)
    {
        string parts = StringUtils::Trim(line);

        auto argument_name = SanitizeText(StringUtils::Before(parts, " "));
        auto argument_value = SanitizeText(StringUtils::After(parts, " "));

        raw_arguments.push_back(argument_name);
        raw_arguments.push_back(argument_value);
    }

    return raw_arguments;
}

void ArgumentsParser::ParseArgumentsFile(Arguments& arguments, const string& fileName) const
{
    if (FileUtils::FileExists(fileName))
    {
        const auto arg = _config.GetCustomArgumentsFilePrefix() + fileName;

        auto argumentValueConsumed = false;
        ParseArgument(arguments, arg, "", argumentValueConsumed);
    }
}

void ArgumentsParser::ParseArguments(Arguments& arguments, list<string>& argumentsText) const
{
    for (auto i = 0; i < static_cast<int>(argumentsText.size()); ++i)
    {
        string argumentName  = ListUtils::GetAt(argumentsText,  i);
        string argumentValue = ListUtils::GetAt(argumentsText, i + 1);

        auto argumentValueConsumed = false;
        if (!ParseArgument(arguments, argumentName, argumentValue, argumentValueConsumed))
            return;
        if (argumentValueConsumed)
            i += 1;
    }
}

bool ArgumentsParser::ParseArgument(Arguments& arguments, const string& argumentName, const string& argumentValue, bool& argumentValueConsumed) const
{
    argumentValueConsumed = false;

    if (StringUtils::StartsWith(argumentName, _config.GetCustomArgumentsFilePrefix()))
    {
        const auto fileName = StringUtils::RemoveStartsWith(argumentName, _config.GetCustomArgumentsFilePrefix());

        try
        {
            const auto lines = FileUtils::ReadLines(fileName);
            auto argumentsText = ConvertLinesToRawArguments(lines);

            ParseArguments(arguments, argumentsText);

            return true;
        }
        catch (exception& ex)
        {
            arguments.AddError(ex.what());
            return false;
        }
    }

    if (StringUtils::StartsWith(argumentName, _config.GetLongNamePrefix()))
    {
        const auto switch_long_name = StringUtils::RemoveStartsWith(argumentName, _config.GetLongNamePrefix(), 1);

        if (HandleAsSwitch(arguments, _config, switch_long_name))
            return true;
        if (HandleAsOption(arguments, switch_long_name, argumentValue))
        {
            argumentValueConsumed = true;
            return true;
        }
    }

    if (StringUtils::StartsWith(argumentName, _config.GetShortNamePrefix()))
    {
        const auto switch_short_name = StringUtils::RemoveStartsWith(argumentName, _config.GetShortNamePrefix(), 1);

        if (HandleAsSwitch(arguments, _config, switch_short_name))
            return true;
        if (HandleAsOption(arguments, switch_short_name, argumentValue))
        {
            argumentValueConsumed = true;
            return true;
        }
    }

    if (HandleAsParameter(arguments, arguments.GetNextPosition(), argumentName))
    {
        arguments.AdvancePosition();
        return true;
    }

    return false;
}

bool ArgumentsParser::HandleAsSwitch(Arguments& arguments, const ParserConfig& config, const string& argumentName)
{
    const auto switchOnSuffix = string(1, config.GetSwitchOnSuffix());
    const auto switchOffSuffix = string(1, config.GetSwitchOffSuffix());

    auto switchValue = true;
    string switchName = argumentName;

    if (StringUtils::EndsWith(switchName, switchOnSuffix))
    {
        switchName = StringUtils::RemoveEndsWith(switchName, switchOnSuffix, 1);
        switchValue = true;
    }
    if (StringUtils::EndsWith(switchName, switchOffSuffix))
    {
        switchName = StringUtils::RemoveEndsWith(switchName, switchOffSuffix, 1);
        switchValue = false;
    }

    const auto& option = arguments.GetOptionByName(argumentName);
    if (option.IsEmpty())
        return false;

    if (option.GetArgumentType() != ArgumentType::SWITCH)
    {
        return false;
    }

    arguments.SetOptionValue(option.GetLongName(), StringUtils::BoolToString(switchValue));

    return true;
}

bool ArgumentsParser::HandleAsOption(Arguments& arguments, const string& argumentName, const string& argumentValue)
{
    const auto& option = arguments.GetOptionByName(argumentName);
    if (option.IsEmpty())
        return false;

    if (option.GetArgumentType() != ArgumentType::OPTION)
    {
        return false;
    }

    arguments.SetOptionValue(option.GetLongName(), argumentValue);

    return true;
}

bool ArgumentsParser::HandleAsParameter(Arguments& arguments, const int position, const string& argumentValue)
{
    auto& option = arguments.GetParameterAtPosition(position);
    if (option.IsEmpty())
        return false;

    arguments.SetOptionValue(option.GetLongName(), argumentValue);

    return true;
}

void ArgumentsParser::ValidateRequired(Arguments& arguments)
{
    auto requiredArguments = arguments.GetRequiredArguments();

    for (auto iter = requiredArguments.begin(); iter != requiredArguments.end(); ++iter)
    {
        if (!arguments.HasOptionValue(iter->GetShortName()))
        {
            arguments.AddError(iter->GetNameDescription() + " is required");
        }
    }
}

void ArgumentsParser::ValidateValues(Arguments& arguments)
{
    auto optionList = arguments.GetArguments();

    for (auto iter = optionList.begin(); iter != optionList.end(); ++iter)
    {
        const auto optionValue = arguments.GetOptionValue(iter->GetShortName());
        if (!ValueConverter::IsValueValid(optionValue, iter->GetValueType()))
        {
            if (!(iter->GetRequired() && optionValue.empty()))
            {
                arguments.AddError(iter->GetNameDescription() + " value is invalid (" + optionValue + ")");
            }
        }
    }
}


//-----------------------------------------------------------------------------
// Public usage methods
ArgumentsParser::ArgumentsParser(Arguments& arguments, const AppDetails& app_details, const ParserConfig& config)
    : _arguments(arguments),
    _config(config),
    _app_details(app_details)
{
}

void ArgumentsParser::Parse(const int argc, char* argv[]) const
{
    if (_config.GetUseCustomArgumentsFile() && _arguments.IsUsingDefaultArgumentsFile())
        ParseArgumentsFile(_arguments, AppDetails::GetDefaultArgumentsFileName());

    if (_config.GetUseLocalArgumentsFile() && _arguments.IsUsingDefaultArgumentsFile())
        ParseArgumentsFile(_arguments, AppDetails::GetLocalArgumentsFileName());

    auto arguments = ListUtils::ToList(argc, argv, 1);

    ParseArguments(_arguments, arguments);

    // Validate
    ValidateRequired(_arguments);
    ValidateValues(_arguments);
    _arguments.PostParseValidate();
}


//-----------------------------------------------------------------------------
// Static Public methods
void ArgumentsParser::ParseArguments(Arguments& arguments, const int argc, char* argv[], const AppDetails& app_details, const ParserConfig& config)
{
    const auto parser = ArgumentsParser(arguments, app_details, config);
    parser.Parse(argc, argv);
}
