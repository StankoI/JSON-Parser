#ifndef JSON_NULL_HPP
#define JSON_NULL_HPP
#include <string>
#include <vector>
#include <fstream>
#include "JSONbase.hpp"

class JSONNull : public JSONBase
{
    private:

    bool is_element_exist(std::vector<std::string>& reversePath);

    public:

    void print() const; 

    std::string getType() const; 

    JSONBase* clone();

    void search(const std::string& element); 

    bool set(std::vector<std::string>& reversePath, std::string str);

    void create(std::vector<std::string>& reversePath, std::string str);

    void delete_element(std::vector<std::string>& reversePath);

    void saves(std::vector<std::string>& reversePath, std::ofstream& os); 

    void move(std::vector<std::string> &from, std::vector<std::string> &to);

    JSONBase* get(std::vector<std::string>& reversePath);

    void addbByPath(std::vector<std::string>& reversePath, const std::string& key, JSONBase* element);

    ~JSONNull();

};


#endif