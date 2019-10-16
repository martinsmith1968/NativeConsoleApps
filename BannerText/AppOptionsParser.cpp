#include "stdafx.h"
#include "StringUtils.hpp"
#include <algorithm>
#include <iterator>
#include <iostream>
#include <iomanip>
#include <string>
#include <list>
#include <map>
#include "../DNX.App/DNXAppDetails.h"
#include "../DNX.Utils/EnumUtils.h"

// ReSharper disable CppInconsistentNaming

#ifndef APPOPTIONSPARSER
#define APPOPTIONSPARSER

using namespace std;
using namespace DNX::App;
using namespace DNX::Utils::EnumUtils;

namespace AppOptionsParser {

    //--------------------------------------------------------------------------
    // Enum: ValueType
    //--------------------------------------------------------------------------
    enum ValueType {
        CHAR,
        STRING,
        BOOL,
        INT,
        DOUBLE,
        ENUM,
        DATE,
        DATETIME
    };


    //--------------------------------------------------------------------------
    // Class: ValueTypeText
    //--------------------------------------------------------------------------
    class ValueTypeText : EnumTextResolver<ValueType>
    {
    public:
        ValueTypeText() {
            SetText(CHAR, "Char");
            SetText(STRING, "String");
            SetText(BOOL, "Bool");
            SetText(INT, "Integer");
            SetText(DOUBLE, "Number");
            SetText(ENUM, "Value");
            SetText(DATE, "Date");
            SetText(DATETIME, "Date and Time");
        }
    };


    //--------------------------------------------------------------------------
    // Enum: OptionType
    //--------------------------------------------------------------------------
    enum OptionType {
        PARAMETER,
        OPTION,
        SWITCH
    };


    //--------------------------------------------------------------------------
    // Class: ValueTypeText
    //--------------------------------------------------------------------------
    class OptionTypeText : EnumTextResolver<OptionType>
    {
    public:
        OptionTypeText() {
            SetText(PARAMETER, "Parameter");
            SetText(OPTION, "Option");
            SetText(SWITCH, "Switch");
        }
    };


    //--------------------------------------------------------------------------
    // Class: AppOptionValueConverter
    //--------------------------------------------------------------------------
    class AppOptionValueConverter {
    public:
        static bool IsValueValid(const string& value, ValueType valueType) {
            switch (valueType) {
                case CHAR:
                    return IsChar(value);
                case STRING:
                    return !value.empty();
                case BOOL:
                    return IsBool(value);
                case INT:
                    return IsInt(value);
                    //case DOUBLE:
                    //    return isDouble(value);
                case ENUM:
                    return true;    // TODO: Needs fixing
                //    return isEnum(value);
                //case DATE:
                //    return isDate(value);
                //case DATETIME:
                //    return isDateTime(value);
                default:
                    return false;
            }
        }

        static string GetDescription(ValueType valueType) {
            switch (valueType) {
                case CHAR: return "CHAR";
                case STRING: return "TEXT";
                case BOOL: return "[+/-]";
                case INT: return "NUM";
                case DOUBLE: return "NUM";
                case ENUM: return "VALUE";
                case DATE: return "DATE";
                case DATETIME: return "DATETIME";
                default: return "";
            }
        }

        static bool IsChar(const string& value) {
            return !value.empty();
        }

        static bool IsBool(const string& value) {
            return !value.empty()
                && (ToLower(value) == "true" || ToLower(value) == "false");
        }

        static bool IsInt(const string& value) {
            if (value.empty() || ((!isdigit(value[0])) && (value[0] != '-') && (value[0] != '+')))
                return false;

            char * p;
            strtol(value.c_str(), &p, 10);

            return (*p == 0);
        }

        static char ToChar(const string& value) {
            return value.at(0);
        }

        static bool ToBool(const string& value) {
            if (ToLower(value) == "true")
                return true;
            if (ToLower(value) == "false")
                return false;

            throw new exception((string("Invalid boolean vaue: ") + value).c_str());
        }

        static int ToInt(const string& value) {
            return stoi(value);
        }
    };


