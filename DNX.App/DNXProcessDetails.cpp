#include "stdafx.h"
#include "DNXProcessDetails.h"

#include <Windows.h>

using namespace std;
using namespace DNX::App;

// ReSharper disable CppInconsistentNaming

/// <summary>
/// Gets the name of the executable file.
/// </summary>
/// <returns>string.</returns>
string ProcessDetails::GetExecutableFileName()
{
    wchar_t buffer[MAX_PATH];
    auto length = GetModuleFileName(nullptr, buffer, MAX_PATH);

    wstring ws(buffer);

    string str(ws.begin(), ws.end());

    return str;
}
