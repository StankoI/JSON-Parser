#include <iostream>
#include <string>
#include "JSONObject.hpp"

JSONObject::JSONObject(){
     
};

void JSONObject::print() const{

    for(size_t i = 0; i < this->key_value.size(); i++)
    {
        std::cout << key_value[i].first << " "; 
        key_value[i].second->print();
        std::cout << '\n';
    }
};

std::string JSONObject::getType() const{
    return "object"; 
};

void JSONObject::set_key(const std::string& el, size_t index){
    key_value[index].first = el; 
} 

void JSONObject::add_element(std::pair<std::string, JSONBase*> el)
{
    key_value.push_back(el); 
}