    //--------------------------------------------------------------------------
    // Class: AppOption
    //--------------------------------------------------------------------------
    class AppOption {
        OptionType _optionType;
        ValueType _valueType;
        string _shortName;
        string _longName;
        string _description;
        string _defaultValue;
        bool _required;
        int _position;
        list<string> _valueList;

    public:
        OptionType getOptionType() const {
            return _optionType;
        }
        ValueType getValueType() const {
            return _valueType;
        }
        const string getShortName() const {
            return _shortName;
        }
        const string getLongName() const {
            return _longName;
        }
        const string getDescription() const {
            return _description;
        }
        const string getDefaultValue() const {
            return _defaultValue;
        }
        bool getRequired() const {
            return _required;
        }
        int getPosition() const {
            return _position;
        }
        list<string> getValueList() {
            return _valueList;
        }

        bool hasLongName() const {
            return !_longName.empty();
        }

        const string getNameDescription() const {
            string description;

            switch (_optionType) {
                case PARAMETER:
                    description = "Parameter";
                    break;
                case OPTION:
                    description = "Option";
                    break;
                case SWITCH:
                    description = "Switch";
                    break;
            }

            if (!description.empty()) {
                description += ": ";
            }

            description += _shortName;

            return description;
        }

        AppOption() :
            _optionType(PARAMETER),
            _valueType(STRING),
            _required(false),
            _position(0) {
        }


        AppOption(
            OptionType optionType,
            ValueType valueType,
            int position,
            string shortName,
            string longName = "",
            string description = "",
            string defaultValue = "",
            bool required = false,
            list<string> valueList = list<string>()
        )
        {
            _optionType = optionType;
            _valueType = valueType;
            _shortName = shortName;
            _longName = longName;
            _description = description;
            _defaultValue = defaultValue;
            _required = required;
            _position = position;
        }

        static bool CompareByPosition(const AppOption& first, const AppOption& second)
        {
            return first.getPosition() < second.getPosition();
        }

        static bool CompareByTypeAndPosition(const AppOption& first, const AppOption& second)
        {
            if (first.getOptionType() != second.getOptionType()) {
                return first.getOptionType() < second.getOptionType();
            }

            return first.getPosition() < second.getPosition();
        }
    };


    //--------------------------------------------------------------------------
    // Class: AppOptionsBase
    //--------------------------------------------------------------------------
    class AppOptionsBase
    {
    private:
        map<string, AppOption> _options;
        map<string, string> _values;
        list<string> _errors;

    protected:
        AppOptionValueConverter Converter;
        friend class AppOptionParser;

        void addError(string text) {
            _errors.push_back(text);
        }

        list<AppOption> getOptions() {
            auto types = { PARAMETER, OPTION, SWITCH };

            return getOptionsByTypes(types);
        }

        const AppOption* getOptionByLongName(string longName) {
            for (auto iter = _options.begin(); iter != _options.end(); ++iter) {
                if (iter->second.hasLongName() && iter->second.getLongName() == longName) {
                    return &iter->second;
                }
            }

            return NULL;
        }

        const AppOption* getOptionByShortName(string shortName) {
            auto iter = _options.find(shortName);
            return iter == _options.end()
                ? NULL
                : &iter->second;
        }

        const AppOption* getOptionByName(string name) {
            auto property = getOptionByShortName(name);
            return property == NULL
                ? getOptionByLongName(name)
                : property;
        }

        list<AppOption> getOptionsByType(OptionType optionType) {
            list<AppOption> filtered;

            for (auto iter = _options.begin(); iter != _options.end(); ++iter) {
                if (iter->second.getOptionType() == optionType) {
                    filtered.push_back(iter->second);
                }
            }

            return filtered;
        }

        list<AppOption> getOptionsByTypes(list<OptionType> optionTypes) {
            list<AppOption> filtered;

            for (auto iter = _options.begin(); iter != _options.end(); ++iter) {
                auto found = std::find(std::begin(optionTypes), std::end(optionTypes), iter->second.getOptionType()) != std::end(optionTypes);
                if (found) {
                    filtered.push_back(iter->second);
                }
            }

            return filtered;
        }

