#include <iostream>
#include <string>
#include "JSONString.hpp"

JSONString::JSONString(const std::string _value) : value(_value) {}

void JSONString::print() const
{
    std::cout << value;
}

std::string JSONString::getType() const
{
    return "string";
}

void JSONString::set_value(const std::string el)
{
    this->value = el; 
}