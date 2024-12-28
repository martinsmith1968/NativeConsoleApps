﻿#pragma once
#include "stdafx.h"
#include "ArgumentType.h"
#include "ValueType.h"

// ReSharper disable CppInconsistentNaming
// ReSharper disable CppClangTidyClangDiagnosticHeaderHygiene

using namespace std;
using namespace DNX::App;

namespace DNX::App
{
    //--------------------------------------------------------------------------
    // Class: AppOption
    //--------------------------------------------------------------------------
    class AppOption
    {
        ArgumentType _argumentType;
        ValueType _valueType;
        string _shortName;
        string _longName;
        string _description;
        string _defaultValue;
        bool _required;
        uint8_t _position;
        list<string> _valueList{};

    protected:
        ArgumentTypeText ArgumentTypeTextHelper;

    public:
        [[nodiscard]] bool IsEmpty() const;

        [[nodiscard]] ArgumentType GetArgumentType() const;
        [[nodiscard]] ValueType GetValueType() const;
        [[nodiscard]] string GetShortName() const;
        [[nodiscard]] string GetLongName() const;
        [[nodiscard]] string GetDescription() const;
        [[nodiscard]] string GetDefaultValue() const;
        [[nodiscard]] bool GetRequired() const;
        [[nodiscard]] uint8_t GetPosition() const;
        [[nodiscard]] list<string> GetValueList() const;

        [[nodiscard]] bool HasLongName() const;
        [[nodiscard]] string GetNameDescription() const;

        AppOption();

        AppOption(
            ArgumentType argumentType,
            ValueType valueType,
            uint8_t position,
            const string& shortName,
            const string& longName = "",
            const string& description = "",
            const string& defaultValue = "",
            bool required = false,
            const list<string>& valueList = list<string>()
        );

        static AppOption _app_option;
        static AppOption& Empty() { return _app_option; }

        static bool CompareByPosition(const AppOption& first, const AppOption& second);
        static bool CompareByTypeAndPosition(const AppOption& first, const AppOption& second);
    };
}