        list<AppOption> getRequiredOptions() {
            list<AppOption> filtered;

            auto typeList = getOptions();
            for (auto iter = typeList.begin(); iter != typeList.end(); ++iter) {
                if (iter->getRequired()) {
                    filtered.push_back(*iter);
                }
            }

            return filtered;
        }

        string getOptionValue(string name) {
            auto option = getOptionByName(name);
            if (option == NULL)
                throw new exception((string("Unknown Option: ") + name).c_str());

            auto iter = _values.find(option->getShortName());
            return iter == _values.end()
                ? option->getDefaultValue()
                : iter->second;
        }

        void setOptionValue(string name, string value) {
            auto option = getOptionByName(name);
            if (option == NULL)
                throw new exception((string("Unknown Option: ") + name).c_str());

            _values[option->getShortName()] = value;
        }

        bool hasOptionValue(string name) {
            auto option = getOptionByName(name);
            if (option == NULL)
                throw new exception((string("Unknown Option: ") + name).c_str());

            return _values.find(option->getShortName()) != _values.end();
        }

        void virtual postParseValidate() {

        }

        void addOptionWithValues(
            OptionType optionType,
            ValueType valueType,
            string shortName,
            string longName = "",
            string defaultValue = "",
            string description = "",
            bool required = false,
            int position = 0,
            string valueListText = ""
        )
        {
            auto valueList = list<string>();

            if (!valueListText.empty()) {
                valueList = SplitText(valueListText, ',');
            }

            addOption(optionType, valueType, shortName, longName, defaultValue, description, required, position, valueList);
        }

        void addOption(
            OptionType optionType,
            ValueType valueType,
            string shortName,
            string longName = "",
            string defaultValue = "",
            string description = "",
            bool required = false,
            int position = 0,
            list<string> valueList = list<string>()
        )
        {
            if (getOptionByShortName(shortName) != NULL)
                throw new exception((string("Option already exists: ") + shortName).c_str());
            if (getOptionByLongName(longName) != NULL)
                throw new exception((string("Option already exists: ") + longName).c_str());

            if (optionType == PARAMETER) {
                position = getOptionsByType(PARAMETER).size() + 1;
                shortName = to_string(position);

                if (longName.empty()) {
                    throw new exception((string("Parameter must have a long name: ") + shortName).c_str());
                }
            }
            else {
                if (AppOptionValueConverter::IsInt(shortName))
                    throw new exception((string("Invalid Option Name: ") + shortName).c_str());

                if (position == 0) {
                    auto types = { OPTION, SWITCH };
                    position = getOptionsByTypes(types).size() + 1;
                }
            }

            auto option = AppOption(optionType, valueType, position, shortName, longName, description, defaultValue, required, valueList);

            _options[option.getShortName()] = option;
        }

        AppOptionsBase() {
            addOption(SWITCH, BOOL, "h", "help", "false", "Show Help screen", false, INT_MAX);
        }

    public:
        virtual ~AppOptionsBase() = default;


        list<string> getErrors() {
            return _errors;
        }

        bool isHelp() {
            return Converter.ToBool(getOptionValue("h"));
        }

        bool isValid() {
            return _errors.size() == 0;
        }
    };


    //--------------------------------------------------------------------------
    // Class: AppOptionsSwitchValue
    //--------------------------------------------------------------------------
    class AppOptionsSwitchValue {
    private:
        string _name;
        bool _value;

    public:
        const string getName() const {
            return _name;
        }
        const bool getValue() const {
            return _value;
        }

        AppOptionsSwitchValue(string name, bool value) {
            _name = name;
            _value = value;
        }

        static AppOptionsSwitchValue ParseSwitchDetails(string optionName) {
            auto realName = optionName;
            auto value = true;

            auto switchValue = Right(optionName, 1);
            if (switchValue == "-") {
                value = false;
                realName = Left(optionName, optionName.length() - 1);
            }
            else if (switchValue == "+") {
                value = true;
                realName = Left(optionName, optionName.length() - 1);
            }

            return AppOptionsSwitchValue(realName, value);
        }
    };


