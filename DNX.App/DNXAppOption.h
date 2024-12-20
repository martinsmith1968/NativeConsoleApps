#pragma once
#include "stdafx.h"

#include "DNXOptionType.h"
#include "DNXValueType.h"

// ReSharper disable CppInconsistentNaming

using namespace std;
using namespace DNX::App;

namespace DNX {
    namespace App {
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
            list<string> _valueList{};

        protected:
            OptionTypeText OptionTypeTextHelper;

        public:
            bool IsEmpty() const;

            OptionType GetOptionType() const;
            ValueType GetValueType() const;
            string GetShortName() const;
            string GetLongName() const;
            string GetDescription() const;
            string GetDefaultValue() const;
            bool GetRequired() const;
            int GetPosition() const;
            list<string> GetValueList() const;

            bool HasLongName() const;
            string GetNameDescription() const;

            AppOption();

            AppOption(
                OptionType optionType,
                ValueType valueType,
                int position,
                const string& shortName,
                const string& longName = "",
                const string& description = "",
                const string& defaultValue = "",
                bool required = false,
                const list<string>& valueList = list<string>()
            );

            static AppOption& Empty();
            static bool CompareByPosition(const AppOption& first, const AppOption& second);
            static bool CompareByTypeAndPosition(const AppOption& first, const AppOption& second);
        };
    }
}
