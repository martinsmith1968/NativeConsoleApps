#include "stdafx.h"
#include "ListUtils.h"

using namespace std;

// ReSharper disable CppInconsistentNaming

using namespace std;
using namespace DNX::Utils;

static list<string> ListUtils::ToList(const char* array[]) {
    list<string> list;

    for (auto i = 0; i < sizeof(array); ++i) {
        list.push_back(array[i]);
    }

    return list;
}
