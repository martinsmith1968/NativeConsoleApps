#ifndef DNX_UTILS_STRINGUTILS
#define DNX_UTILS_STRINGUTILS

#include "stdafx.h"
#include <algorithm>
#include <list>
#include <sstream>
#include <string>

// ReSharper disable CppInconsistentNaming

using namespace std;

namespace DNX {
    namespace Utils {
        namespace StringUtils {
            string Trim(const string& str, char removeChar = ' ');
            string LTrim(const string& str, char removeChar = ' ');
            string RTrim(const string& str, char removeChar = ' ');

            string ReplaceString(string subject, const string& search, const string& replace);

            string ToLower(string text);
            string ToUpper(string text);

            string Left(string text, size_t length);
            string Right(string text, size_t length);

            string BoolToString(bool value);

            list<string> SplitText(const string& str, char splitChar = ',', char trimChar = NULL);
            string JoinText(const list<string>& list, const string& delim);

            bool StartsWith(const string& str, const string& prefix);
            bool EndsWith(const string& str, const string& suffix);
            bool StartsAndEndsWith(const string& str, const string& prefixAndSuffix);

            string RemoveStartsWith(const string& str, const string& prefix);
            string RemoveEndsWith(const string& str, const string& suffix);
            string RemoveStartsAndEndsWith(const string& str, const string& prefixAndSuffix);
        }
    }
}

#endif // DNX_UTILS_STRINGUTILS
