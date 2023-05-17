#ifndef JSON_STRING_HPP
#define JSON_STRING_HPP
#include "JSONbase.hpp"
#include <iostream>
#include <string>
#include <vector>

class JSONString : public JSONBase{
    private:
    std::string value; 

    bool is_element_exist(std::vector<std::string>& reversePath);

    public:
    
    JSONString(const std::string& _value); 

    void print() const override; 

    std::string getType() const;

    void set_value(const std::string& el);

    JSONString* clone();

    void search(const std::string& element);

    bool set(std::vector<std::string>& reversePath, std::string str);

    void create(std::vector<std::string>& reversePath, std::string str);

    // bool is_element_exist(std::vector<std::string>& reversePath);

    void delete_element(std::vector<std::string>& reversePath);

    void saves(std::vector<std::string>& reversePath, std::ofstream& os);

    void move(std::vector<std::string> &from, std::vector<std::string> &to);

    void addbByPath(std::vector<std::string>& reversePath, const std::string& key, JSONBase* element);

    JSONBase* get(std::vector<std::string>& reversePath); 
};

#endif