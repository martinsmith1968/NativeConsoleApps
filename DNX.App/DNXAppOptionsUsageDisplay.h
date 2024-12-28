#pragma once
#include "stdafx.h"
#include "AppDetails.h"
#include "DNXAppOptions.h"

// ReSharper disable CppInconsistentNaming
// ReSharper disable CppClangTidyCppcoreguidelinesSpecialMemberFunctions
// ReSharper disable CppClassCanBeFinal

namespace DNX::App
{
    //--------------------------------------------------------------------------
    // Class: DNXAppOptionsUsageDisplay
    //--------------------------------------------------------------------------
    class AppOptionsUsageDisplay
    {
    public:
        static void ShowUsage(const AppOptions& options, const AppDetails& appDetails);
        static void ShowErrors(const AppOptions& options, int blankLinesBefore = 0, int blankLinesAfter = 0);
    };
}
