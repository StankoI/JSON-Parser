#include <string>
#include "JSONarray.hpp"
#include <iostream>
#include <fstream>
#include <vector>

JSONarray::JSONarray(){};

void JSONarray::print() const
{
    for(int i = 0; i < value.size(); i++)
    {
        value[i]->print(); 
        std::cout << '\n';
    }
};

std::string JSONarray::getType() const
{
    return "array";
};

void JSONarray::add(JSONBase* element)
{
    value.push_back(element); 
}

JSONarray* JSONarray::clone()
{
    JSONarray* temp = new JSONarray;
    for(std::size_t i = 0; i < value.size(); i++)
    {
        temp->add(value[i]->clone());
    }
    return temp; 
}

void JSONarray::search(const std::string& element)
{
    for(std::size_t i = 0; i < value.size(); i++)
    {
        if(value[i]->getType() == "object")
        {
            value[i]->search(element); 
        }
    }
}

JSONarray::~JSONarray()
{
    for(std::size_t i = 0; i < value.size(); i++)
    {
        delete value[i];
    }
}