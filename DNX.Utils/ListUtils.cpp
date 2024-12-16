#include "stdafx.h"
#include "ListUtils.h"

using namespace std;

// ReSharper disable CppInconsistentNaming

namespace DNX {
    namespace Utils {
        namespace ListUtils {
            list<string> ToList(const char* array[]) {
                list<string> list;

                for (auto i = 0; i < sizeof(array); ++i) {
                    list.push_back(array[i]);
                }

                return list;
            }
        }
    }
}
