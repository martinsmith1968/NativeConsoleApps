#include "stdafx.h"
#include "StringUtils.h"

// ReSharper disable CppInconsistentNaming

using namespace std;
using namespace DNX::Utils;

//--------------------------------------------------------------------------
// Class: StringUtils
//--------------------------------------------------------------------------
string StringUtils::Trim(const string& str, const char removeChar)
{
    return LTrim(RTrim(str, removeChar), removeChar);
}

string StringUtils::LTrim(const string& str, const char removeChar)
{
    const auto first = str.find_first_not_of(removeChar);
    if (first == string::npos)
    {
        return str;
    }

    return str.substr(first, string::npos);
}

string StringUtils::RTrim(const string& str, const char removeChar)
{
    const auto last = str.find_last_not_of(removeChar);
    if (last == string::npos)
    {
        return str;
    }

    return str.substr(0, str.length() - last);
}

string StringUtils::ReplaceString(string subject, const string& search, const string& replace) {
    size_t pos = 0;

    while ((pos = subject.find(search, pos)) != string::npos)
    {
        subject.replace(pos, search.length(), replace);
        pos += replace.length();
    }

    return subject;
}

string StringUtils::ToLower(string text) {
    transform(text.begin(), text.end(), text.begin(), ::tolower);

    return text;
}

string StringUtils::ToUpper(string text) {
    transform(text.begin(), text.end(), text.begin(), ::toupper);

    return text;
}

string StringUtils::Left(string text, const size_t length) {
    return text.substr(0, length);
}

string StringUtils::Right(string text, const size_t length) {
    return text.substr(text.length() - length, string::npos);
}

string StringUtils::BoolToString(const bool value) {
    return value
        ? "true"
        : "false";
}

list<string> StringUtils::SplitText(const string& str, const char splitChar, const char trimChar) {
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

string StringUtils::JoinText(const list<string>& list, const string& delim)
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

bool StringUtils::StartsWith(const string& str, const string& prefix) {
    if (str.length() < prefix.length())
        return false;

    return Left(str, prefix.length()) == prefix;
}

bool StringUtils::EndsWith(const string& str, const string& suffix) {
    if (str.length() < suffix.length())
        return false;

    return Right(str, suffix.length()) == suffix;
}

bool StringUtils::StartsAndEndsWith(const string& str, const string& prefixAndSuffix) {
    return StartsWith(str, prefixAndSuffix) && EndsWith(str, prefixAndSuffix);
}

string StringUtils::RemoveStartsWith(const string& str, const string& prefix) {
    if (str.length() < prefix.length())
        return str;

    auto trimmedStr = str;
    while (StartsWith(trimmedStr, prefix)) {
        trimmedStr = trimmedStr == prefix
            ? ""
            : trimmedStr.substr(prefix.length(), string::npos);
    }

    return trimmedStr;
}

string StringUtils::RemoveEndsWith(const string& str, const string& suffix) {
    if (str.length() < suffix.length())
        return str;

    auto trimmedStr = str;
    while (EndsWith(trimmedStr, suffix)) {
        trimmedStr = trimmedStr == suffix
            ? ""
            : trimmedStr.substr(0, trimmedStr.length() - suffix.length());
    }

    return trimmedStr;
}

string StringUtils::RemoveStartsAndEndsWith(const string& str, const string& prefixAndSuffix) {
    return RemoveStartsWith(RemoveEndsWith(str, prefixAndSuffix), prefixAndSuffix);
}
