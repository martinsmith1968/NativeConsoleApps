#include "stdafx.h"
#include "StringUtils.h"

#include <algorithm>

// ReSharper disable CppInconsistentNaming
// ReSharper disable CppClangTidyMiscUseAnonymousNamespace
// ReSharper disable CppClangTidyMiscUseInternalLinkage

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

string StringUtils::Trim(const string& str, const string& prefix_suffix)
{
    return RTrim(LTrim(str, prefix_suffix), prefix_suffix);
}

string StringUtils::LTrim(const string& str, const string& prefix)
{
    auto result = str;
    while (StartsWith(result, prefix))
        result = Right(result, result.length() - prefix.length());

    return result;
}

string StringUtils::RTrim(const string& str, const string& suffix)
{
    auto result = str;
    while (EndsWith(result, suffix))
        result = Left(result, result.length() - suffix.length());

    return result;
}

string StringUtils::Before(const string& str, const string& find)
{
    if (str.empty() || find.empty())
        return "";

    const auto pos = str.find(find);
    if (pos == string::npos)
        return "";

    return Left(str, pos);
}

string StringUtils::After(const string& str, const string& find)
{
    if (str.empty() || find.empty())
        return "";

    const auto pos = str.find(find);
    if (pos == string::npos)
        return "";

    return Right(str, str.length() - pos - find.length());

}

string StringUtils::BeforeLast(const string& str, const string& find)
{
    if (str.empty() || find.empty())
        return "";

    const auto pos = str.find_last_of(find);
    if (pos == string::npos)
        return "";

    return Left(str, pos);
}

string StringUtils::AfterLast(const string& str, const string& find)
{
    if (str.empty() || find.empty())
        return "";

    const auto pos = str.find_last_of(find);
    if (pos == string::npos)
        return "";

    return Right(str, str.length() - pos - find.length());

}

string StringUtils::Between(const string& str, const string& first, const string& second)
{
    return BeforeLast(After(str, first), second);
}

string StringUtils::BetweenInner(const string& str, const string& first, const string& second)
{
    return Before(AfterLast(str, first), second);
}


string StringUtils::ReplaceString(string subject, const string& search, const string& replace)
{
    size_t pos = 0;

    while ((pos = subject.find(search, pos)) != string::npos)
    {
        subject.replace(pos, search.length(), replace);
        pos += replace.length();
    }

    return subject;
}

string StringUtils::Repeat(const string& subject, const int count)
{
    // Source : https://stackoverflow.com/questions/166630/how-can-i-repeat-a-string-a-variable-number-of-times-in-c
    std::ostringstream os;
    for (int i = 0; i < count; i++)
        os << subject;
    return os.str();
}

string StringUtils::ToLower(const string& text)
{
    string copy = text;
    transform(copy.begin(), copy.end(), copy.begin(), tolower);

    return copy;
}

string StringUtils::ToUpper(const string& text)
{
    string copy = text;
    transform(copy.begin(), copy.end(), copy.begin(), toupper);

    return copy;
}

string StringUtils::Left(const string& text, const size_t length)
{
    return text.substr(0, length);
}

string StringUtils::Right(const string& text, const size_t length)
{
    return text.substr(text.length() - length, string::npos);
}

string StringUtils::BoolToString(const bool value, const string& trueValue, const string& falseValue)
{
    if (value)
        return trueValue;
    else
        return falseValue;
}

list<string> StringUtils::SplitText(const string& str, const char splitChar, const char trimChar)
{
    stringstream ss(str);

    list<string> list;

    while (ss.good())
    {
        string piece;
        getline(ss, piece, splitChar);

        if (trimChar != NULL)
        {
            piece = Trim(piece, trimChar);
        }

        if (!piece.empty())
        {
            list.push_back(piece);
        }
    }

    return list;
}

string StringUtils::JoinText(const list<string>& list, const string& delimiter)
{
    ostringstream ss;

    for (auto iter = list.begin(); iter != list.end(); ++iter)
    {
        if (iter != list.begin())
        {
            ss << delimiter;
        }

        ss << *iter;
    }

    return ss.str();
}

bool StringUtils::StartsWith(const string& str, const string& prefix)
{
    if (str.length() < prefix.length())
        return false;

    return Left(str, prefix.length()) == prefix;
}

bool StringUtils::EndsWith(const string& str, const string& suffix)
{
    if (str.length() < suffix.length())
        return false;

    return Right(str, suffix.length()) == suffix;
}

bool StringUtils::StartsAndEndsWith(const string& str, const string& prefixAndSuffix)
{
    return StartsWith(str, prefixAndSuffix) && EndsWith(str, prefixAndSuffix);
}

string StringUtils::RemoveStartsWith(const string& str, const string& prefix)
{
    if (str.length() < prefix.length())
        return str;

    string trimmedStr = str;
    while (StartsWith(trimmedStr, prefix))
    {
        trimmedStr = trimmedStr == prefix
            ? ""
            : trimmedStr.substr(prefix.length(), string::npos);
    }

    return trimmedStr;
}

string StringUtils::RemoveEndsWith(const string& str, const string& suffix)
{
    if (str.length() < suffix.length())
        return str;

    string trimmedStr = str;
    while (EndsWith(trimmedStr, suffix))
    {
        trimmedStr = trimmedStr == suffix
            ? ""
            : trimmedStr.substr(0, trimmedStr.length() - suffix.length());
    }

    return trimmedStr;
}

string StringUtils::RemoveStartsAndEndsWith(const string& str, const string& prefixAndSuffix)
{
    return RemoveStartsWith(RemoveEndsWith(str, prefixAndSuffix), prefixAndSuffix);
}
