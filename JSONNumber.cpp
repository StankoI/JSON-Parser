#include "JSONNumber.hpp"
#include <iostream>
#include <string>

JSONNumber::JSONNumber(const double _value) : value(_value){};

void JSONNumber::print() const
{
    std::cout << value << " ";
};

std::string JSONNumber::getType() const
{
    return "number";
};

void JSONNumber::set_value(double number)
{
    this->value = number;
}

JSONNumber *JSONNumber::clone()
{
    return new JSONNumber(*this);
}

void JSONNumber::search(const std::string &element){};

bool JSONNumber::set(std::vector<std::string> &reversePath, std::string str)
{
    return true;
}

void JSONNumber::create(std::vector<std::string> &reversePath, std::string str) {}

bool JSONNumber::is_element_exist(std::vector<std::string> &reversePath)
{
    return true;
}

void JSONNumber::delete_element(std::vector<std::string> &reversePath) {}

void JSONNumber::move(std::vector<std::string> &from, std::vector<std::string> &to){}

void JSONNumber::saves(std::vector<std::string>& reversePath, std::ofstream& os)
{
    os << value << ' '; 
}

JSONBase* JSONNumber::get(std::vector<std::string>& reversePath){
    return this; 
}

void JSONNumber::addbByPath(std::vector<std::string>& reversePath, const std::string& key, JSONBase* element){}