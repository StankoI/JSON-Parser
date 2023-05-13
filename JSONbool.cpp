#include <string>
#include "JSONbool.hpp"
#include <iostream>
#include <vector>

JSONbool::JSONbool(const bool _value) : value(_value){};

void JSONbool::print() const
{
    std::cout << std::boolalpha << value << " ";
}

std::string JSONbool::getType() const
{
    return "bool";
}

void JSONbool::set_value(bool b)
{
    this->value = b;
}

JSONbool *JSONbool::clone()
{
    return new JSONbool(*this);
}

void JSONbool::search(const std::string &element) {}

bool JSONbool::set(std::vector<std::string> &reversePath, std::string str)
{
    return true;
}

void JSONbool::create(std::vector<std::string> &reversePath, std::string str) {}

bool JSONbool::is_element_exist(std::vector<std::string> &reversePath)
{
    return true;
}

void JSONbool::delete_element(std::vector<std::string> &reversePath) {}

void JSONbool::saves(std::vector<std::string>& reversePath, std::ofstream& os)
{
    os << value << ' '; 
}