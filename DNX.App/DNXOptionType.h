#pragma once
#include "stdafx.h"

#ifndef DNX_APP_OPTION_TYPE
#define DNX_APP_OPTION_TYPE

#include "../DNX.Utils/EnumUtils.h"

// ReSharper disable CppInconsistentNaming

using namespace DNX::Utils::EnumUtils;

namespace DNX {
    namespace App {
        //--------------------------------------------------------------------------
        // Enum: OptionType
        //--------------------------------------------------------------------------
        enum class OptionType {
            PARAMETER,
            OPTION,
            SWITCH
        };


        //--------------------------------------------------------------------------
        // Class: OptionTypeText
        //--------------------------------------------------------------------------
        class OptionTypeText : public EnumTextResolver<OptionType>
        {
        public:
            OptionTypeText();
        };
    }
}

#endif // DNX_APP_OPTION_TYPE
