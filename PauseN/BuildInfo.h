#pragma once

#include "Macros.h"

#define BUILD_DATE      TO_STR(__DATE__)
#define BUILD_TIME      TO_STR(__TIME__)
#define BUILD_DATETIME  BUILD_DATE " " BUILD_TIME
