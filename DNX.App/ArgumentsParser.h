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
        Arguments& _arguments;
        const ParserConfig _config;
        const AppDetails _app_details;

        static string SanitizeText(const string& text);
        static list<string> ConvertLinesToRawArguments(const list<string>& lines);

        void ParseArgumentsFile(Arguments& arguments, const string& fileName) const;
        void ParseArguments(Arguments& arguments, list<string>& argumentsText) const;
        bool ParseArgument(Arguments& arguments, const string& argumentName, const string& argumentValue, bool& argumentValueConsumed) const;

        static bool HandleAsSwitch(Arguments& arguments, const ParserConfig& config, const string& argumentName);
        static bool HandleAsOption(Arguments& arguments, const string& argumentName, const string& argumentValue);
        static bool HandleAsParameter(Arguments& arguments, int position, const string& argumentValue);

        static void ValidateRequired(Arguments& arguments);
        static void ValidateValues(Arguments& arguments);

    public:
        explicit ArgumentsParser(Arguments& arguments, const AppDetails& app_details = AppDetails(), const ParserConfig& config = ParserConfig());
        void Parse(int argc, char* argv[]) const;

        static void ParseArguments(Arguments& arguments, int argc, char* argv[], const AppDetails& app_details = AppDetails(), const ParserConfig& config = ParserConfig());
    };
}
