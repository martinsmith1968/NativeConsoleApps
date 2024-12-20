#pragma once
#include "stdafx.h"

#include <ostream>
#include <sstream>
#include <string>
#include <vector>

// ReSharper disable CppClangTidyPerformanceAvoidEndl
// ReSharper disable CppInconsistentNaming

using namespace std;

// Source : https://stackoverflow.com/questions/53164946/c-approach-to-handling-a-collection-of-multiple-exceptions
class AggregateException : public std::exception
{
private:
    std::vector<std::exception> _exceptions;
    std::string _whatMessage;

public:
    explicit AggregateException(std::vector<std::exception> exceptions)
    {
        _exceptions = std::move(exceptions);

        std::stringstream what_string;
        what_string << "AggregateException:" << endl;
        for (auto const& ex : _exceptions) {
            what_string << " " << ex.what() << endl;
        }
        _whatMessage = what_string.str();
    }


    const char* what() const noexcept override {
        return _whatMessage.c_str();
    }

    std::vector<std::exception> GetExceptions() const
    {
        return _exceptions;
    }
};
