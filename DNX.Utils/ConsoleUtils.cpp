#include "stdafx.h"
#include "ConsoleUtils.h"
#include <iostream>

// ReSharper disable CppClangTidyPerformanceAvoidEndl
// ReSharper disable CppInconsistentNaming

using namespace DNX::Utils;

void ConsoleUtils::ShowBlankLines(const int count)
{
    for (auto iter = 0; iter < count; ++iter)
    {
        cout << endl;
    }
}
