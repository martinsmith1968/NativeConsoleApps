#include "stdafx.h"
#include "ListUtils.h"

using namespace std;

// ReSharper disable CppInconsistentNaming

namespace DNX {
    namespace Utils {
        namespace ListUtils {
            list<string> ToList(const char* arr[]) {
                list<string> list;

                for (auto i = 0; i < sizeof(arr); ++i) {
                    list.push_back(arr[i]);
                }

                return list;
            }
        }
    }
}
