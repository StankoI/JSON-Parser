#ifndef JSON_BASE_HPP
#define JSON_BASE_HPP
#include <vector>
#include <string>
#include <fstream>
#include <iostream>

class JSONBase
{
    public:
    
    virtual void print() const = 0; 

    virtual std::string getType() const = 0; 

    virtual JSONBase* clone() = 0;

    virtual ~JSONBase() = default;

    virtual void search(const std::string& element) = 0; 

    virtual bool set(std::vector<std::string>& reversePath, std::string str) = 0;

    virtual void create(std::vector<std::string>& reversePath, std::string str) = 0;

    virtual bool is_element_exist(std::vector<std::string>& reversePath) = 0;

    virtual void delete_element(std::vector<std::string>& reversePath) = 0;

    virtual void saves(std::vector<std::string>& reversePath, std::ofstream& os) = 0;

    virtual void move(std::vector<std::string> &from, std::vector<std::string> &to) = 0;

    virtual JSONBase* get(std::vector<std::string>& reversePath) = 0;

    virtual void addbByPath(std::vector<std::string>& reversePath, const std::string& key, JSONBase* element) = 0;
};

#endif