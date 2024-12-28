#pragma once
#include "stdafx.h"
#include <string>

// ReSharper disable CppInconsistentNaming
// ReSharper disable CppClangTidyClangDiagnosticHeaderHygiene

using namespace std;

namespace DNX::App
{
    //--------------------------------------------------------------------------
    // Class: AppOptionsSwitchValue
    //--------------------------------------------------------------------------
    class AppOptionsSwitchValue {
        string _name;
        bool _value;

    public:
        [[nodiscard]] string GetName() const;
        [[nodiscard]] bool GetValue() const;

        AppOptionsSwitchValue(const string& name, bool value);

        static AppOptionsSwitchValue ParseSwitchDetails(const string& optionName);
    };
}
