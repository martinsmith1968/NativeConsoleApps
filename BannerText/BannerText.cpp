#include "stdafx.h"
#include <iostream>
#include <string>
#include <regex>
#include "AppInfo.cpp"
#include "Options.cpp"
#include "../DNX.Utils/StringUtils.h"
#include "../DNX.App/DNXAppOptions.h"
#include "../DNX.App/DNXAppOptionsParser.h"
#include "../DNX.App/DNXAppOptionsParser.cpp"

using namespace std;
using namespace DNX::App;
using namespace StringUtils;

// ReSharper disable CppInconsistentNaming

//------------------------------------------------------------------------------
// main
int main(const int argc, char* argv[])
{
    try
    {
        const AppInfo app_info;

        Options options;
        AppOptionsParser::Parse(argc, argv, options);

        if (options.IsHelp())
        {
            AppOptionsParser::ShowUsage(options, app_info);
            return 1;
        }

        if (!options.IsValid())
        {
            AppOptionsParser::ShowErrors(options);
            return 2;
        }

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

        return 0;
    }
    catch (exception ex)
    {
        cerr << "Error: " << ex.what() << endl;
        return 99;
    }
    catch (...)
    {
        cerr << "Error: Unknown error occurred" << endl;
        return 98;
    }
}
