#include "stdafx.h"
#include "ListUtils.h"

// ReSharper disable CppInconsistentNaming

using namespace std;
using namespace DNX::Utils;

//--------------------------------------------------------------------------
// Class: ListUtils
//--------------------------------------------------------------------------

list<string> ListUtils::ToList(const int argc, char* argv[], const int startAt)
{
    list<string> list;

    for (auto i=startAt; i < argc; ++i)
    {
        list.emplace_back(argv[i]);
    }

    return list;
}
