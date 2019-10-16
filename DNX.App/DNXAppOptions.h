#pragma once
#include "stdafx.h"

#ifndef DNX_APP_OPTIONS
#define DNX_APP_OPTIONS

#include <list>
#include <map>
#include <string>
#include "DNXOptionType.h"
#include "DNXAppOption.h"
#include "DNXValueConverter.h"

using namespace std;

// ReSharper disable CppInconsistentNaming

namespace DNX {
    namespace App {
        //--------------------------------------------------------------------------
        // Class: AppOptions
        //--------------------------------------------------------------------------
        class AppOptions {
            map<string, AppOption> _options{};
            map<string, string> _values{};
            list<string> _errors{};

        protected:
            OptionTypeText OptionTypeText;

            void virtual PostParseValidate();

            void AddError(string text);
            void AddOptionWithValues(
                OptionType optionType,
                ValueType valueType,
                string shortName,
                string longName = "",
                string defaultValue = "",
                string description = "",
                bool required = false,
                int position = 0,
                string valueListText = ""
            );
            void AddOption(
                OptionType optionType,
                ValueType valueType,
                string shortName,
                string longName = "",
                string defaultValue = "",
                string description = "",
                bool required = false,
                int position = 0,
                list<string> valueList = list<string>()
            );

            list<AppOption> GetOptions();
            AppOption& GetOptionByLongName(string longName);
            AppOption& GetOptionByShortName(string shortName);
            AppOption& GetOptionByName(string name);
            list<AppOption> GetOptionsByType(OptionType optionType);
            list<AppOption> GetOptionsByTypes(list<OptionType> optionTypes);

            list<AppOption> GetRequiredOptions();

            string GetOptionValue(string name);
            void SetOptionValue(string name, string value);
            bool HasOptionValue(string name);

            friend class AppOptionsParser;

        public:
            AppOptions();
            virtual ~AppOptions() = default;

            void Reset();

            list<string> GetErrors() const;
            bool IsValid() const;
            bool IsHelp();
            bool IsUsingDefaultOptionsFile();

        };
    }
}

#endif // DNX_APP_OPTIONS
