#ifndef JSON_OBJECT_HPP
#define JSON_OBJECT_HPP
#include <string>
#include <vector>
#include "JSONbase.hpp"

class JSONObject : public JSONBase{

    private:

    std::vector<std::pair<std::string, JSONBase*>> key_value;

    public:

    JSONObject(); 
    
    void print() const;

    std::string getType() const;

    void set_key(const std::string& el, size_t index); 

    void add_element(std::pair<std::string, JSONBase*>); 

    JSONObject* clone();

    void search(const std::string& element);

    ~JSONObject();

};

#endif