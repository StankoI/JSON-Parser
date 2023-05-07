#ifndef JSON_STRING_HPP
#define JSON_STRING_HPP
#include "JSONbase.hpp"
#include <iostream>
#include <string>

class JSONString : public JSONBase{
    private:
    std::string value; 

    public:
    
    JSONString(const std::string _value); 

    void print() const; 

    std::string getType() const;

    void set_value(const std::string el);

    JSONString* clone();

    void search(const std::string& element);

};

#endif