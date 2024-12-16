#pragma once
#include "stdafx.h"

#ifndef DNX_APP_OPTIONS_SWITCH_VALUE
#define DNX_APP_OPTIONS_SWITCH_VALUE

#include <string>
#include "../DNX.Utils/StringUtils.h"

// ReSharper disable CppInconsistentNaming

using namespace std;

namespace DNX {
    namespace App {
        //--------------------------------------------------------------------------
        // Class: AppOptionsSwitchValue
        //--------------------------------------------------------------------------
        class AppOptionsSwitchValue {
            string _name;
            bool _value;

        public:
            string GetName() const;
            bool GetValue() const;

            AppOptionsSwitchValue(const string& name, bool value);

            static AppOptionsSwitchValue ParseSwitchDetails(const string& optionName);
        };
    }
}

#endif // DNX_APP_OPTIONS_SWITCH_VALUE
