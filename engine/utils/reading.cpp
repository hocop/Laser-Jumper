#include "reading.hpp"


std::string rd::join(const std::string& path, const std::string& file)
{
    if (path.back() == '/')
        return path + file;
    else
        return path + "/" + file;
}

std::string rd::join(const std::string& path, const std::string& folder, const std::string& file)
{
    std::string s = rd::join(path, folder);
    return rd::join(s, file);
}


// template<typename T>
// T rd::get(const json& from, const std::string& key, const T& defValue)
// {
//     return from.contains(key)? T(from[key]) : defValue;
// }

json rd::read_json(const std::string& path)
{
    std::ifstream f(path);
    return json::parse(f);
}