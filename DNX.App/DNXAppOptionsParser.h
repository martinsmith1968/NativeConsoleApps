﻿#pragma once
#include "DNXAppDetails.h"
#include "DNXAppOptions.h"

#ifndef DNX_APP_OPTIONS_PARSER
#define DNX_APP_OPTIONS_PARSER

using namespace std;

// ReSharper disable CppInconsistentNaming

namespace DNX {
    namespace App {
        //--------------------------------------------------------------------------
        // Class: AppOptionsParser
        //--------------------------------------------------------------------------
        class AppOptionsParser {
            static void ParseDefaultOptionsFile(AppOptions& options);
            static void ParseLocalOptionsFile(AppOptions& options);
            static void ParseOptionsFile(AppOptions& options, const string& fileName);
            static void ReadOptions(int argc, char** argv, AppOptions& options, const bool processOptionsFiles);
            static void ParseOptions(int argc, char** argv, AppOptions& options);

            static bool HandleParameter(AppOptions& options, int position, const string& value);
            static void HandleOption(AppOptions& options, const string& optionName, const string& value);
            static bool HandleSwitch(AppOptions& options, const string& optionName, bool switchOn);

            static void ValidateRequired(AppOptions& options);
            static void ValidateValues(AppOptions& options);

            static void ParseSingleArg(string arg, AppOptions& options, string& optionName, int& parameter);

            static list<string> ReadLinesFromFile(const string& fileName, AppOptions& options);

        public:
            static void Parse(int argc, char* argv[], AppOptions& options);
            static void ShowUsage(AppOptions& options, const AppDetails& appDetails);
            static void ShowErrors(const AppOptions& options);
        };
    }
}


#endif // DNX_APP_OPTIONS_PARSER
