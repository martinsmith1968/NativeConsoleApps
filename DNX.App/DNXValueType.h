#pragma once
#include "stdafx.h"

#ifndef DNX_APP_VALUE_TYPE
#define DNX_APP_VALUE_TYPE

#include "../DNX.Utils/EnumUtils.h"

// ReSharper disable CppInconsistentNaming

using namespace DNX::Utils::EnumUtils;

namespace DNX {
    namespace App {
        //--------------------------------------------------------------------------
        // Enum: ValueType
        //--------------------------------------------------------------------------
        enum class ValueType {
            CHAR,
            STRING,
            BOOL,
            INT,
            DOUBLE,
            ENUM,
            DATE,
            DATETIME
        };

        //--------------------------------------------------------------------------
        // Class: ValueTypeText
        //--------------------------------------------------------------------------
        class ValueTypeText : public EnumTextResolver<ValueType>
        {
        public:
            ValueTypeText();
        };

        static ValueTypeText ValueTypeTextConverter;
    }
}

#endif // DNX_APP_VALUE_TYPE
