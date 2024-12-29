#include "stdafx.h"
#include "AppInfo.h"
#include "AppArguments.h"
#include "../DNX.Utils/StringUtils.h"
#include "../DNX.App/ArgumentsParser.h"
#include "../DNX.App/ArgumentsUsageDisplay.h"
#include <iostream>
#include <regex>
#include <string>

// ReSharper disable CppInconsistentNaming
// ReSharper disable CppClangTidyPerformanceAvoidEndl
// ReSharper disable CppTooWideScopeInitStatement
// ReSharper disable CppTooWideScope

using namespace std;
using namespace DNX::App;
using namespace DNX::Utils;

//------------------------------------------------------------------------------
// Declarations
namespace BannerText {
    static void Execute(AppArguments& arguments);  // NOLINT(misc-use-anonymous-namespace)
}

//------------------------------------------------------------------------------
// main
int main(const int argc, char* argv[])
{
    try
    {
        const AppInfo appInfo;

        AppArguments arguments;
        ArgumentsParser::ParseArguments(arguments, argc, argv);

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

        BannerText::Execute(arguments);

        return 0;
    }
    catch (exception& ex)
    {
        cerr << ArgumentsUsageDisplay::ErrorLinePrefix << ": " << ex.what() << endl;
        return 99;
    }
    catch (...)
    {
        cerr << ArgumentsUsageDisplay::ErrorLinePrefix << ": Unknown error occurred" << endl;
        return 98;
    }
}

//------------------------------------------------------------------------------
// Execute
void BannerText::Execute(AppArguments& arguments)
{
    const auto header_line_count = arguments.GetHeaderLineCount();
    if (header_line_count > 0)
    {
        const auto header_line = arguments.GetHeaderLine();

        for (auto i = 0; i < static_cast<int>(header_line_count); ++i)
        {
            cout << header_line << endl;
        }
    }

    auto text_lines = arguments.GetTextLines();
    for (auto iter = text_lines.begin(); iter != text_lines.end(); ++iter)
    {
        cout << *iter << endl;
    }

    const auto footer_line_count = arguments.GetFooterLineCount();
    if (footer_line_count)
    {
        const auto footer_line = arguments.GetFooterLine();

        for (auto i = 0; i < static_cast<int>(arguments.GetFooterLineCount()); ++i)
        {
            cout << footer_line << endl;
        }
    }
}
