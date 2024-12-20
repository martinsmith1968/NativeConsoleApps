#pragma once
#include "stdafx.h"
#include <string>
#include "DNXAppOptions.h"
#include "DNXAppDetails.h"

using namespace std;

// ReSharper disable CppInconsistentNaming

namespace DNX {
    namespace App {
        //--------------------------------------------------------------------------
        // Class: AppArgumentsParser
        //--------------------------------------------------------------------------
        class AppArgumentsParser {
            static void ParseDefaultOptionsFile(AppOptions& options);
            static void ParseLocalOptionsFile(AppOptions& options);
            static void ParseOptionsFile(AppOptions& options, const string& fileName);
            static void ReadOptions(const int argc, char* argv[], AppOptions& options, const bool processOptionsFiles);
            static void ParseOptions(int argc, char** argv, AppOptions& options);

            static bool HandleParameter(AppOptions& options, int position, const string& value);
            static void HandleOption(AppOptions& options, const string& optionName, const string& value);
            static bool HandleSwitch(AppOptions& options, const string& optionName, bool switchOn);

            static void ValidateRequired(AppOptions& options);
            static void ValidateValues(AppOptions& options);

            static void ParseSingleArg(string arg, AppOptions& options, string& optionName, int& parameter);

            static list<string> ReadLinesFromFile(const string& fileName, AppOptions& options);

            static void ShowBlankLines(const int count);

        public:
            static void Parse(int argc, char* argv[], AppOptions& options);
            static void ShowUsage(const AppOptions& options, const AppDetails& appDetails);
            static void ShowErrors(const AppOptions& options, const int blankLinesBefore = 0, const int blankLinesAfter = 0);
        };
    }
}
