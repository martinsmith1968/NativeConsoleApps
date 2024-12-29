#pragma once

#include <list>
#include <string>

// ReSharper disable CppInconsistentNaming
// ReSharper disable CppClangTidyClangDiagnosticHeaderHygiene

using namespace std;

namespace DNX::Utils
{
    //--------------------------------------------------------------------------
    // Class: ListUtils
    //--------------------------------------------------------------------------
    class ListUtils
    {
    public:
        static list<string> ToList(int argc, char* argv[], const int startAt = 0);

        template<class T>
        static T& GetAt(list<T>& list, const int index)
        {
            static T default_return_value;

            if (index < 0 || index >= list.size())
                return default_return_value;

            auto iter = list.begin();

            std::advance(iter, index);

            return *iter;
        }
    };
}
