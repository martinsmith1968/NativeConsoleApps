#include "stdafx.h"
#include "ProcessUtils.h"
#include "PathUtils.h"
#include "StringUtils.h"
#include <Windows.h>

// ReSharper disable CppInconsistentNaming

using namespace std;
using namespace DNX::Utils;

//--------------------------------------------------------------------------
// Class: ProcessUtils
//--------------------------------------------------------------------------

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
