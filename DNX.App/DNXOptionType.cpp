#include "stdafx.h"
#include "DNXOptionType.h"

using namespace DNX::App;

// ReSharper disable CppInconsistentNaming

OptionTypeText::OptionTypeText() {
    SetText(OptionType::PARAMETER, "Parameter");
    SetText(OptionType::OPTION, "Option");
    SetText(OptionType::SWITCH, "+/-");
}
