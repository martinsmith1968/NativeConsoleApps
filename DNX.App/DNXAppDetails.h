#pragma once
#include "stdafx.h"

#include <string>

// ReSharper disable CppInconsistentNaming

using namespace std;

namespace DNX {
    namespace App {
        //--------------------------------------------------------------------------
        // Class: AppDetails
        //--------------------------------------------------------------------------
        class AppDetails
        {
        public:
            string Name;
            string Version;
            string Description;
            string Copyright;

            AppDetails();
            virtual ~AppDetails();

            string virtual GetHeaderLine() const;

            static string GetApplicationName();

            static string GetOptionsFileNameOnly();
            static string GetDefaultOptionsFileName();
            static string GetLocalOptionsFileName();
        };
    }
}