    //--------------------------------------------------------------------------
    // Class: AppOptionParser
    //--------------------------------------------------------------------------
    class AppOptionParser {
    public:
        static void Parse(int argc, char* argv[], AppOptionsBase& options) {
            string optionName = "";
            int parameter = 0;

            for (auto i = 1; i < argc; ++i)
            {
                string arg = argv[i];

                // Handle long name options
                if (arg.substr(0, 2) == "--")
                {
                    auto argNameAndValue = arg.substr(2, string::npos);

                    auto equals_pos = argNameAndValue.find("=");
                    auto hasValue = equals_pos != string::npos;

                    auto argName = hasValue
                        ? argNameAndValue.substr(0, equals_pos - 1)
                        : argNameAndValue;

                    auto argValue = hasValue
                        ? arg.substr(equals_pos + 1, string::npos)
                        : "";

                    auto option = options.getOptionByLongName(argName);
                    if (option == NULL) {
                        options.addError(string("Unknown option: ") + argName);
                        continue;
                    }

                    auto shortName = option->getShortName();
                    if (hasValue) {
                        HandleOption(options, shortName, argValue);
                    }
                    else {
                        auto switchInfo = AppOptionsSwitchValue::ParseSwitchDetails(optionName);

                        HandleSwitch(options, switchInfo.getName(), switchInfo.getValue());
                    }

                    continue;
                }

                // Parse Option Name
                if (arg.substr(0, 1) == "-")
                {
                    optionName = arg.substr(1, string::npos);

                    auto switchInfo = AppOptionsSwitchValue::ParseSwitchDetails(optionName);

                    // Handle as a switch ?
                    HandleSwitch(options, switchInfo.getName(), switchInfo.getValue());
                    continue;
                }

                // Handle as an option or parameter ?
                if (optionName.empty()) {
                    HandleParameter(options, ++parameter, arg);
                }
                else {
                    HandleOption(options, optionName, arg);
                }

                // Reset for next iteration
                optionName = "";
            }

            // Validate
            ValidateRequired(options);
            ValidateValues(options);
            options.postParseValidate();
        }

        static void ShowUsage(AppOptionsBase& options, AppInfo& appInfo) {
            auto parameters = options.getOptionsByType(PARAMETER);
            parameters.sort(AppOption::CompareByPosition);

            auto optionsAndSwitchesTypes = { PARAMETER, OPTION, SWITCH };
            auto optionsAndSwitches = options.getOptionsByTypes(optionsAndSwitchesTypes);
            optionsAndSwitches.sort(AppOption::CompareByTypeAndPosition);

            auto hasOptions = !optionsAndSwitches.empty();

            string parameterText;
            for (auto iter = parameters.begin(); iter != parameters.end(); ++iter) {
                parameterText
                    .append(" [")
                    .append(iter->getLongName())
                    .append("]")
                    ;
            }

            if (hasOptions) {
                if (!parameterText.empty()) {
                    parameterText.append(" ");
                }

                parameterText.append("[OPTIONS]");
            }

            cout << appInfo.getHeaderLine() << std::endl;
            cout << appInfo.Copyright << std::endl;
            cout << std::endl;
            cout << "Usage:" << std::endl;
            cout << appInfo.Name << parameterText << std::endl;

            if (hasOptions) {
                cout << std::endl;
                cout << "OPTIONS:" << std::endl;

                list<tuple<AppOption, string, string>> optionDescriptions;

                size_t maxOptionDescripionLength = 0;
                for (auto iter = optionsAndSwitches.begin(); iter != optionsAndSwitches.end(); ++iter) {
                    string optionDesc;
                    if (iter->getOptionType() == PARAMETER) {
                        optionDesc = "[" + iter->getLongName() + "]";
                    }
                    else {
                        optionDesc = "-" + iter->getShortName();
                        if (iter->hasLongName()) {
                            optionDesc += ", --" + iter->getLongName();
                        }
                    }
                    optionDesc += " " + AppOptionValueConverter::GetDescription(iter->getValueType());

                    if (optionDesc.length() > maxOptionDescripionLength) {
                        maxOptionDescripionLength = optionDesc.length();
                    }

                    auto textDesc = iter->getDescription();

                    list<string> textDescParts;

                    if (iter->getRequired()) {
                        textDescParts.push_back("Required");
                    }
                    if (!iter->getDefaultValue().empty()) {
                        textDescParts.push_back("Default:" + iter->getDefaultValue());
                    }
                    if (!iter->getValueList().empty()) {
                        auto valueListText = JoinText(iter->getValueList(), ", ");

                        textDescParts.push_back("Values: " + valueListText);
                    }

                    if (!textDescParts.empty()) {
                        textDesc += " (";

                        auto index = 0;
                        for (auto iter = textDescParts.begin(); iter != textDescParts.end(); ++iter) {
                            if (index > 0) {
                                textDesc += ", ";
                            }

                            textDesc += *iter;

                            ++index;
                        }

                        textDesc += ")";
                    }

                    auto optionAndDesc = tuple<AppOption, string, string>(*iter, optionDesc, textDesc);

                    optionDescriptions.push_back(optionAndDesc);
                }

                for (auto iter = optionDescriptions.begin(); iter != optionDescriptions.end(); ++iter) {
                    std::cout << std::left << std::setfill(' ') << std::setw(maxOptionDescripionLength + 2) << std::get<1>(*iter)
                        << std::get<2>(*iter)
                        << std::endl;
                }
            }
        }

