#include "stdafx.h"
#include "AppInfo.h"
#include "Options.h"
#include "../DNX.Utils/StringUtils.h"
#include "../DNX.App/ArgumentsParser.h"
#include "../DNX.App/ArgumentsUsageDisplay.h"
#include <conio.h>
#include <chrono>
#include <ctime>
#include <iostream>
#include <regex>
#include <thread>

// ReSharper disable CppInconsistentNaming
// ReSharper disable CppClangTidyPerformanceAvoidEndl

using namespace std;
using namespace DNX::App;
using namespace DNX::Utils;

//------------------------------------------------------------------------------
// Declarations
namespace PauseN {
    static void Execute(Options& options);  // NOLINT(misc-use-anonymous-namespace)
};

//------------------------------------------------------------------------------
// main
int main(const int argc, char* argv[])
{
    try
    {
        const AppInfo appInfo;

        Options options;
        ArgumentsParser::ParseArguments(argc, argv, options);

        if (options.IsHelp())
        {
            ArgumentsUsageDisplay::ShowUsage(options, appInfo);
            return 1;
        }
        if (!options.IsValid())
        {
            ArgumentsUsageDisplay::ShowUsage(options, appInfo);
            ArgumentsUsageDisplay::ShowErrors(options, 1);
            return 2;
        }

        PauseN::Execute(options);

        return 0;
    }
    catch (exception& ex)
    {
        cerr << "ERROR: " << ex.what() << endl;
        return 99;
    }
    catch (...)
    {
        cerr << "ERROR: Unknown error occurred" << endl;
        return 98;
    }
}

//------------------------------------------------------------------------------
// Execute
void PauseN::Execute(Options& options)
{
    cout << options.GetFormattedMessageText();

    const auto start_time = time(nullptr);
    const auto exit_time  = start_time + options.GetTimeoutSeconds();
    const auto sleep_time = std::chrono::milliseconds(options.GetSleepMilliseconds());

    do
    {
        if (_kbhit())
        {
            _getch();
            break;
        }

        std::this_thread::sleep_for(sleep_time);
    } while (time(nullptr) < exit_time || options.GetTimeoutSeconds() == 0);

    cout << endl;
}
