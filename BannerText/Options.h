#pragma once
#include "stdafx.h"
#include <algorithm>
#include <string>
#include "../DNX.Utils/StringUtils.h"
#include "../DNX.App/Arguments.h"

// ReSharper disable CppInconsistentNaming
// ReSharper disable StringLiteralTypo
// ReSharper disable CppClangTidyModernizeReturnBracedInitList
// ReSharper disable CppClangTidyClangDiagnosticHeaderHygiene

using namespace std;
using namespace DNX::App;
using namespace DNX::Utils;

enum class TextAlignmentType : uint8_t
{
    LEFT,
    RIGHT,
    CENTER
};

class TextAlignmentTypeText : public EnumTextResolver<TextAlignmentType>
{
    public:
    TextAlignmentTypeText()
    {
        SetText(TextAlignmentType::LEFT, "Left");
        SetText(TextAlignmentType::RIGHT, "Right");
        SetText(TextAlignmentType::CENTER, "Center");
    }
};

class Options final : public Arguments
{
    TextAlignmentTypeText TextAlignmentTypeTextConverter;

    public:
    Options()
    {
        AddArgument(ArgumentType::PARAMETER, ValueType::STRING, "text", "message-text", "", "The Text to display", true);
        AddArgument(ArgumentType::OPTION, ValueType::CHAR, "hlc", "header-line-char", "*", "The character to use for header lines", false);
        AddArgument(ArgumentType::OPTION, ValueType::INT, "hln", "header-line-count", "1", "The number of header lines to print", false);
        AddArgument(ArgumentType::OPTION, ValueType::CHAR, "flc", "footer-line-char", "*", "The character to use for footer lines", false);
        AddArgument(ArgumentType::OPTION, ValueType::INT, "fln", "footer-line-count", "1", "The number of footer lines to print", false);
        AddArgument(ArgumentType::OPTION, ValueType::CHAR, "tlc", "text-line-char", "*", "The character to use for text line prefix/suffix", false);
        AddArgument(ArgumentType::OPTION, ValueType::INT, "tpc", "title-prefix-count", "2", "Set Title Prefix Count", false);
        AddArgument(ArgumentType::OPTION, ValueType::INT, "tsc", "title-suffix-count", "2", "Set Title Suffix Count", false);
        AddArgument(ArgumentType::OPTION, ValueType::INT, "tpgs", "title-prefix-gap-size", "2", "Set Title Prefix Gap Size", false);
        AddArgument(ArgumentType::OPTION, ValueType::INT, "tsgs", "title-suffix-gap-size", "2", "Set Title Suffix Gap Size", false);
        AddArgument(ArgumentType::OPTION, ValueType::ENUM, "ta", "text-alignment", "CENTER", "Set Text Alignment", false, 0, TextAlignmentTypeTextConverter.GetAllText());
        AddArgument(ArgumentType::OPTION, ValueType::INT, "minl", "min-total-length", "0", "Set Minimum Total line length", false);
        AddArgument(ArgumentType::OPTION, ValueType::INT, "maxl", "max-total-length", "0", "Set Maximum Total line length", false);
        AddArgument(ArgumentType::SWITCH, ValueType::BOOL, "x", "debug", "false", "Turn debugging on/off", false);
    }

    void PostParseValidate() override
    {
        if (!IsValid())
            return;

        const auto printableLineLength = GetTextPrintableLineLength();
        if (printableLineLength <= 0)
        {
            AddError(string("Maximum line length too restrictive: ") + to_string(printableLineLength));
        }
    }

    string GetMessageText()
    {
        return GetOptionValue("message-text");
    }

    char GetHeaderLineChar()
    {
        return ValueConverter::ToChar(GetOptionValue("hlc"));
    }

    size_t GetHeaderLineCount()
    {
        return ValueConverter::ToInt(GetOptionValue("hln"));
    }

    char GetFooterLineChar()
    {
        return ValueConverter::ToChar(GetOptionValue("flc"));
    }

    size_t GetFooterLineCount()
    {
        return ValueConverter::ToInt(GetOptionValue("fln"));
    }

    char GetTextLineChar()
    {
        return ValueConverter::ToChar(GetOptionValue("tlc"));
    }

