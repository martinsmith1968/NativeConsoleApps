#include "stdafx.h"
#include "DNXAppOptions.h"
#include "../DNX.Utils/StringUtils.h"

// ReSharper disable CppInconsistentNaming
// ReSharper disable CppTooWideScope
// ReSharper disable CppClangTidyClangDiagnosticImplicitIntConversion

using namespace std;
using namespace DNX::App;
using namespace DNX::Utils;

AppOptions::AppOptions()
{
    AddSwitch(DebugShortName,                 DebugLongName,                    "false", DebugDescription,                     false, INT_MAX - 3);
    AddSwitch(HelpShortName,                  HelpLongName,                     "false", HelpDescription,                      false, INT_MAX - 2);
    AddSwitch(UseDefaultOptionsFileShortName, UseDefaultOptionsFileLongName, "true",  useDefaultOptionsFileDesc, false, INT_MAX - 1);
    AddSwitch(UseLocalOptionsFileShortName,   UseLocalOptionsFileLongName,   "true",  useLocalOptionsFileDesc,   false, INT_MAX);
}

void AppOptions::PostParseValidate()
{
}

void AppOptions::AddError(const string& text)
{
    _errors.push_back(text);
}

list<AppOption> AppOptions::GetOptions() const
{
    const auto types = OptionTypeText.GetAllValues();

    return GetOptionsByTypes(types);
}

AppOption& AppOptions::GetOptionByLongName(const string& longName)
{
    const auto iter = _options.find(longName);
    if (iter == _options.end())
        return AppOption::Empty();

    return iter->second;
}

AppOption& AppOptions::GetOptionByShortName(const string& shortName)
{
    for (auto iter = _options.begin(); iter != _options.end(); ++iter)
    {
        if (iter->second.GetShortName() == shortName)
        {
            return iter->second;
        }
    }

    return AppOption::Empty();
}

AppOption& AppOptions::GetOptionByName(const string& name)
{
    auto& property = GetOptionByShortName(name);
    if (!property.IsEmpty())
        return property;

    return GetOptionByLongName(name);
}

AppOption& AppOptions::GetParameterAtPosition(const int position)
{
    for (auto iter = _options.begin(); iter != _options.end(); ++iter)
    {
        if (iter->second.GetOptionType() == OptionType::PARAMETER && iter->second.GetPosition() == position)
        {
            return iter->second;
        }
    }

    return AppOption::Empty();
}

list<AppOption> AppOptions::GetOptionsByType(const OptionType optionType) const
{
    list<AppOption> filtered;

    for (auto iter = _options.begin(); iter != _options.end(); ++iter)
    {
        if (iter->second.GetOptionType() == optionType)
        {
            filtered.push_back(iter->second);
        }
    }

    return filtered;
}

list<AppOption> AppOptions::GetOptionsByTypes(const list<OptionType>& optionTypes) const
{
    list<AppOption> filtered;

    for (auto iter = _options.begin(); iter != _options.end(); ++iter)
    {
        const auto found = std::find(std::begin(optionTypes), std::end(optionTypes), iter->second.GetOptionType()) != std::end(optionTypes);
        if (found)
        {
            filtered.push_back(iter->second);
        }
    }

    return filtered;
}

list<AppOption> AppOptions::GetRequiredOptions() const
{
    list<AppOption> filtered;

    auto typeList = GetOptions();
    for (auto iter = typeList.begin(); iter != typeList.end(); ++iter)
    {
        if (iter->GetRequired())
        {
            filtered.push_back(*iter);
        }
    }

    return filtered;
}

string AppOptions::GetOptionValue(const string& name)
{
    const auto& option = GetOptionByName(name);
    if (option.IsEmpty())
        throw exception((string("Unknown Option: ") + name).c_str());

    const auto iter = _values.find(option.GetLongName());
    if (iter != _values.end())
        return iter->second;

    return option.GetDefaultValue();
}

void AppOptions::SetOptionValue(const string& name, const string& value)
{
    const auto& option = GetOptionByName(name);
    if (option.IsEmpty())
        throw exception((string("Unknown Option: ") + name).c_str());

    _values[option.GetLongName()] = value;
}

