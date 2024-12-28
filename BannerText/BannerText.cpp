#include "stdafx.h"
#include "AppInfo.h"
#include "Options.h"
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

        BannerText::Execute(options);

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
void BannerText::Execute(Options& options)
{
    const auto header_line_count = options.GetHeaderLineCount();
    if (header_line_count > 0)
    {
        const auto header_line = options.GetHeaderLine();

        for (auto i = 0; i < static_cast<int>(header_line_count); ++i)
        {
            cout << header_line << endl;
        }
    }

    auto text_lines = options.GetTextLines();
    for (auto iter = text_lines.begin(); iter != text_lines.end(); ++iter)
    {
        cout << *iter << endl;
    }

    const auto footer_line_count = options.GetFooterLineCount();
    if (footer_line_count)
    {
        const auto footer_line = options.GetFooterLine();

        for (auto i = 0; i < static_cast<int>(options.GetFooterLineCount()); ++i)
        {
            cout << footer_line << endl;
        }
    }
}