    size_t GetTitlePrefixCount()
    {
        return ValueConverter::ToInt(GetOptionValue("tpc"));
    }

    size_t GetTitleSuffixCount()
    {
        return ValueConverter::ToInt(GetOptionValue("tsc"));
    }

    size_t GetTitlePrefixGapSize()
    {
        return ValueConverter::ToInt(GetOptionValue("tpgs"));
    }

    size_t GetTitleSuffixGapSize()
    {
        return ValueConverter::ToInt(GetOptionValue("tsgs"));
    }

    TextAlignmentType GetTextAlignment()
    {
        return TextAlignmentTypeTextConverter.GetValue(GetOptionValue("ta"));
    }

    size_t GetMinimumTotalLength()
    {
        return ValueConverter::ToInt(GetOptionValue("minl"));
    }

    size_t GetMaximumTotalLength()
    {
        return ValueConverter::ToInt(GetOptionValue("maxl"));
    }

    list<string> GetTextLines()
    {
        auto textLines = GetTextLinesToOutput();

        list<string> lines;
        for (auto iter = textLines.begin(); iter != textLines.end(); ++iter)
        {
            lines.push_back(GetFormattedTextLine(*iter));
        }

        return lines;
    }

    string GetFormattedTextLine(const string& text)
    {
        auto prefixGapSize    = GetTitlePrefixGapSize();
        auto suffixGapSize    = GetTitleSuffixGapSize();
        const auto textLength = text.length();

        if (GetMinimumTotalLength() > 0 || GetMaximumTotalLength() > 0)
        {
            switch (GetTextAlignment())
            {
                case TextAlignmentType::LEFT:
                    suffixGapSize = GetLineLength() - textLength - GetTitlePrefixCount() - GetTitlePrefixGapSize() - GetTitleSuffixCount();
                    break;
                case TextAlignmentType::RIGHT:
                    prefixGapSize = GetLineLength() - textLength - GetTitlePrefixCount() - GetTitleSuffixGapSize() - GetTitleSuffixCount();
                    break;
                case TextAlignmentType::CENTER:
                    const auto totalGapSize = GetLineLength() - textLength - GetTitlePrefixCount() - GetTitleSuffixCount();
                    prefixGapSize = totalGapSize / 2;
                    suffixGapSize = totalGapSize - prefixGapSize;
                    break;
            }
        }

        return GetTitlePrefixText()
               .append(string(prefixGapSize, ' '))
               .append(text)
               .append(string(suffixGapSize, ' '))
               .append(GetTitleSuffixText());
    }

    string GetHeaderLine()
    {
        return string(GetLineLength(), GetHeaderLineChar());
    }

    string GetFooterLine()
    {
        return string(GetLineLength(), GetFooterLineChar());
    }

    protected:
    size_t GetLineLength()
    {
        auto lineLength = GetMessageText().length()
            + (GetTitlePrefixCount() + GetTitlePrefixGapSize())
            + (GetTitleSuffixCount() + GetTitleSuffixGapSize());

        if (GetMinimumTotalLength() > 0)
        {
            lineLength = std::max(lineLength, GetMinimumTotalLength());
        }

        if (GetMaximumTotalLength() > 0)
        {
            lineLength = std::min(lineLength, GetMaximumTotalLength());
        }

        return lineLength;
    }

    size_t GetTextPrintableLineLength()
    {
        return GetLineLength()
            - GetTitlePrefixCount() - GetTitlePrefixGapSize()
            - GetTitleSuffixCount() - GetTitleSuffixCount();
    }

    list<string> GetTextLinesToOutput()
    {
        list<string> lines;

        const auto lineLength = GetTextPrintableLineLength();

        auto remainingText = GetMessageText();
        while (!remainingText.empty())
        {
            if (remainingText.length() > lineLength)
            {
                lines.push_back(remainingText.substr(0, lineLength));
                remainingText = remainingText.substr(lineLength, string::npos);
            }
            else
            {
                lines.push_back(remainingText);
                remainingText.clear();
            }
        }

        return lines;
    }

    string GetTitlePrefixText()
    {
        return string(GetTitlePrefixCount(), GetTextLineChar());
    }

    string GetTitleSuffixText()
    {
        return string(GetTitleSuffixCount(), GetTextLineChar());
    }
};
