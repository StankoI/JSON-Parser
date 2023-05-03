#include <iostream>
#include <string>
#include "factory.hpp"

JSONBase *Factory::product(const std::string word)
{
    if (word == "string")
    {
        return new JSONString("");
    }
    else if (word == "object")
    {
        return new JSONObject;
    }
    else if (word == "number")
    {
        return new JSONNumber(0);
    }
    else if (word == "bool")
    {
        return new JSONbool(true);
    }
    else if (word == "array")
    {
        return new JSONarray;
    }
    else
    {
        return nullptr;
    }
}