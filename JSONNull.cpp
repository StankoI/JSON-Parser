#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "JSONNull.hpp"

void JSONNull::print() const
{
    std::cout << "null";
}

std::string JSONNull::getType() const
{
    return "null";
}

JSONBase *JSONNull::clone()
{
    return new JSONNull(*this);
}

void JSONNull::search(const std::string &element) {}

bool JSONNull::set(std::vector<std::string> &reversePath, std::string str)
{
    return true;
}

void JSONNull::create(std::vector<std::string> &reversePath, std::string str) {}

void JSONNull::delete_element(std::vector<std::string> &reversePath) {}

void JSONNull::saves(std::vector<std::string> &reversePath, std::ofstream &os)
{
    os << "null" << ' ';
}

bool JSONNull::is_element_exist(std::vector<std::string> &reversePath)
{
    return true;
}

void JSONNull::move(std::vector<std::string> &from, std::vector<std::string> &to){}

JSONBase* JSONNull::get(std::vector<std::string>& reversePath){
    return this;
}

void JSONNull::addbByPath(std::vector<std::string>& reversePath, const std::string& key, JSONBase* element){}

JSONNull::~JSONNull() {}