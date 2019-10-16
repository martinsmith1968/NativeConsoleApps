#pragma once
#include "stdafx.h"

#ifndef DNX_APP_APP_DETAILS
#define DNX_APP_APP_DETAILS

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

            static string GetDefaultOptionsFileName();
        };
    }
}

#endif // DNX_APP_APP_DETAILS
