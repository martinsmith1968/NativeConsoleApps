#include "stdafx.h"
#include "Arguments.h"
#include "../DNX.Utils/StringUtils.h"
#include "Argument.h"

// ReSharper disable CppInconsistentNaming
// ReSharper disable CppTooWideScope
// ReSharper disable CppClangTidyClangDiagnosticImplicitIntConversion

using namespace std;
using namespace DNX::App;
using namespace DNX::Utils;

Arguments::Arguments()
{
    AddSwitch(DebugShortName,                   DebugLongName,                   "false", DebugDescription,                     false, INT_MAX - 3);
    AddSwitch(HelpShortName,                    HelpLongName,                    "false", HelpDescription,                      false, INT_MAX - 2);
    AddSwitch(UseDefaultArgumentsFileShortName, UseDefaultArgumentsFileLongName, "true",  useDefaultArgumentsFileDesc, false, INT_MAX - 1);
    AddSwitch(UseLocalArgumentsFileShortName,   UseLocalArgumentsFileLongName,   "true",  useLocalArgumentsFileDesc,   false, INT_MAX);
}

void Arguments::PostParseValidate()
{
}

void Arguments::AddError(const string& text)
{
    _errors.push_back(text);
}

list<Argument> Arguments::GetArguments() const
{
    const auto types = ArgumentTypeText.GetAllValues();

    return GetArgumentsByTypes(types);
}

Argument& Arguments::GetOptionByLongName(const string& longName)
{
    const auto iter = _arguments.find(longName);
    if (iter == _arguments.end())
        return Argument::Empty();

    return iter->second;
}

Argument& Arguments::GetOptionByShortName(const string& shortName)
{
    for (auto iter = _arguments.begin(); iter != _arguments.end(); ++iter)
    {
        if (iter->second.GetShortName() == shortName)
        {
            return iter->second;
        }
    }

    return Argument::Empty();
}

Argument& Arguments::GetOptionByName(const string& name)
{
    auto& property = GetOptionByShortName(name);
    if (!property.IsEmpty())
        return property;

    return GetOptionByLongName(name);
}

Argument& Arguments::GetParameterAtPosition(const int position)
{
    for (auto iter = _arguments.begin(); iter != _arguments.end(); ++iter)
    {
        if (iter->second.GetArgumentType() == ArgumentType::PARAMETER && iter->second.GetPosition() == position)
        {
            return iter->second;
        }
    }

    return Argument::Empty();
}

list<Argument> Arguments::GetArgumentsByType(const ArgumentType ArgumentType) const
{
    list<Argument> filtered;

    for (auto iter = _arguments.begin(); iter != _arguments.end(); ++iter)
    {
        if (iter->second.GetArgumentType() == ArgumentType)
        {
            filtered.push_back(iter->second);
        }
    }

    return filtered;
}

list<Argument> Arguments::GetArgumentsByTypes(const list<ArgumentType>& ArgumentTypes) const
{
    list<Argument> filtered;

    for (auto iter = _arguments.begin(); iter != _arguments.end(); ++iter)
    {
        const auto found = std::find(std::begin(ArgumentTypes), std::end(ArgumentTypes), iter->second.GetArgumentType()) != std::end(ArgumentTypes);
        if (found)
        {
            filtered.push_back(iter->second);
        }
    }

    return filtered;
}

list<Argument> Arguments::GetRequiredArguments() const
{
    list<Argument> filtered;

    auto typeList = GetArguments();
    for (auto iter = typeList.begin(); iter != typeList.end(); ++iter)
    {
        if (iter->GetRequired())
        {
            filtered.push_back(*iter);
        }
    }

    return filtered;
}

string Arguments::GetOptionValue(const string& name)
{
    const auto& option = GetOptionByName(name);
    if (option.IsEmpty())
        throw exception((string("Unknown Option: ") + name).c_str());

    const auto iter = _values.find(option.GetLongName());
    if (iter != _values.end())
        return iter->second;

    return option.GetDefaultValue();
}

void Arguments::SetOptionValue(const string& name, const string& value)
{
    const auto& option = GetOptionByName(name);
    if (option.IsEmpty())
        throw exception((string("Unknown Option: ") + name).c_str());

    _values[option.GetLongName()] = value;
}

bool Arguments::HasOptionValue(const string& name)
{
    const auto& option = GetOptionByName(name);
    if (option.IsEmpty())
        throw exception((string("Unknown Option: ") + name).c_str());

    return _values.find(option.GetLongName()) != _values.end();
}

void Arguments::AddArgumentWithValues(
    const ArgumentType ArgumentType,
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

    AddArgument(ArgumentType, valueType, shortName, longName, defaultValue, description, required, position, valueList);
}

void Arguments::AddArgument(
    const ArgumentType ArgumentType,
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
    if (shortName.empty() && ArgumentType != ArgumentType::PARAMETER)
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

    if (ArgumentType == ArgumentType::PARAMETER)
    {
        realPosition = static_cast<uint8_t>(GetArgumentsByType(ArgumentType::PARAMETER).size() + 1);
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
            const auto types = {ArgumentType::OPTION, ArgumentType::SWITCH };
            realPosition = static_cast<int>(GetArgumentsByTypes(types).size() + 1);
        }
    }

    const auto option = Argument(ArgumentType, valueType, realPosition, realShortName, longName, description, defaultValue, required, valueList);

    _arguments[option.GetLongName()] = option;
}

void Arguments::AddSwitch(
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
        const auto types = { ArgumentType::OPTION, ArgumentType::SWITCH };
        realPosition = static_cast<int>(GetArgumentsByTypes(types).size() + 1);
    }

    AddArgument(ArgumentType::SWITCH, ValueType::BOOL, shortName, longName, defaultValue, description, required, realPosition);
}

void Arguments::Reset()
{
    _last_position = 0;
    _values.clear();
    _errors.clear();
}

int Arguments::GetNextPosition() const
{
    return _last_position + 1;
}

void Arguments::AdvancePosition()
{
    ++_last_position;
}

list<string> Arguments::GetErrors() const
{
    return _errors;
}

bool Arguments::IsValid() const
{
    return _errors.empty();
}

bool Arguments::IsDebug()
{
    return ValueConverter::ToBool(GetOptionValue(DebugLongName));
}

bool Arguments::IsHelp()
{
    const auto value = GetOptionValue(HelpLongName);
    return ValueConverter::IsBool(value)
        ? ValueConverter::ToBool(value)
        : false;
}

bool Arguments::IsUsingDefaultArgumentsFile()
{
    const auto value = GetOptionValue(UseDefaultArgumentsFileLongName);
    return ValueConverter::IsBool(value)
        ? ValueConverter::ToBool(value)
        : false;
}
