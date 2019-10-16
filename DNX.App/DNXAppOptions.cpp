#include "stdafx.h"
#include "DNXAppOptions.h"
#include "DNXAppDetails.h"
#include "../DNX.Utils/FileUtils.h"

using namespace std;
using namespace DNX::App;
using namespace DNX::Utils;

// ReSharper disable CppInconsistentNaming

const string HelpShortCode = "?";
const string UseDefaultOptionsFileShortCode = "@";

AppOptions::AppOptions() {

    const auto useDefaultOptionsFileDesc = "Use Default Options File (" + FileUtils::GetFileNameAndExtension(AppDetails::GetDefaultOptionsFileName()) + ")";

    AddOption(OptionType::SWITCH, ValueType::BOOL, HelpShortCode,                   "help",                     "false", "Show Help screen",        false, INT_MAX);
    AddOption(OptionType::SWITCH, ValueType::BOOL, UseDefaultOptionsFileShortCode,  "use-default-options-file", "true",  useDefaultOptionsFileDesc, false, INT_MAX - 1);
}

void AppOptions::PostParseValidate() {

}

void AppOptions::AddError(const string text) {
    _errors.push_back(text);
}

list<AppOption> AppOptions::GetOptions() {
    const auto types = OptionTypeText.GetAllValues();

    return GetOptionsByTypes(types);
}

AppOption& AppOptions::GetOptionByLongName(const string longName) {
    for (auto iter = _options.begin(); iter != _options.end(); ++iter) {
        if (iter->second.HasLongName() && iter->second.GetLongName() == longName) {
            return iter->second;
        }
    }

    return AppOption::Empty();
}

AppOption& AppOptions::GetOptionByShortName(const string shortName) {
    auto iter = _options.find(shortName);
    return iter == _options.end()
        ? AppOption::Empty()
        : iter->second;
}

AppOption& AppOptions::GetOptionByName(const string name) {
    auto& property = GetOptionByShortName(name);
    if (!property.IsEmpty())
        return property;

    return GetOptionByLongName(name);
}

list<AppOption> AppOptions::GetOptionsByType(const OptionType optionType) {
    list<AppOption> filtered;

    for (auto iter = _options.begin(); iter != _options.end(); ++iter) {
        if (iter->second.GetOptionType() == optionType) {
            filtered.push_back(iter->second);
        }
    }

    return filtered;
}

list<AppOption> AppOptions::GetOptionsByTypes(const list<OptionType> optionTypes) {
    list<AppOption> filtered;

    for (auto iter = _options.begin(); iter != _options.end(); ++iter) {
        const auto found = std::find(std::begin(optionTypes), std::end(optionTypes), iter->second.GetOptionType()) != std::end(optionTypes);
        if (found) {
            filtered.push_back(iter->second);
        }
    }

    return filtered;
}

list<AppOption> AppOptions::GetRequiredOptions() {
    list<AppOption> filtered;

    auto typeList = GetOptions();
    for (auto iter = typeList.begin(); iter != typeList.end(); ++iter) {
        if (iter->GetRequired()) {
            filtered.push_back(*iter);
        }
    }

    return filtered;
}

string AppOptions::GetOptionValue(const string name) {
    const auto option = GetOptionByName(name);
    if (option.IsEmpty())
        throw exception((string("Unknown Option: ") + name).c_str());

    const auto iter = _values.find(option.GetShortName());
    if (iter != _values.end())
        return iter->second;

    return option.GetDefaultValue();
}

void AppOptions::SetOptionValue(const string name, const string value) {
    const auto option = GetOptionByName(name);
    if (option.IsEmpty())
        throw exception((string("Unknown Option: ") + name).c_str());

    _values[option.GetShortName()] = value;
}

bool AppOptions::HasOptionValue(const string name) {
    const auto option = GetOptionByName(name);
    if (option.IsEmpty())
        throw exception((string("Unknown Option: ") + name).c_str());

    return _values.find(option.GetShortName()) != _values.end();
}

void AppOptions::AddOptionWithValues(
    const OptionType optionType,
    const ValueType valueType,
    const string shortName,
    const string longName,
    const string defaultValue,
    const string description,
    const bool required,
    const int position,
    const string valueListText
)
{
    auto valueList = list<string>();

    if (!valueListText.empty()) {
        valueList = SplitText(valueListText, ',');
    }

    AddOption(optionType, valueType, shortName, longName, defaultValue, description, required, position, valueList);
}

void AppOptions::AddOption(
    const OptionType optionType,
    const ValueType valueType,
    const string shortName,
    const string longName,
    const string defaultValue,
    const string description,
    const bool required,
    const int position,
    const list<string> valueList
)
{
    if (!GetOptionByShortName(shortName).IsEmpty())
        throw exception((string("Option already exists: ") + shortName).c_str());
    if (!GetOptionByLongName(longName).IsEmpty())
        throw exception((string("Option already exists: ") + longName).c_str());

    auto realPosition = position;
    auto realShortName = shortName;

    if (optionType == OptionType::PARAMETER) {
        realPosition = static_cast<int>(GetOptionsByType(OptionType::PARAMETER).size() + 1);
        realShortName = to_string(position);

        if (longName.empty()) {
            throw exception((string("Parameter must have a long name: ") + shortName).c_str());
        }
    }
    else {
        if (ValueConverter::IsInt(shortName))
            throw exception((string("Invalid Option Name: ") + shortName).c_str());

        if (position == 0) {
            const auto types = {OptionType::OPTION, OptionType::SWITCH };
            realPosition = static_cast<int>(GetOptionsByTypes(types).size() + 1);
        }
    }

    auto option = AppOption(optionType, valueType, realPosition, realShortName, longName, description, defaultValue, required, valueList);

    _options[option.GetShortName()] = option;
}

void AppOptions::Reset()
{
    _values.clear();
    _errors.clear();
}

list<string> AppOptions::GetErrors() const {
    return _errors;
}

bool AppOptions::IsValid() const {
    return _errors.empty();
}

bool AppOptions::IsHelp() {
    const auto value = GetOptionValue(HelpShortCode);
    return ValueConverter::IsBool(value)
        ? ValueConverter::ToBool(value)
        : false;
}

bool AppOptions::IsUsingDefaultOptionsFile() {
    const auto value = GetOptionValue(UseDefaultOptionsFileShortCode);
    return ValueConverter::IsBool(value)
        ? ValueConverter::ToBool(value)
        : false;
}
