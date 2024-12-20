#ifndef DNX_UTILS_LISTUTILS
#define DNX_UTILS_LISTUTILS

#include "stdafx.h"
#include <list>
#include <string>

// ReSharper disable CppInconsistentNaming

using namespace std;

namespace DNX {
    namespace Utils {
        namespace ListUtils {
            static list<string> ToList(const char* array[]);
        }
    }
}

#endif // DNX_UTILS_LISTUTILS
