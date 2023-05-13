#include <iostream>
#include <string>
#include <vector>

#include "JSONString.hpp"


JSONString::JSONString(const std::string& _value) : value(_value){};

void JSONString::print() const
{
    std::cout << value << " ";
}

std::string JSONString::getType() const
{
    return "string";
}

void JSONString::set_value(const std::string& el)
{
    this->value = el;
}

void JSONString::search(const std::string &element){};

JSONString *JSONString::clone()
{
    return new JSONString(*this);
}

bool JSONString::set(std::vector<std::string> &reversePath, std::string str)
{
    return true;
};

void JSONString::create(std::vector<std::string> &reversePath, std::string str)
{}

bool JSONString::is_element_exist(std::vector<std::string>& reversePath)
{
    return true;
}

void JSONString::delete_element(std::vector<std::string>& reversePath){}

void JSONString::saves(std::vector<std::string>& reversePath, std::ofstream& os)
{
    os << '\"' << value << '\"' << ' '; 
}