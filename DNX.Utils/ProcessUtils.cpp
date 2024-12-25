#include "stdafx.h"
#include "ProcessUtils.h"

#include <Windows.h>

#include "PathUtils.h"
#include "StringUtils.h"

using namespace std;
using namespace DNX::Utils;

// ReSharper disable CppInconsistentNaming

string ProcessUtils::GetExecutableFileName()
{
    wchar_t buffer[MAX_PATH];
    const auto length = GetModuleFileName(nullptr, buffer, MAX_PATH);

    wstring ws(buffer, length);

    string str(ws.begin(), ws.end());

    return str;
}

string ProcessUtils::GetExecutableFileNameOnly()
{
    return StringUtils::AfterLast(GetExecutableFileName(), PathUtils::PATH_SEPARATOR);
}

string ProcessUtils::GetExecutableFilePath()
{
    return StringUtils::BeforeLast(GetExecutableFileName(), PathUtils::PATH_SEPARATOR);
}
