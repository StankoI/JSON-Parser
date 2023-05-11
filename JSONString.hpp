#ifndef JSON_STRING_HPP
#define JSON_STRING_HPP
#include "JSONbase.hpp"
#include <iostream>
#include <string>
#include <vector>

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

    bool set(std::vector<std::string>& reversePath, std::string str);

    void create(std::vector<std::string>& reversePath, std::string str);

    bool is_element_exist(std::vector<std::string>& reversePath);

    void delete_element(std::vector<std::string>& reversePath);
};

#endif