#include <string>
#include "JSONbool.hpp"
#include <iostream>

JSONbool::JSONbool(const bool _value):value(_value){};

void JSONbool::print() const{
    std::cout << std::boolalpha << value; 
};

std::string JSONbool::getType() const
{
    return "bool"; 
};

void JSONbool::set_value(bool b){
    this->value = b; 
}