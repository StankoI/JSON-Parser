#ifndef JSON_ARRAY_HPP
#define JSON_ARRAY_HPP
#include <string>
#include <vector>
#include "JSONbase.hpp"

class JSONarray : public JSONBase
{
    private:
    std::vector<JSONBase*> value; 

    void copy(const JSONarray& other);

    void destroy();

    bool is_element_exist(std::vector<std::string>& reversePath);

    public:

    JSONarray();

    JSONarray(const JSONarray& other);

    JSONarray& operator=(const JSONarray& other);

    void print() const;

    std::string getType() const;

    void add_element(JSONBase* element); 

    JSONarray* clone();

    void search(const std::string& element);

    bool set(std::vector<std::string>& reversePath, std::string str); 

    void create(std::vector<std::string>& reversePath, std::string str);

    // bool is_element_exist(std::vector<std::string>& reversePath);

    void delete_element(std::vector<std::string>& reversePath);

    void saves(std::vector<std::string>& reversePath, std::ofstream& os);

    void move(std::vector<std::string> &from, std::vector<std::string> &to);

    JSONBase* get(std::vector<std::string>& reversePath);

    void addbByPath(std::vector<std::string>& reversePath, const std::string& key, JSONBase* element);
    
    ~JSONarray();

};

#endif