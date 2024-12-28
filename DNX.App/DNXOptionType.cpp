#include "stdafx.h"
#include "DNXOptionType.h"

// ReSharper disable CppInconsistentNaming

using namespace DNX::App;

OptionTypeText::OptionTypeText()
{
    SetText(OptionType::PARAMETER, "Parameter");
    SetText(OptionType::OPTION, "Option");
    SetText(OptionType::SWITCH, "+/-");
}
