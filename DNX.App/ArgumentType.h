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
    // Enum: ArgumentType
    //--------------------------------------------------------------------------
    enum class ArgumentType : uint8_t
    {
        PARAMETER,
        OPTION,
        SWITCH
    };


    //--------------------------------------------------------------------------
    // Class: ArgumentTypeText
    //--------------------------------------------------------------------------
    class ArgumentTypeText : public EnumTextResolver<ArgumentType>
    {
    public:
        ArgumentTypeText();
    };
}
