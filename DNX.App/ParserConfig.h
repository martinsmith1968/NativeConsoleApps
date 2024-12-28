#pragma once
#include "stdafx.h"
#include <string>

// ReSharper disable CppInconsistentNaming
// ReSharper disable CppClangTidyCppcoreguidelinesAvoidConstOrRefDataMembers
// ReSharper disable CppClangTidyClangDiagnosticHeaderHygiene

using namespace std;

namespace DNX::App
{
    //--------------------------------------------------------------------------
    // Class: ParserConfig
    //--------------------------------------------------------------------------
    class ParserConfig {
        static const string DefaultShortNamePrefix;
        static const string DefaultLongNamePrefix;
        static const string DefaultCustomOptionsFilePrefix;
        static constexpr bool DefaultUseGlobalOptionsFile  = true;
        static constexpr bool DefaultUseLocalOptionsFile   = true;
        static constexpr bool DefaultUseCustomOptionsFile  = true;
        static constexpr char DefaultSwitchOnSuffix = '+';
        static constexpr char DefaultSwitchOffSuffix = '-';

        string _shortNamePrefix;
        string _longNamePrefix;
        string _customOptionsFilePrefix;
        bool _useGlobalOptionsFile;
        bool _useLocalOptionsFile;
        bool _useCustomOptionsFile;
        char _switchOnSuffix;
        char _switchOffSuffix;

    public:
        [[nodiscard]] const string& GetShortNamePrefix() const { return _shortNamePrefix; }
        [[nodiscard]] const string& GetLongNamePrefix() const { return _longNamePrefix; }
        [[nodiscard]] const string& GetCustomOptionsFilePrefix() const { return _customOptionsFilePrefix; }
        [[nodiscard]] bool GetUseGlobalOptionsFile() const { return _useGlobalOptionsFile; }
        [[nodiscard]] bool GetUseLocalOptionsFile() const { return _useLocalOptionsFile; }
        [[nodiscard]] bool GetUseCustomOptionsFile() const { return _useCustomOptionsFile; }
        [[nodiscard]] char GetSwitchOnSuffix() const { return _switchOnSuffix; }
        [[nodiscard]] char GetSwitchOffSuffix() const { return _switchOffSuffix; }

        ParserConfig()
            : ParserConfig(
                DefaultShortNamePrefix,
                DefaultLongNamePrefix,
                DefaultCustomOptionsFilePrefix,
                DefaultUseGlobalOptionsFile,
                DefaultUseLocalOptionsFile,
                DefaultUseCustomOptionsFile,
                DefaultSwitchOnSuffix,
                DefaultSwitchOffSuffix
            )
        {
        }

        ParserConfig(
            const string& shortNamePrefix,
            const string& longNamePrefix,
            const string& customOptionsFilePrefix,
            const bool useGlobalOptionsFile,
            const bool useLocalOptionsFile,
            const bool useCustomOptionsFile,
            const char switchOnSuffix,
            const char switchOffSuffix
        )
        {
            _shortNamePrefix         = shortNamePrefix;
            _longNamePrefix          = longNamePrefix;
            _customOptionsFilePrefix = customOptionsFilePrefix;
            _useGlobalOptionsFile    = useGlobalOptionsFile;
            _useLocalOptionsFile     = useLocalOptionsFile;
            _useCustomOptionsFile    = useCustomOptionsFile;
            _switchOnSuffix          = switchOnSuffix;
            _switchOffSuffix         = switchOffSuffix;
        }
    };
}
