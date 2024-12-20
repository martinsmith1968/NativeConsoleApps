#include "stdafx.h"
#include <iostream>
#include <regex>
#include <string>

#include "AppInfo.h"
#include "Options.cpp"
#include "../DNX.Utils/StringUtils.h"
#include "../DNX.App/DNXAppArgumentsParser.h"

using namespace std;
using namespace DNX::App;
using namespace DNX::Utils;

// ReSharper disable CppInconsistentNaming

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
        AppArgumentsParser::Parse(argc, argv, options);

        if (options.IsHelp())
        {
            AppArgumentsParser::ShowUsage(options, appInfo);
            return 1;
        }
        if (!options.IsValid())
        {
            AppArgumentsParser::ShowUsage(options, appInfo);
            AppArgumentsParser::ShowErrors(options, 1);
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
        auto header_line = options.GetHeaderLine();

        for (auto i = 0; i < header_line_count; ++i)
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
        auto footer_line = options.GetFooterLine();

        for (auto i = 0; i < options.GetFooterLineCount(); ++i)
        {
            cout << footer_line << endl;
        }
    }
}

