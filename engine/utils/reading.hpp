#pragma once
#include <iostream>
#include "../../extensions/nlohmann/json.hpp"
using json = nlohmann::json;


namespace rd
{
    std::string join(const std::string& path, const std::string& file);

    template<typename T>
    T get(const json& from, const std::string& key, const T& defValue)
    {
        return from.contains(key)? T(from[key]) : defValue;
    };
}