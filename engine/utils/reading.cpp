#include "reading.hpp"


std::string rd::join(const std::string& path, const std::string& file)
{
    if (path.back() == '/')
        return path + file;
    else
        return path + "/" + file;
}


// template<typename T>
// T rd::get(const json& from, const std::string& key, const T& defValue)
// {
//     return from.contains(key)? T(from[key]) : defValue;
// }