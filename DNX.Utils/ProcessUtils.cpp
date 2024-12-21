#include "stdafx.h"
#include "ProcessUtils.h"

#include <Windows.h>

using namespace std;
using namespace DNX::Utils;

// ReSharper disable CppInconsistentNaming

/// <summary>
/// Gets the name of the executable file.
/// </summary>
/// <returns>string.</returns>
string ProcessUtils::GetExecutableFileName()
{
    wchar_t buffer[MAX_PATH];
    const auto length = GetModuleFileName(nullptr, buffer, MAX_PATH);

    wstring ws(buffer, length);

    string str(ws.begin(), ws.end());

    return str;
}
