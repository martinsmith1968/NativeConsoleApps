#include "stdafx.h"
#include "EnumUtils.h"

// ReSharper disable CppInconsistentNaming

using namespace std;
using namespace DNX::Utils::EnumUtils;

/*
enum class Bob
{
    One, Two
};

class BobTextResolver : public EnumTextResolver<Bob>
{
public:
    BobTextResolver() {
        SetText(Bob::One, "One");
        SetText(Bob::Two, "Two");
    }
};
*/


/*
class TextAlignmentHelper { // TOOD: This is shit
public:
    static map<TextAlignment, string> GetValues() {
        map<TextAlignment, string> map;

        map[TextAlignment::LEFT] = "LEFT";
        map[TextAlignment::RIGHT] = "RIGHT";
        map[TextAlignment::CENTER] = "CENTER";

        return map;
    }

    static string ToText(TextAlignment value) {
        auto values = GetValues();

        auto item = values.find(value);
        if (item == values.end()) {
            throw new exception("Unknown TextAlignment value");
        }

        return item->second;
    }

    static TextAlignment ToValue(string text) {
        auto values = GetValues();

        for (auto iter = values.begin(); iter != values.end(); ++iter) {
            if (iter->second == text) {
                return iter->first;
            }
        }

        throw new exception((string("Unknown TextAlignment value: ") + text).c_str());
    }

    static list<string> ToTextArray() {
        auto values = GetValues();

        list<string> list;

        for (auto iter = values.begin(); iter != values.end(); ++iter) {
            list.push_back(iter->second);
        }

        return list;
    }
};
*/
