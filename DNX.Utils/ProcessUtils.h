#pragma once
#include "stdafx.h"

#include <string>

// ReSharper disable CppInconsistentNaming

using namespace std;

namespace DNX {
    namespace Utils {

        //--------------------------------------------------------------------------
        // Class: ProcessUtils
        //--------------------------------------------------------------------------
        class ProcessUtils
        {
        public:
            static string GetExecutableFileName();
        };

    }
}
