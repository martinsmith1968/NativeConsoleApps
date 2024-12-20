#pragma once
#include "stdafx.h"

#include <string>

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
