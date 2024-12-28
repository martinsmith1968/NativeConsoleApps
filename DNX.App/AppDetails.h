#pragma once
#include "stdafx.h"
#include <string>

// ReSharper disable CppInconsistentNaming
// ReSharper disable CppClangTidyClangDiagnosticHeaderHygiene
// ReSharper disable CppClangTidyCppcoreguidelinesSpecialMemberFunctions

using namespace std;

namespace DNX::App
{
    //--------------------------------------------------------------------------
    // Class: AppDetails
    //--------------------------------------------------------------------------
    class AppDetails
    {
        static string _options_file_extension;

    public:
        string Name;
        string Version;
        string Description;
        string Copyright;

        AppDetails();
        virtual ~AppDetails();

        [[nodiscard]] string virtual GetHeaderLine() const;

        static string GetApplicationName();

        static string GetArgumentsFileNameOnly();
        static string GetDefaultArgumentsFileName();
        static string GetLocalArgumentsFileName();
    };
}
