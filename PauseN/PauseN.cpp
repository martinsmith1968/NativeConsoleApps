#include "stdafx.h"
#include <conio.h>
#include <ctime>
#include <iostream>
#include <regex>
#include "AppInfo.cpp"
#include "Options.cpp"
#include "../DNX.Utils/StringUtils.h"
#include "../DNX.App/DNXAppOptions.h"
#include "../DNX.App/DNXAppOptionsParser.h"
#include "../DNX.App/DNXAppOptionsParser.cpp"

using namespace DNX::App;
using namespace StringUtils;

// ReSharper disable CppInconsistentNaming

//------------------------------------------------------------------------------
// main
int main(const int argc, char* argv[])
{
    const AppInfo appInfo;

    Options options;
    AppOptionsParser::Parse(argc, argv, options);

    if (options.IsHelp())
    {
        AppOptionsParser::ShowUsage(options, appInfo);
        return 1;
    }
    if (!options.IsValid())
    {
        AppOptionsParser::ShowErrors(options);
        return 2;
    }

    cout << options.GetFormattedMessageText();

    const auto start_time = time(nullptr);
    const auto exit_time  = start_time + options.GetTimeoutSeconds();

    do
    {
        if (_kbhit())
        {
            auto key = _getch();
            break;
        }
    }
    while (time(nullptr) < exit_time || options.GetTimeoutSeconds() == 0);

    cout << endl;

    return 0;
}
