#include "JSONNumber.hpp"
#include <iostream>
#include <string>

JSONNumber::JSONNumber(const double _value) : value(_value){};

void JSONNumber::print() const
{
    std::cout << value;
};

std::string JSONNumber::getType() const
{
    return "number";
};

void JSONNumber::set_value(double number)
{
    this->value = number; 
}
