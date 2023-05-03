#ifndef JSON_NUMBER_HPP
#define JSON_NUMBER_HPP
#include <string>
#include "JSONbase.hpp"


class JSONNumber : public JSONBase
{
    private:
    double value; 

    public:

    JSONNumber(const double _value); 

    void print() const; 

    std::string getType() const;

    void set_value(double number); 
};

#endif