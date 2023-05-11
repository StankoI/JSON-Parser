#ifndef JSON_NUMBER_HPP
#define JSON_NUMBER_HPP
#include <string>
#include <vector>
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

    JSONNumber* clone();

    void search(const std::string& element);

    bool set(std::vector<std::string>& reversePath, std::string str);

    void create(std::vector<std::string>& reversePath, std::string str);

    bool is_element_exist(std::vector<std::string>& reversePath);

    void delete_element(std::vector<std::string>& reversePath);
};

#endif