#include <string>
#include "JSONarray.hpp"
#include <iostream>
#include <vector>

JSONarray::JSONarray(){};

void JSONarray::print() const
{
    for(int i = 0; i < value.size(); i++)
    {
        std::cout << value[i]; 
    }
};

std::string JSONarray::getType() const
{
    return "array";
};