#include "stdafx.h"
#include "DNXAppOptionsSwitchValue.h"

using namespace std;
using namespace DNX::App;
using namespace DNX::Utils::StringUtils;

// ReSharper disable CppInconsistentNaming

string AppOptionsSwitchValue::GetName() const {
    return _name;
}
bool AppOptionsSwitchValue::GetValue() const {
    return _value;
}

AppOptionsSwitchValue::AppOptionsSwitchValue(const string name, const bool value) {
    _name  = name;
    _value = value;
}

AppOptionsSwitchValue AppOptionsSwitchValue::ParseSwitchDetails(const string optionName) {
    auto realName = optionName;
    auto value = true;

    const auto switchValue = Right(optionName, 1);
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
