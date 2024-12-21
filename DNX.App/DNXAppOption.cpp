#include "stdafx.h"
#include "DNXAppOption.h"

using namespace std;
using namespace DNX::App;

// ReSharper disable CppInconsistentNaming

bool AppOption::IsEmpty() const
{
    return _position < 0;
}

OptionType AppOption::GetOptionType() const
{
    return _optionType;
}

ValueType AppOption::GetValueType() const
{
    return _valueType;
}
string AppOption::GetShortName() const
{
    return _shortName;
}
string AppOption::GetLongName() const
{
    return _longName;
}
string AppOption::GetDescription() const
{
    return _description;
}
string AppOption::GetDefaultValue() const
{
    return _defaultValue;
}
bool AppOption::GetRequired() const
{
    return _required;
}
int AppOption::GetPosition() const
{
    return _position;
}
list<string> AppOption::GetValueList() const
{
    return _valueList;
}

bool AppOption::HasLongName() const
{
    return !_longName.empty();
}

string AppOption::GetNameDescription() const
{
    string description;

    description += OptionTypeTextHelper.GetText(_optionType);

    if (!description.empty()) {
        description += ": ";
    }

    description += _optionType == OptionType::PARAMETER
        ? _longName
        : _shortName;

    return description;
}

AppOption::AppOption() :
    _optionType(OptionType::PARAMETER),
    _valueType(ValueType::STRING),
    _required(false),
    _position(-1)
{
}

AppOption::AppOption(
    const OptionType optionType,
    const ValueType valueType,
    const int position,
    const string& shortName,
    const string& longName,
    const string& description,
    const string& defaultValue,
    const bool required,
    const list<string>& valueList
)
{
    _optionType   = optionType;
    _valueType    = valueType;
    _shortName    = shortName;
    _longName     = longName;
    _description  = description;
    _defaultValue = defaultValue;
    _required     = required;
    _position     = position;

    if (!valueList.empty())
    {
        _valueList = valueList;
    }
}

AppOption& AppOption::Empty()
{
    static AppOption empty_instance;

    return empty_instance;
}

bool AppOption::CompareByPosition(const AppOption& first, const AppOption& second)
{
    return first.GetPosition() < second.GetPosition();
}

bool AppOption::CompareByTypeAndPosition(const AppOption& first, const AppOption& second)
{
    if (first.GetOptionType() != second.GetOptionType())
    {
        return first.GetOptionType() < second.GetOptionType();
    }

    return CompareByPosition(first, second);
}
