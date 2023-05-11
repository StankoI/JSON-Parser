#include <iostream>
#include <string>
#include <fstream>
#include "JSONObject.hpp"
#include "JSONFile.hpp"

void JSONObject::copy(const JSONObject &other)
{
    for (std::size_t i = 0; i < other.key_value.size(); i++)
    {
        std::pair<std::string, JSONBase *> temp;
        temp.first = other.key_value[i].first;
        temp.second = other.key_value[i].second->clone();

        this->add_element(temp);
    }
}

void JSONObject::destroy()
{
    for (std::size_t i = 0; i < this->key_value.size(); i++)
    {
        delete key_value[i].second;
    }
}

bool JSONObject::is_element_exist(std::vector<std::string> &reversePath)
{
    for (std::size_t i = 0; i < this->key_value.size(); i++)
    {
        if (reversePath[reversePath.size() - 1] == key_value[i].first)
        {
            reversePath.pop_back();

            if (reversePath.empty())
            {
                return true;
            }
            key_value[i].second->is_element_exist(reversePath);
        }
    }

    if (reversePath.empty())
    {
        return true;
    }
    else
    {
        // std::cout << "path not found " << '\n';
        return false;
    }
}

JSONObject::JSONObject() {}

JSONObject::JSONObject(const JSONObject &other)
{
    copy(other);
}

JSONObject &JSONObject::operator=(const JSONObject &other)
{
    if (this != &other)
    {
        destroy();
        copy(other);
    }
    return *this;
}

void JSONObject::print() const
{

    for (size_t i = 0; i < this->key_value.size(); i++)
    {
        std::cout << key_value[i].first << " ";
        key_value[i].second->print();
        std::cout << '\n';
    }
};

std::string JSONObject::getType() const
{
    return "object";
};

void JSONObject::set_key(const std::string &el, size_t index)
{
    key_value[index].first = el;
}

void JSONObject::add_element(std::pair<std::string, JSONBase *> el)
{
    key_value.push_back(el);
}

JSONObject *JSONObject::clone()
{
    JSONObject *temp = new JSONObject;
    for (std::size_t i = 0; i < key_value.size(); i++)
    {
        std::pair<std::string, JSONBase *> transfer;
        transfer.first = key_value[i].first;
        transfer.second = key_value[i].second->clone();
        temp->add_element(transfer);
    }
    return temp;
}

void JSONObject::search(const std::string &element)
{
    for (std::size_t i = 0; i < this->key_value.size(); i++)
    {
        if (element == key_value[i].first)
        {
            key_value[i].second->print();
        }

        if (key_value[i].second->getType() == "array")
        {
            key_value[i].second->search(element);
        }

        if (key_value[i].second->getType() == "object")
        {
            key_value[i].second->search(element);
        }
    }
}

bool JSONObject::set(std::vector<std::string> &reversePath, std::string str)
{
    for (std::size_t i = 0; i < this->key_value.size(); i++)
    {
        if (reversePath[reversePath.size() - 1] == key_value[i].first)
        {
            reversePath.pop_back();

            if (reversePath.empty())
            {
                std::ofstream os("convert.txt");
                os << str;

                os.close();

                std::ifstream is("convert.txt");

                JSONFile a;
                JSONBase *strConvert = a.create(is);

                std::string temp = this->key_value[i].second->getType();
                if (temp == "array")
                {
                    if (temp != strConvert->getType())
                    {
                        std::cout << "types of previous and new value does not maches!!!" << '\n';
                        return false;
                    }
                    delete key_value[i].second;
                    this->key_value[i].second = strConvert;
                    return true;
                }
                if (temp == "object")
                {
                    if (temp != strConvert->getType())
                    {
                        std::cout << "types of previous and new value does not maches!!!" << '\n';
                        return false;
                    }
                    delete key_value[i].second;
                    this->key_value[i].second = strConvert;
                    return true;
                }
                if (temp == "string")
                {
                    if (temp != strConvert->getType())
                    {
                        std::cout << "types of previous and new value does not maches!!!" << '\n';
                        return false;
                    }
                    delete key_value[i].second;
                    this->key_value[i].second = strConvert;
                    return true;
                }
                if (temp == "number")
                {
                    if (temp != strConvert->getType())
                    {
                        std::cout << "types of previous and new value does not maches!!!" << '\n';
                        return false;
                    }
                    delete key_value[i].second;
                    this->key_value[i].second = strConvert;
                    return true;
                }
                if (temp == "bool")
                {
                    if (temp != strConvert->getType())
                    {
                        std::cout << "types of previous and new value does not maches!!!" << '\n';
                        return false;
                    }
                    delete key_value[i].second;
                    this->key_value[i].second = strConvert;
                    return true;
                }
                // return true;
            }

            key_value[i].second->set(reversePath, str);

            // key_value[i].second->set(reversePath, str);
        }
    }

    if (reversePath.empty())
    {
        return true;
    }
    else
    {
        std::cout << "path not found " << '\n';
        return false;
    }
}

void JSONObject::create(std::vector<std::string> &reversePath, std::string str)
{
    std::vector<std::string> t;
    t = reversePath;
    if (is_element_exist(t))
    {
        std::cout << "this path already exist" << '\n';
    }
    else
    {
        JSONFile a;

        std::ofstream os("convert.txt");
        os << str;

        os.close();

        std::ifstream is("convert.txt");

        // JSONFile a;
        JSONBase *strConvert = a.create(is);

        JSONObject *creater = new JSONObject;
        std::pair<std::string, JSONBase *> pairTemp;
        pairTemp.first = reversePath[0];
        pairTemp.second = strConvert->clone();

        creater->add_element(pairTemp);

        for (std::size_t i = 1; i < reversePath.size() - 1; i++)
        {
            // JSONObject* temp = new JSONObject;
            pairTemp.first = reversePath[i];
            pairTemp.second = creater->clone();
            creater->add_element(pairTemp);
        }
        pairTemp.first = reversePath[reversePath.size() - 1];
        pairTemp.second = creater->clone();
        delete creater; // check for problems
        this->key_value.push_back(pairTemp);
    }
    // std::cout << reversePath.empty();
}

void JSONObject::delete_element(std::vector<std::string>& reversePath)
{
    std::vector<std::string> t = reversePath;
    if (!is_element_exist(t))
    {
        std::cout << "uncorect path" << '\n';
    }
    else
    {
        for (std::size_t i = 0; i < this->key_value.size(); i++)
        {
            if (reversePath[reversePath.size() - 1] == key_value[i].first)
            {
                reversePath.pop_back();

                if (reversePath.empty())
                {
                    delete key_value[i].second;
                    JSONString* empty = new JSONString(" ");
                    // JSONBase* empty = new JSONString(""); 
                    key_value[i].second = empty->clone();  
                    delete empty;
                    // key_value[i].second = nullptr;
                }
                key_value[i].second->delete_element(reversePath);
            }
            
        }
    }
}

JSONObject::~JSONObject()
{
    for (std::size_t i = 0; i < key_value.size(); i++)
    {
        delete key_value[i].second;
    }
}
