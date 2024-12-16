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
            static bool IsValueValid(const string& value, ValueType valueType);

            static bool IsChar(const string& value);
            static bool IsBool(const string& value);
            static bool IsInt(const string& value);
            static bool IsDouble(const string& value);
            static bool IsEnum(const string& value);
            static bool IsDate(const string& value);
            static bool IsDateTime(const string& value);

            static char ToChar(const string& value);
            static bool ToBool(const string& value);
            static int ToInt(const string& value);
            static double ToDouble(const string& value);
            static bool ToDate(const string& value, tm* date);
            static bool ToDateTime(const string& value, tm* datetime);
        };
    }
}

#endif // DNX_APP_VALUE_CONVERTER
