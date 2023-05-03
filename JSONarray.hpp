#ifndef JSON_ARRAY_HPP
#define JSON_ARRAY_HPP
#include <string>
#include <vector>
#include "JSONbase.hpp"

class JSONarray : public JSONBase
{
    private:
    std::vector<JSONBase*> value; 

    public:

    JSONarray();

    void print() const;

    std::string getType() const;

};

#endif