#pragma once
#include "stdafx.h"
#include "Arguments.h"
#include "AppDetails.h"
#include "ParserConfig.h"
#include <string>

// ReSharper disable CppInconsistentNaming
// ReSharper disable CppClangTidyCppcoreguidelinesAvoidConstOrRefDataMembers
// ReSharper disable CppClangTidyClangDiagnosticHeaderHygiene

using namespace std;

namespace DNX::App
{
    //--------------------------------------------------------------------------
    // Class: ArgumentsParser
    //--------------------------------------------------------------------------
    class ArgumentsParser
    {
        Arguments& _options;
        const ParserConfig _config;
        const AppDetails _app_details;

        void ParseOptionsFile(Arguments& options, const string& fileName) const;
        bool ParseArgument(const string& argumentName, const string& argumentValue, Arguments& options, bool& argumentValueConsumed) const;
        void ParseArguments(list<string> arguments, Arguments& options) const;

        static string SanitizeText(const string& text);
        static list<string> ConvertLinesToRawArguments(const list<string>& lines);

        static bool HandleAsSwitch(Arguments& options, const ParserConfig& config, const string& argumentName);
        static bool HandleAsOption(Arguments& options, const string& argumentName, const string& argumentValue);
        static bool HandleAsParameter(Arguments& options, int position, const string& argumentValue);

        static void ValidateRequired(Arguments& options);
        static void ValidateValues(Arguments& options);

    public:
        ArgumentsParser(Arguments& options, const AppDetails& app_details, const ParserConfig& config);
        void Parse(int argc, char* argv[]) const;

        static void ParseArguments(int argc, char* argv[], Arguments& options, const ParserConfig& config = ParserConfig());
    };
}
