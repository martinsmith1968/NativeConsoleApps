#include "stdafx.h"
#include "AppInfo.h"
#include "AppArguments.h"
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
    static void Execute(AppArguments& arguments);  // NOLINT(misc-use-anonymous-namespace)
};

//------------------------------------------------------------------------------
// main
int main(const int argc, char* argv[])
{
    try
    {
        const AppInfo appInfo;

        AppArguments arguments;
        ArgumentsParser::ParseArguments(argc, argv, arguments);

        if (arguments.IsHelp())
        {
            ArgumentsUsageDisplay::ShowUsage(arguments, appInfo);
            return 1;
        }
        if (!arguments.IsValid())
        {
            ArgumentsUsageDisplay::ShowUsage(arguments, appInfo);
            ArgumentsUsageDisplay::ShowErrors(arguments, 1);
            return 2;
        }

        PauseN::Execute(arguments);

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
void PauseN::Execute(AppArguments& arguments)
{
    cout << arguments.GetFormattedMessageText();

    const auto start_time = time(nullptr);
    const auto exit_time  = start_time + arguments.GetTimeoutSeconds();
    const auto sleep_time = std::chrono::milliseconds(arguments.GetSleepMilliseconds());

    do
    {
        if (_kbhit())
        {
            _getch();
            break;
        }

        std::this_thread::sleep_for(sleep_time);
    } while (time(nullptr) < exit_time || arguments.GetTimeoutSeconds() == 0);

    cout << endl;
}
