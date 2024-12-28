#pragma once
#include "stdafx.h"
#include <ostream>

// ReSharper disable CppInconsistentNaming
// ReSharper disable CppClangTidyClangDiagnosticHeaderHygiene

using namespace std;

namespace DNX::Utils
{
    class ConsoleUtils
    {
    public:
        static void ShowBlankLines(const int count);
    };
}
