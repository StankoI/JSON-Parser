#include <string>
#include "JSONarray.hpp"
#include "JSONFile.hpp"
#include <iostream>
#include <fstream>
#include <vector>

void JSONarray::copy(const JSONarray &other)
{
    for (std::size_t i = 0; i < other.value.size(); i++)
    {
        this->value.push_back(other.value[i]->clone());
    }
}

void JSONarray::destroy()
{
    for (std::size_t i = 0; i < value.size(); i++)
    {
        delete value[i];
    }
}

JSONarray::JSONarray(){};

JSONarray::JSONarray(const JSONarray &other)
{
    copy(other);
}

JSONarray &JSONarray::operator=(const JSONarray &other)
{
    if (this != &other)
    {
        destroy();
        copy(other);
    }
    return *this;
}

void JSONarray::print() const
{
    std::cout << '[' << '\n';
    for (int i = 0; i < value.size(); i++)
    {
        std::cout << "  ";
        if (value[i] != nullptr)
        {
            value[i]->print();
            std::cout << '\n';
        }
        // value[i]->print();
        // std::cout << '\n';
    }
    std::cout << ']';
};

std::string JSONarray::getType() const
{
    return "array";
};

void JSONarray::add_element(JSONBase *element)
{
    value.push_back(element);
}

JSONarray *JSONarray::clone()
{
    JSONarray *temp = new JSONarray;
    for (std::size_t i = 0; i < value.size(); i++)
    {
        temp->add_element(value[i]->clone());
    }
    return temp;
}

void JSONarray::search(const std::string &element)
{
    for (std::size_t i = 0; i < value.size(); i++)
    {
        if (value[i]->getType() == "object")
        {
            value[i]->search(element);
        }
    }
}

bool JSONarray::set(std::vector<std::string> &reversePath, std::string str)
{
    for (std::size_t i = 0; i < this->value.size(); i++)
    {
        if (this->value[i]->getType() == "object")
        {
            value[i]->set(reversePath, str);
            return true;
        }
    }
    return false;
}

void JSONarray::create(std::vector<std::string> &reversePath, std::string str)
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

        for (std::size_t i = 1; i < reversePath.size(); i++)
        {
            // JSONObject* temp = new JSONObject;
            pairTemp.first = reversePath[i];
            pairTemp.second = creater->clone();
            creater->add_element(pairTemp);
        }

        value.push_back(creater->clone());
        delete creater; // check for problem

        // pairTemp.first = reversePath[reversePath.size()-1];
        // pairTemp.second = creater->clone();

        // this->key_value.push_back(pairTemp);
    }
}

bool JSONarray::is_element_exist(std::vector<std::string> &reversePath)
{
    for (std::size_t i = 0; i < this->value.size(); i++)
    {
        if (this->value[i]->getType() == "object")
        {
            if (value[i] != nullptr)
            {
                value[i]->is_element_exist(reversePath);
                return true;
            }
            // value[i]->is_element_exist(reversePath);
            // return true;
        }
    }
    return false;
}

void JSONarray::delete_element(std::vector<std::string> &reversePath)
{
    for (std::size_t i = 0; i < this->value.size(); i++)
    {
        if (this->value[i]->getType() == "object")
        {
            if (value[i] != nullptr)
            {
                value[i]->delete_element(reversePath);
            }
            // value[i]->delete_element(reversePath);
        }
    }
}

void JSONarray::saves(std::vector<std::string> &reversePath, std::ofstream &os)
{
    if (reversePath.empty())
    {
        os << '[' << " ";
        for (std::size_t i = 0; i < value.size(); i++)
        {
            value[i]->saves(reversePath, os);
        }
        os << ']' << " ";
    }
    else
    {
        os << '[' << " ";
        for (std::size_t i = 0; i < this->value.size(); i++)
        {
            if (this->value[i]->getType() == "object")
            {
                value[i]->saves(reversePath, os);
            }
        }
        os << ']' << " ";
    }
}

void JSONarray::move(std::vector<std::string> &from, std::vector<std::string> &to) {}

JSONBase *JSONarray::get(std::vector<std::string> &reversePath)
{
    return this;
}

void JSONarray::addbByPath(std::vector<std::string> &reversePath, const std::string &key, JSONBase *element)
{
    // for (std::size_t i = 0; i < this->value.size(); i++)
    // {
        if(reversePath.empty())
        {
            std::pair<std::string, JSONBase*> temp;
            temp.first = key;
            temp.second = element->clone();
            JSONObject* obj = new JSONObject;
            obj->add_element(temp);
            value.push_back(obj->clone()); 
            delete obj; 
        }
        else
        {
            for(std::size_t i = 0; i < value.size(); i++)
            {
                if(value[i]->getType() == "object")
                {
                    value[i]->addbByPath(reversePath, key, element);
                }
            }
        }
    // }
}

JSONarray::~JSONarray()
{
    destroy();
}