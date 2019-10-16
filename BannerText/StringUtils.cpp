#include "stdafx.h"
#include <algorithm>
#include <list>
#include <sstream>
#include <string>
#include "StringUtils.hpp"

using namespace std;

string Trim(const string& str, char removeChar)
{
    return LTrim(RTrim(str, removeChar), removeChar);
}

string LTrim(const string& str, char removeChar)
{
    auto first = str.find_first_not_of(removeChar);
    if (first == string::npos)
    {
        return str;
    }

    return str.substr(first, string::npos);
}

string RTrim(const string& str, char removeChar)
{
    auto last = str.find_last_not_of(removeChar);
    if (last == string::npos)
    {
        return str;
    }

    return str.substr(0, str.length() - last);
}

string ReplaceString(string subject, const string& search, const string& replace) {
    size_t pos = 0;

    while ((pos = subject.find(search, pos)) != string::npos)
    {
        subject.replace(pos, search.length(), replace);
        pos += replace.length();
    }

    return subject;
}

string ToLower(string text) {
    transform(text.begin(), text.end(), text.begin(), ::tolower);

    return text;
}

string ToUpper(string text) {
    transform(text.begin(), text.end(), text.begin(), ::toupper);

    return text;
}

string Left(string text, int length) {
    return text.substr(0, length);
}

string Right(string text, int length) {
    return text.substr(text.length() - length, string::npos);
}

string BoolToString(bool value) {
    return value
        ? "true"
        : "false";
}

list<string> SplitText(const string& str, char splitChar, char trimChar) {
    stringstream ss(str);

    list<string> list;

    while (ss.good())
    {
        string piece;
        getline(ss, piece, splitChar);

        if (trimChar != NULL) {
            piece = Trim(piece, trimChar);
        }

        if (!piece.empty()) {
            list.push_back(piece);
        }
    }

    return list;
}

string JoinText(const list<string>& list, string delim)
{
    ostringstream ss;

    for (auto iter = list.begin(); iter != list.end(); ++iter)
    {
        if (iter != list.begin()) {
            ss << delim;
        }

        ss << *iter;
    }

    return ss.str();
}

list<string> ToList(const char* arr[]) {
    list<string> list;

    for (auto i = 0; i < sizeof(arr); ++i) {
        list.push_back(arr[i]);
    }

    return list;
}
