#ifndef JSON_BOOL_HPP
#define JSON_BOOL_HPP
#include <string>
#include "JSONbase.hpp"

class JSONbool : public JSONBase
{
private:
    bool value;

public:
    JSONbool(const bool _value);

    void print() const;

    std::string getType() const;

    void set_value(bool b);
};

#endif