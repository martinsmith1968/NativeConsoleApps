#pragma once
#include "stdafx.h"
#include "../DNX.Utils/EnumUtils.h"

// ReSharper disable CppInconsistentNaming
// ReSharper disable CppClangTidyPerformanceEnumSize
// ReSharper disable CppClangTidyClangDiagnosticHeaderHygiene

using namespace DNX::Utils::EnumUtils;

namespace DNX::App
{
    //--------------------------------------------------------------------------
    // Enum: OptionType
    //--------------------------------------------------------------------------
    enum class OptionType : uint8_t
    {
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
