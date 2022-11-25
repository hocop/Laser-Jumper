#pragma once

#include <iostream>


class Action
{
    std::string     m_name = "NONE";
    std::string     m_type = "NONE";

public:
    Action() {};
    Action(const std::string& name, const std::string& type)
    :   m_name(name), m_type(type)
    {};

    const std::string& name() const {return m_name;};
    const std::string& type() const {return m_type;};
    std::string toString() const {return m_name + " " + m_type;};
};