#include "stdafx.h"
#include "DNXAppOption.h"

// ReSharper disable CppInconsistentNaming

using namespace std;
using namespace DNX::App;

AppOption AppOption::_app_option = AppOption();;

bool AppOption::IsEmpty() const
{
    return _position == 0;
}
ArgumentType AppOption::GetArgumentType() const
{
    return _argumentType;
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
uint8_t AppOption::GetPosition() const
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

    description += ArgumentTypeTextHelper.GetText(_argumentType);

    if (!description.empty())
    {
        description += ": ";
    }

    description += _longName;

    return description;
}

AppOption::AppOption() :
    _argumentType(ArgumentType::PARAMETER),
    _valueType(ValueType::STRING),
    _required(false),
    _position(0)
{
}

AppOption::AppOption(
    const ArgumentType argumentType,
    const ValueType valueType,
    const uint8_t position,
    const string& shortName,
    const string& longName,
    const string& description,
    const string& defaultValue,
    const bool required,
    const list<string>& valueList
)
{
    _argumentType = argumentType;
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

bool AppOption::CompareByPosition(const AppOption& first, const AppOption& second)
{
    return first.GetPosition() < second.GetPosition();
}

bool AppOption::CompareByTypeAndPosition(const AppOption& first, const AppOption& second)
{
    if (first.GetArgumentType() != second.GetArgumentType())
    {
        return first.GetArgumentType() < second.GetArgumentType();
    }

    return CompareByPosition(first, second);
}
