#pragma once
#include "stdafx.h"

#include <string>

#ifndef DNX_UTILS_FILE_UTILS
#define DNX_UTILS_FILE_UTILS

// ReSharper disable CppInconsistentNaming

using namespace std;

namespace DNX {
    namespace Utils {
        //--------------------------------------------------------------------------
        // Class: FileUtils
        //--------------------------------------------------------------------------
        class FileUtils {
        public:
            static string GetFileNameOnly(const string filePath);
            static string GetFileNameAndExtension(const string filePath);
            static string ChangeFileExtension(const string filePath, const string fileExtension);
            static bool FileExists(const string& Filename);
        };
    }
}

#endif // DNX_UTILS_FILE_UTILS
