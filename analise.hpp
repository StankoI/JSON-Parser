#ifndef ANALISE_HPP
#define ANALISE_HPP
#include <string>
#include "JSONFile.hpp"

class Analise{

    public:

    std::string invest(const char el)
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
    }
};


#endif