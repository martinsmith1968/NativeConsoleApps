#pragma once
#include "stdafx.h"
#include "../DNX.Utils/FileUtils.h"
#include "AppDetails.h"
#include "ArgumentType.h"
#include "Argument.h"
#include "ValueConverter.h"
#include <list>
#include <map>
#include <string>

// ReSharper disable CppInconsistentNaming
// ReSharper disable CppClangTidyCppcoreguidelinesAvoidConstOrRefDataMembers
// ReSharper disable CppClangTidyCppcoreguidelinesSpecialMemberFunctions
// ReSharper disable CppClangTidyClangDiagnosticHeaderHygiene

using namespace std;
using namespace DNX::Utils;

namespace DNX::App
{
    //--------------------------------------------------------------------------
    // Class: Arguments
    //--------------------------------------------------------------------------
    class Arguments
    {
        const string DebugShortName                 = "x";
        const string HelpShortName                  = "?";
        const string UseDefaultOptionsFileShortName = "@";
        const string UseLocalOptionsFileShortName   = "$";

        const string DebugLongName                 = "debug";
        const string HelpLongName                  = "help";
        const string UseDefaultOptionsFileLongName = "use-default-options-file";
        const string UseLocalOptionsFileLongName   = "use-local-options-file";

        const string HelpDescription           = "Show Help screen";
        const string DebugDescription          = "Activate debug mode";
        const string useDefaultOptionsFileDesc = "Use Default Options File (" + FileUtils::GetFileNameAndExtension(AppDetails::GetDefaultOptionsFileName()) + ")";
        const string useLocalOptionsFileDesc   = "Use Local Options File (" + FileUtils::GetFileNameAndExtension(AppDetails::GetDefaultOptionsFileName()) + ")";

        int _last_position = 0;
        map<string, Argument> _options{};
        map<string, string> _values{};
        list<string> _errors{};

        void AddArgumentWithValues(
            ArgumentType ArgumentType,
            ValueType valueType,
            const string& shortName,
            const string& longName = "",
            const string& defaultValue = "",
            const string& description = "",
            bool required = false,
            int position = 0,
            const string& valueListText = ""
        );

    protected:
        ArgumentTypeText ArgumentTypeText;

        void virtual PostParseValidate();

        void AddArgument(
            ArgumentType ArgumentType,
            ValueType valueType,
            const string& shortName,
            const string& longName = "",
            const string& defaultValue = "",
            const string& description = "",
            bool required = false,
            int position = 0,
            const list<string>& valueList = list<string>()
        );
        void AddSwitch(
            const string& shortName,
            const string& longName = "",
            const string& defaultValue = "",
            const string& description = "",
            bool required = false,
            int position = 0
        );

        void AddError(const string& text);

        [[nodiscard]] list<Argument> GetOptions() const;
        Argument& GetOptionByLongName(const string& longName);
        Argument& GetOptionByShortName(const string& shortName);
        Argument& GetOptionByName(const string& name);
        [[nodiscard]] Argument& GetParameterAtPosition(const int position);

        [[nodiscard]] list<Argument> GetRequiredOptions() const;

        string GetOptionValue(const string& name);
        void SetOptionValue(const string& name, const string& value);
        bool HasOptionValue(const string& name);

        friend class ArgumentsParser;

    public:
        Arguments();
        virtual ~Arguments() = default;

        void Reset();

        [[nodiscard]] list<Argument> GetOptionsByType(ArgumentType ArgumentType) const;
        [[nodiscard]] list<Argument> GetOptionsByTypes(const list<ArgumentType>& ArgumentTypes) const;

        [[nodiscard]] int GetNextPosition() const;
        void AdvancePosition();
        [[nodiscard]] list<string> GetErrors() const;
        [[nodiscard]] bool IsValid() const;
        bool IsDebug();
        bool IsHelp();
        bool IsUsingDefaultOptionsFile();

    };
}
