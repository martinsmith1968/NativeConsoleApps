#pragma once
#include "stdafx.h"
#include "DNXAppOptions.h"
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
        AppOptions& _options;
        const ParserConfig _config;
        const AppDetails _app_details;

        void ParseOptionsFile(AppOptions& options, const string& fileName) const;
        bool ParseArgument(const string& argumentName, const string& argumentValue, AppOptions& options, bool& argumentValueConsumed) const;
        void ParseArguments(list<string> arguments, AppOptions& options) const;

        static string SanitizeText(const string& text);
        static list<string> ConvertLinesToRawArguments(const list<string>& lines);

        static bool HandleAsSwitch(AppOptions& options, const ParserConfig& config, const string& argumentName);
        static bool HandleAsOption(AppOptions& options, const string& argumentName, const string& argumentValue);
        static bool HandleAsParameter(AppOptions& options, int position, const string& argumentValue);

        static void ValidateRequired(AppOptions& options);
        static void ValidateValues(AppOptions& options);

    public:
        ArgumentsParser(AppOptions& options, const AppDetails& app_details, const ParserConfig& config);
        void Parse(int argc, char* argv[]) const;

        static void ParseArguments(int argc, char* argv[], AppOptions& options, const ParserConfig& config = ParserConfig());
    };
}
