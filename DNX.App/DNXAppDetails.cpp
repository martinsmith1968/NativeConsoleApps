#include "stdafx.h"
#include "DNXAppDetails.h"
#include "../DNX.Utils/ProcessUtils.h"
#include "../DNX.Utils/FileUtils.h"

#include <sstream>

using namespace std;
using namespace DNX::App;
using namespace DNX::Utils;

// ReSharper disable CppInconsistentNaming

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
    const auto executableName = ProcessUtils::GetExecutableFileName();

    const auto fileName = FileUtils::GetFileNameOnly(executableName);

    return fileName;
}

string AppDetails::GetDefaultOptionsFileName()
{
    const auto executableName = ProcessUtils::GetExecutableFileName();

    auto defaultOptionsFileName = FileUtils::ChangeFileExtension(executableName, "options");

    return defaultOptionsFileName;
}
