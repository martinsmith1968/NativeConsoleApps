#pragma once
#include "stdafx.h"

#ifndef DNX_UTILS_ENUM_UTILS
#define DNX_UTILS_ENUM_UTILS

#include <list>
#include <map>
#include <string>

// ReSharper disable CppInconsistentNaming

using namespace std;

namespace DNX {
    namespace Utils {
        namespace EnumUtils {

            // TODO: Introduce text categories by value of T
            template <class T>
            class EnumTextResolver {
                map<T, string> _map;

            protected:
                void SetText(const T value, const string text) {
                    _map[value] = text;
                }

            public:
                string GetText(const T value) const {
                    for (auto iter = _map.begin(); iter != _map.end(); ++iter) {
                        if (iter->first == value) {
                            return iter->second;
                        }
                    }
                    return nullptr;
                }

                T GetValue(const string text) const {
                    for (auto iter = _map.begin(); iter != _map.end(); ++iter) {
                        if (iter->second == text) {
                            return iter->first;
                        }
                    }
                    return T();
                }

                list<string> GetAllText() const {
                    list<string> list;

                    for (auto iter = _map.begin(); iter != _map.end(); ++iter) {
                        list.push_back(iter->second);
                    }

                    return list;
                }

                list<T> GetAllValues() const {
                    list<T> list;

                    for (auto iter = _map.begin(); iter != _map.end(); ++iter) {
                        list.push_back(iter->first);
                    }

                    return list;
                }
            };
        }
    }
}

#endif