        static void ShowErrors(AppOptionsBase& options) {
            for (auto iter = options.getErrors().begin(); iter != options.getErrors().end(); ++iter) {
                cout << "Error: " << *iter << endl;
            }
        }

    private:
        static void HandleParameter(AppOptionsBase& options, int position, string value) {
            auto optionName = to_string(position);

            auto sw = options.getOptionByShortName(optionName);
            if (sw == NULL) {
                options.addError(string("Unexpected parameter at position: " + optionName));
                return;
            }
            if (sw->getOptionType() != PARAMETER) {
                return;
            }

            options.setOptionValue(optionName, value);
        }

        static void HandleOption(AppOptionsBase& options, string optionName, string value) {
            auto sw = options.getOptionByShortName(optionName);
            if (sw == NULL) {
                options.addError(string("Unknown option: " + optionName));
                return;
            }
            if (sw->getOptionType() != OPTION) {
                return;
            }

            options.setOptionValue(optionName, value);
        }

        static void HandleSwitch(AppOptionsBase& options, string optionName, bool switchOn) {
            auto sw = options.getOptionByShortName(optionName);
            if (sw == NULL) {
                options.addError(string("Unknown switch: " + optionName));
                return;
            }
            if (sw->getOptionType() != SWITCH) {
                return;
            }

            options.setOptionValue(optionName, BoolToString(switchOn));
        }

        static void ValidateRequired(AppOptionsBase& options) {
            auto requiredOptions = options.getRequiredOptions();

            for (auto iter = requiredOptions.begin(); iter != requiredOptions.end(); ++iter) {
                if (!options.hasOptionValue(iter->getShortName())) {
                    options.addError(iter->getNameDescription() + " is required");
                }
            }
        }

        static void ValidateValues(AppOptionsBase& options) {
            auto optionList = options.getOptions();

            for (auto iter = optionList.begin(); iter != optionList.end(); ++iter) {
                const auto optionValue = options.getOptionValue(iter->getShortName());
                if (!AppOptionValueConverter::IsValueValid(optionValue, iter->getValueType())) {
                    options.addError(iter->getNameDescription() + " value is invalid (" + optionValue + ")");
                }
            }
        }
    };

#endif // !APPOPTIONSPARSER



    /*

    string header_line_char;
    string footer_line_char;
    int header_line_count;
    int footer_line_count;
    int title_prefix_count;
    int title_suffix_count;
    int title_prefix_gap_size;
    int title_suffix_gap_size;
    int minimum_total_length;
    int maximum_total_length;
    text_alignment text_alignment;

    */
}
