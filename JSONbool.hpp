#ifndef JSON_BOOL_HPP
#define JSON_BOOL_HPP
#include <string>
#include <vector>
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

    JSONbool* clone();

    void search(const std::string& element);

    bool set(std::vector<std::string>& reversePath, std::string str);

    void create(std::vector<std::string>& reversePath, std::string str);

    bool is_element_exist(std::vector<std::string>& reversePath);

    void delete_element(std::vector<std::string>& reversePath);
};

#endif