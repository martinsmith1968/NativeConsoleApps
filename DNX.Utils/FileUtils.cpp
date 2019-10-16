#include "stdafx.h"
#include "FileUtils.h"

#include <io.h>
#define ACCESS    _access_s

// ReSharper disable CppInconsistentNaming

using namespace std;
using namespace DNX::Utils;

//--------------------------------------------------------------------------
// Class: FileUtils
//--------------------------------------------------------------------------
string FileUtils::GetFileNameOnly(const string filePath)
{
    auto fileName = GetFileNameAndExtension(filePath);

    const auto lastFileExtSep = fileName.find_last_of('.');
    if (lastFileExtSep >= 0)
    {
        fileName = fileName.substr(0, lastFileExtSep);
    }

    return fileName;
}

string FileUtils::GetFileNameAndExtension(const string filePath)
{
    auto fileName = filePath;

    const auto lastPathSep = filePath.find_last_of('\\');
    if (lastPathSep >= 0)
    {
        fileName = filePath.substr(lastPathSep + 1);
    }

    return fileName;
}

string FileUtils::ChangeFileExtension(const string filePath, const string fileExtension)
{
    auto fileName = filePath;

    const auto lastFileExtSep = fileName.find_last_of('.');
    if (lastFileExtSep >= 0)
    {
        fileName = fileName.substr(0, lastFileExtSep);
    }

    if (fileExtension.length() > 0 && fileExtension.substr(0, 1) != ".")
    {
        fileName += '.';
    }

    fileName += fileExtension;

    return fileName;
}

bool FileUtils::FileExists(const string& Filename)
{
    return ACCESS(Filename.c_str(), 0) == 0;
}
