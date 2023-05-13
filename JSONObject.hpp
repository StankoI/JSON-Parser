#ifndef JSON_OBJECT_HPP
#define JSON_OBJECT_HPP
#include <string>
#include <vector>
#include <fstream>
#include "JSONbase.hpp"

class JSONObject : public JSONBase{

    private:

    std::vector<std::pair<std::string, JSONBase*>> key_value;

    void copy(const JSONObject& other);

    void destroy();

    bool is_element_exist(std::vector<std::string>& reversePath); 

    public:

    JSONObject(); 

    JSONObject(const JSONObject& other);

    JSONObject& operator=(const JSONObject& other);
    
    void print() const;

    std::string getType() const;

    void set_key(const std::string& el, size_t index); 

    void add_element(std::pair<std::string, JSONBase*>); 

    JSONObject* clone();

    void search(const std::string& element);

    bool set(std::vector<std::string>& reversePath, std::string str);

    void create(std::vector<std::string>& reversePath, std::string str);

    void delete_element(std::vector<std::string>& reversePath); 

    void saves(std::vector<std::string>& reversePath, std::ofstream& os); 

    ~JSONObject();

};

#endif