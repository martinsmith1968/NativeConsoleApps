#include "stdafx.h"
#include "DNXAppDetails.h"
#include "../DNX.Utils/ProcessUtils.h"
#include "../DNX.Utils/FileUtils.h"
#include "../DNX.Utils/PathUtils.h"
#include <sstream>

// ReSharper disable CppInconsistentNaming

using namespace std;
using namespace DNX::App;
using namespace DNX::Utils;

AppDetails::AppDetails() = default;

AppDetails::~AppDetails() = default;

string AppDetails::GetHeaderLine() const
{
    ostringstream text;

    text << Name;

    if (!Version.empty())
    {
        text << " v" << Version;
    }

    if (!Description.empty())
    {
        text << " - " << Description;
    }

    return text.str();
}

string AppDetails::GetApplicationName()
{
    return FileUtils::GetFileNameOnly(ProcessUtils::GetExecutableFileNameOnly());
}

string AppDetails::GetOptionsFileNameOnly()
{
    const auto executableName = ProcessUtils::GetExecutableFileNameOnly();

    return FileUtils::ChangeFileExtension(executableName, "options");
}

string AppDetails::GetDefaultOptionsFileName()
{
    return PathUtils::Combine(ProcessUtils::GetExecutableFilePath(), GetOptionsFileNameOnly());
}

string AppDetails::GetLocalOptionsFileName()
{
    return PathUtils::Combine(PathUtils::GetCurrentDirectory(), GetOptionsFileNameOnly());
}
