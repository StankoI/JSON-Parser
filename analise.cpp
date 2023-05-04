#include <iostream>
#include <string>
#include "analise.hpp"


std::string Analise::invest(const char el)
    {
        if(el == '{')
        {
            return "object"; 
        }
        if(el == '\"')
        {
            return "string";
        }
        if(el >= '0' && el <= '9' || el == '-' || el == '+')
        {
            return "number"; 
        }
        if(el == 't' || el == 'f')
        {
            return "bool"; 
        }
        if(el == '[')
        {
            return "array"; 
        }
        return "";
    }