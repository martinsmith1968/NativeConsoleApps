#pragma once
#include "stdafx.h"

#ifndef DNX_APP_VALUE_CONVERTER
#define DNX_APP_VALUE_CONVERTER

#include <string>
#include "DNXValueType.h"
#include "../DNX.Utils/StringUtils.h"

// ReSharper disable CppInconsistentNaming

using namespace std;
using namespace DNX::Utils::StringUtils;

namespace DNX {
    namespace App {
        //--------------------------------------------------------------------------
        // Class: ValueConverter
        //--------------------------------------------------------------------------
        class ValueConverter {
        public:
            static bool IsValueValid(string value, ValueType valueType);

            static bool IsChar(string value);
            static bool IsBool(string value);
            static bool IsInt(string value);
            static bool IsDouble(string value);
            static bool IsEnum(string value);
            static bool IsDate(string value);
            static bool IsDateTime(string value);

            static char ToChar(string value);
            static bool ToBool(string value);
            static int ToInt(string value);
            static double ToDouble(string value);
            static bool ToDate(string value, tm* date);
            static bool ToDateTime(string value, tm* datetime);
        };
    }
}

#endif // DNX_APP_VALUE_CONVERTER