bool AppOptions::HasOptionValue(const string& name)
{
    const auto& option = GetOptionByName(name);
    if (option.IsEmpty())
        throw exception((string("Unknown Option: ") + name).c_str());

    return _values.find(option.GetLongName()) != _values.end();
}

void AppOptions::AddArgumentWithValues(
    const OptionType optionType,
    const ValueType valueType,
    const string& shortName,
    const string& longName,
    const string& defaultValue,
    const string& description,
    const bool required,
    const int position,
    const string& valueListText
)
{
    auto valueList = list<string>();

    if (!valueListText.empty())
    {
        valueList = StringUtils::SplitText(valueListText, ',');
    }

    AddArgument(optionType, valueType, shortName, longName, defaultValue, description, required, position, valueList);
}

void AppOptions::AddArgument(
    const OptionType optionType,
    const ValueType valueType,
    const string& shortName,
    const string& longName,
    const string& defaultValue,
    const string& description,
    const bool required,
    const int position,
    const list<string>& valueList
)
{
    if (shortName.empty() && optionType != OptionType::PARAMETER)
        throw exception("ShortName is required");
    if (longName.empty())
        throw exception("LongName is required");

    auto existingOption = GetOptionByName(shortName);
    if (!existingOption.IsEmpty())
        throw exception((string("Option already exists: ") + shortName).c_str());

    existingOption = GetOptionByName(longName);
    if (!existingOption.IsEmpty())
        throw exception((string("Option already exists: ") + longName).c_str());

    uint8_t realPosition = static_cast<uint8_t>(position);
    string realShortName = shortName;

    if (optionType == OptionType::PARAMETER)
    {
        realPosition = static_cast<uint8_t>(GetOptionsByType(OptionType::PARAMETER).size() + 1);
        realShortName = to_string(position);

        if (longName.empty())
        {
            throw exception((string("Parameter must have a long name: ") + shortName).c_str());
        }
    }
    else
    {
        if (ValueConverter::IsInt(shortName))
            throw exception((string("Invalid Option Name: ") + shortName).c_str());

        if (position == 0)
        {
            const auto types = {OptionType::OPTION, OptionType::SWITCH };
            realPosition = static_cast<int>(GetOptionsByTypes(types).size() + 1);
        }
    }

    const auto option = AppOption(optionType, valueType, realPosition, realShortName, longName, description, defaultValue, required, valueList);

    _options[option.GetLongName()] = option;
}

void AppOptions::AddSwitch(
    const string& shortName,
    const string& longName,
    const string& defaultValue,
    const string& description,
    const bool required,
    const int position
)
{
    if (!ValueConverter::IsBool(defaultValue))
        throw exception((string("Default Value is not a BOOL: ") + defaultValue).c_str());

    int realPosition = position;
    if (position == 0)
    {
        const auto types = { OptionType::OPTION, OptionType::SWITCH };
        realPosition = static_cast<int>(GetOptionsByTypes(types).size() + 1);
    }

    AddArgument(OptionType::SWITCH, ValueType::BOOL, shortName, longName, defaultValue, description, required, realPosition);
}

void AppOptions::Reset()
{
    _last_position = 0;
    _values.clear();
    _errors.clear();
}

int AppOptions::GetNextPosition() const
{
    return _last_position + 1;
}

void AppOptions::AdvancePosition()
{
    ++_last_position;
}

list<string> AppOptions::GetErrors() const
{
    return _errors;
}

bool AppOptions::IsValid() const
{
    return _errors.empty();
}

bool AppOptions::IsDebug()
{
    return ValueConverter::ToBool(GetOptionValue(DebugLongName));
}

bool AppOptions::IsHelp()
{
    const auto value = GetOptionValue(HelpLongName);
    return ValueConverter::IsBool(value)
        ? ValueConverter::ToBool(value)
        : false;
}

bool AppOptions::IsUsingDefaultOptionsFile()
{
    const auto value = GetOptionValue(UseDefaultOptionsFileLongName);
    return ValueConverter::IsBool(value)
        ? ValueConverter::ToBool(value)
        : false;
}
