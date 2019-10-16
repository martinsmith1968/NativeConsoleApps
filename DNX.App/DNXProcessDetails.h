#pragma once
#include "stdafx.h"
#include <string>

#ifndef DNX_APP_PROCESS_DETAILS
#define DNX_APP_PROCESS_DETAILS

// ReSharper disable CppInconsistentNaming

using namespace std;

namespace DNX {
    namespace App {

        //--------------------------------------------------------------------------
        // Class: ProcessDetails
        //--------------------------------------------------------------------------
        class ProcessDetails {
        public:
            static string GetExecutableFileName();
        };

    }
}

#endif // DNX_APP_PROCESS_DETAILS
