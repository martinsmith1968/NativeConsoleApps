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

            void AddError(const string& text);
            void AddOptionWithValues(
                OptionType optionType,
                ValueType valueType,
                const string& shortName,
                const string& longName = "",
                const string& defaultValue = "",
                const string& description = "",
                bool required = false,
                int position = 0,
                const string& valueListText = ""
            );
            void AddOption(
                OptionType optionType,
                ValueType valueType,
                const string& shortName,
                const string& longName = "",
                const string& defaultValue = "",
                const string& description = "",
                bool required = false,
                int position = 0,
                const list<string>& valueList = list<string>()
            );

            list<AppOption> GetOptions();
            AppOption& GetOptionByLongName(const string& longName);
            AppOption& GetOptionByShortName(const string& shortName);
            AppOption& GetOptionByName(const string& name);
            list<AppOption> GetOptionsByType(OptionType optionType);
            list<AppOption> GetOptionsByTypes(const list<OptionType>& optionTypes);

            list<AppOption> GetRequiredOptions();

            string GetOptionValue(const string& name);
            void SetOptionValue(const string& name, const string& value);
            bool HasOptionValue(const string& name);

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
