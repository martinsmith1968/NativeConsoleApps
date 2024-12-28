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
// Instance methods
void ArgumentsParser::ParseOptionsFile(Arguments& options, const string& fileName) const
{
    if (FileUtils::FileExists(fileName))
    {
        const auto arg = _config.GetCustomOptionsFilePrefix() + fileName;

        auto argumentValueConsumed = false;
        ParseArgument(arg, "", options, argumentValueConsumed);
    }
}

void ArgumentsParser::ParseArguments(list<string> arguments, Arguments& options) const
{
    for (auto i = 0; i < static_cast<int>(arguments.size()); ++i)
    {
        string argumentName  = ListUtils::GetAt(arguments, i);
        string argumentValue = ListUtils::GetAt(arguments, i + 1);

        auto argumentValueConsumed = false;
        if (!ParseArgument(argumentName, argumentValue, options, argumentValueConsumed))
            return;
        if (argumentValueConsumed)
            i += 1;
    }
}

bool ArgumentsParser::ParseArgument(const string& argumentName, const string& argumentValue, Arguments& options, bool& argumentValueConsumed) const
{
    argumentValueConsumed = false;

    if (StringUtils::StartsWith(argumentName, _config.GetCustomOptionsFilePrefix()))
    {
        const auto fileName = StringUtils::RemoveStartsWith(argumentName, _config.GetCustomOptionsFilePrefix());

        try
        {
            const auto lines = FileUtils::ReadLines(fileName);
            const auto arguments = ConvertLinesToRawArguments(lines);

            ParseArguments(arguments, options);

            return true;
        }
        catch (exception& ex)
        {
            options.AddError(ex.what());
            return false;
        }
    }

    if (StringUtils::StartsWith(argumentName, _config.GetLongNamePrefix()))
    {
        const auto switch_long_name = StringUtils::RemoveStartsWith(argumentName, _config.GetLongNamePrefix(), 1);

        if (HandleAsSwitch(options, _config, switch_long_name))
            return true;
        if (HandleAsOption(options, switch_long_name, argumentValue))
        {
            argumentValueConsumed = true;
            return true;
        }
    }

    if (StringUtils::StartsWith(argumentName, _config.GetShortNamePrefix()))
    {
        const auto switch_short_name = StringUtils::RemoveStartsWith(argumentName, _config.GetShortNamePrefix(), 1);

        if (HandleAsSwitch(options, _config, switch_short_name))
            return true;
        if (HandleAsOption(options, switch_short_name, argumentValue))
        {
            argumentValueConsumed = true;
            return true;
        }
    }

    if (HandleAsParameter(options, options.GetNextPosition(), argumentName))
    {
        options.AdvancePosition();
        return true;
    }

    return false;
}

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

    for (auto line : lines)
    {
        line = StringUtils::Trim(line);

        auto argument_name  = SanitizeText(StringUtils::Before(line, " "));
        auto argument_value = SanitizeText(StringUtils::After(line, " "));

        raw_arguments.push_back(argument_name);
        raw_arguments.push_back(argument_value);
    }

    return raw_arguments;
}

bool ArgumentsParser::HandleAsSwitch(Arguments& options, const ParserConfig& config, const string& argumentName)
{
    const auto switchOnSuffix = string(1, config.GetSwitchOnSuffix());
    const auto switchOffSuffix = string(1, config.GetSwitchOffSuffix());

    auto switchValue = true;
    auto switchName = argumentName;

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

    const auto& option = options.GetOptionByName(argumentName);
    if (option.IsEmpty())
        return false;

    if (option.GetArgumentType() != ArgumentType::SWITCH)
    {
        return false;
    }

    options.SetOptionValue(option.GetLongName(), StringUtils::BoolToString(switchValue));

    return true;
}

bool ArgumentsParser::HandleAsOption(Arguments& options, const string& argumentName, const string& argumentValue)
{
    const auto& option = options.GetOptionByName(argumentName);
    if (option.IsEmpty())
        return false;

    if (option.GetArgumentType() != ArgumentType::OPTION)
    {
        return false;
    }

    options.SetOptionValue(option.GetLongName(), argumentValue);

    return true;
}

bool ArgumentsParser::HandleAsParameter(Arguments& options, const int position, const string& argumentValue)
{
    auto& option = options.GetParameterAtPosition(position);
    if (option.IsEmpty())
        return false;

    options.SetOptionValue(option.GetLongName(), argumentValue);

    return true;
}

void ArgumentsParser::ValidateRequired(Arguments& options)
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

void ArgumentsParser::ValidateValues(Arguments& options)
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



//-----------------------------------------------------------------------------
// Public methods
ArgumentsParser::ArgumentsParser(Arguments& options, const AppDetails& app_details, const ParserConfig& config)
    : _options(options),
    _config(config),
    _app_details(app_details)
{
}

void ArgumentsParser::Parse(const int argc, char* argv[]) const
{
    if (_config.GetUseGlobalOptionsFile() && _options.IsUsingDefaultOptionsFile())
        ParseOptionsFile(_options, AppDetails::GetDefaultOptionsFileName());

    if (_config.GetUseLocalOptionsFile() && _options.IsUsingDefaultOptionsFile())
        ParseOptionsFile(_options, AppDetails::GetLocalOptionsFileName());

    const auto arguments = ListUtils::ToList(argc, argv, 1);

    ParseArguments(arguments, _options);

    // Validate
    ValidateRequired(_options);
    ValidateValues(_options);
    _options.PostParseValidate();
}


//-----------------------------------------------------------------------------
// Static Public methods
void ArgumentsParser::ParseArguments(const int argc, char* argv[], Arguments& options, const ParserConfig& config)
{
    auto parser = ArgumentsParser(options, AppDetails(), config);
    parser.Parse(argc, argv);
}
