#include "stdafx.h"
#include "../DNX.App/DNXAppDetails.h"
#include "AppInfo.h"

using namespace DNX::App;

// ReSharper disable CppInconsistentNaming

//------------------------------------------------------------------------------
// AppInfo
class AppInfo final : public AppDetails
{
public:
    AppInfo()
    {
        Name        = VER_PRODUCTNAME_STR;
        Description = VER_FILE_DESCRIPTION_STR;
        Version     = VER_FILE_VERSION_STR;
        Copyright   = VER_COPYRIGHT_STR;
    }
};
