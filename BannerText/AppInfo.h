#pragma once

// ReSharper disable IdentifierTypo

#include "BuildInfo.h"
#include "..\Common\Version.h"
#include "Macros.h"

#define VER_PRODUCTNAME_STR         "BannerText"
#define VER_FILE_DESCRIPTION_STR    "Generate and display a Text Banner in the console"
#define VER_COMPANY_NAME            "DNX Solutions Ltd"
#define VER_COPYRIGHT_STR           "Copyright © 2018-" TO_STR(COPYRIGHT_YEAR) " " VER_COMPANY_NAME

#define VER_FILE_VERSION            VERSION_MAJOR, VERSION_MINOR, VERSION_REVISION, VERSION_BUILD
#define VER_FILE_VERSION_STR        TO_STR(VERSION_MAJOR)        \
                                    "." TO_STR(VERSION_MINOR)    \
                                    "." TO_STR(VERSION_REVISION) \
                                    "." TO_STR(VERSION_BUILD)

#define VER_PRODUCT_VERSION         VERSION_MAJOR, VERSION_MINOR
#define VER_PRODUCT_VERSION_STR     TO_STR(VERSION_MAJOR)        \
                                    "." TO_STR(VERSION_MINOR)
#define VER_ORIGINAL_FILENAME_STR   VER_PRODUCTNAME_STR ".exe"
#define VER_INTERNAL_NAME_STR       VER_ORIGINAL_FILENAME_STR

#define VER_COMMENTS                "Build Timestamp : " BUILD_DATETIME

#ifdef _DEBUG
#define VER_VER_DEBUG               VS_FF_DEBUG
#else
#define VER_VER_DEBUG               0
#endif

#define VER_FILEOS                  VOS_NT_WINDOWS32
#define VER_FILEFLAGS               VER_VER_DEBUG
#define VER_FILETYPE                VFT_APP
