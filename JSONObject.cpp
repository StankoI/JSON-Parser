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

JSONObject* JSONObject::clone(){
    JSONObject* temp = new JSONObject;
    for(std::size_t i = 0; i < key_value.size(); i++)
    {
        std::pair<std::string, JSONBase*> transfer;
        transfer.first = key_value[i].first;
        transfer.second = key_value[i].second->clone();
        temp->add_element(transfer);
    }
    return temp;
}

void JSONObject::search(const std::string& element)
{
    for(std::size_t i = 0; i < this->key_value.size(); i++)
    {
        if(element == key_value[i].first)
        {
            key_value[i].second->print();
        }

        if(key_value[i].second->getType() == "array")
        {
            key_value[i].second->search(element); 
        }

        if(key_value[i].second->getType() == "object")
        {
            key_value[i].second->search(element);
        }
    }
}

JSONObject::~JSONObject()
{
    for(std::size_t i = 0; i < key_value.size(); i++)
    {
        delete key_value[i].second; 
    }
}
