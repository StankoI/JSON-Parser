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
            if (key_value[i].second != nullptr)
            {
                return key_value[i].second->is_element_exist(reversePath);
            }
        }
    }

    if (reversePath.empty())
    {
        return true;
    }
    else
    {
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
    std::cout << "{" << '\n';
    for (size_t i = 0; i < this->key_value.size(); i++)
    {
        std::cout << "  ";
        std::cout << key_value[i].first << " ";
        if (key_value[i].second != nullptr)
        {
            key_value[i].second->print();
            std::cout << '\n';
        }
    }
    std::cout << "}" << '\n';
};

std::string JSONObject::getType() const
{
    return "object";
};

// void JSONObject::set_key(const std::string &el, size_t index)
// {
//     key_value[index].first = el;
// }

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
            std::cout << '\n';
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

                if (key_value[i].second == nullptr) // tuk ne sum siguren
                {
                    this->key_value[i].second = strConvert->clone();
                    delete strConvert;
                    return true;
                }

                std::string temp = this->key_value[i].second->getType();

                if (temp == "array")
                {
                    if (temp != strConvert->getType())
                    {
                        std::cout << "types of previous and new value does not maches!!!" << '\n';
                        return false;
                    }
                    delete key_value[i].second;
                    this->key_value[i].second = strConvert->clone();
                    delete strConvert;
                    return true;
                }
                if (temp == "null")
                {
                    delete key_value[i].second;
                    this->key_value[i].second = strConvert->clone();
                    delete strConvert;
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
                    this->key_value[i].second = strConvert->clone();
                    delete strConvert;
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
                    this->key_value[i].second = strConvert->clone();
                    delete strConvert;
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
                    this->key_value[i].second = strConvert->clone();
                    delete strConvert;
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
                    this->key_value[i].second = strConvert->clone();
                    delete strConvert;
                    return true;
                }
            }
            if (key_value[i].second != nullptr)
            {
                key_value[i].second->set(reversePath, str);
            }
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

        JSONBase *strConvert = a.create(is);
    
        std::string lastKey = *(reversePath.end() - 1);

        JSONObject *creater = new JSONObject;
        std::pair<std::string, JSONBase *> pairTemp;
        pairTemp.first = reversePath[0];
        pairTemp.second = strConvert->clone(); // JOSNBase*

        

        reversePath.erase(reversePath.begin());

        if (!reversePath.empty())
        {
            creater->add_element(pairTemp);
        }

        if (!reversePath.empty())
        {
            for (std::size_t i = 0; i < reversePath.size() - 1; i++)
            {
                pairTemp.first = reversePath[i];
                pairTemp.second = creater->clone();
                JSONObject *something = new JSONObject;
                something->add_element(pairTemp);
                creater = something->clone();
                delete something;
            }
            pairTemp.second = creater->clone();
        }

        pairTemp.first = lastKey;

        this->key_value.push_back(pairTemp);
        delete creater;
    }
    // std::cout << reversePath.empty();
}

void JSONObject::delete_element(std::vector<std::string> &reversePath)
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
                    key_value.erase(key_value.begin() + i);
                    // delete key_value[i].second;
                    // JSONString* empty = new JSONString(" ");
                    //  JSONBase* empty = new JSONString("");
                    //  key_value[i].second = empty->clone();
                    // delete empty;
                    // key_value[i].second = nullptr;
                    // for (std::size_t j = i; j < this->key_value.size(); j++)
                    // {
                    //     key_value[j] = key_value[j + 1];
                    // }
                    // key_value.pop_back();
                    return;
                }
                if (key_value[i].second != nullptr)
                {
                    key_value[i].second->delete_element(reversePath);
                }
                // key_value[i].second->delete_element(reversePath);
            }
        }
    }
}

JSONBase *JSONObject::get(std::vector<std::string> &reversePath)
{
    // JSONBase* temp;
    for (std::size_t i = 0; i < key_value.size(); i++)
    {
        if (reversePath[reversePath.size() - 1] == key_value[i].first)
        {
            reversePath.pop_back();

            if (reversePath.empty())
            {
                // std::cout << "empty\n";
                return key_value[i].second->clone();
            }
            if (key_value[i].second != nullptr)
            {
                // std::cout << "recursive\n";
                return key_value[i].second->get(reversePath);
            }
        }
    }
    // std::cout << "nullptr\n";
    return nullptr;
}

void JSONObject::addbByPath(std::vector<std::string> &reversePath, const std::string &key, JSONBase *element)
{
    if (reversePath.empty())
    {
        std::pair<std::string, JSONBase *> temp;
        temp.first = key;
        temp.second = element->clone();
        key_value.push_back(temp);
    }
    else
    {
        for (std::size_t i = 0; i < this->key_value.size(); i++)
        {
            if (reversePath[reversePath.size() - 1] == key_value[i].first)
            {
                reversePath.pop_back();
                // if (reversePath.empty())
                // {
                //     // std::pair<std::string, JSONBase *> temp;
                //     // temp.first = key;
                //     // temp.second = element->clone();
                //     // key_value.push_back(temp);
                // }
                if (key_value[i].second != nullptr)
                {
                    key_value[i].second->addbByPath(reversePath, key, element);
                }
            }
        }
    }
}

void JSONObject::move(std::vector<std::string> &from, std::vector<std::string> &to)
{
    std::string key = from[0];
    std::vector<std::string> fromCopy;
    fromCopy = from;
    JSONBase *fr = get(fromCopy);
    delete_element(from);
    addbByPath(to, key, fr->clone());
    // delete fr;
}

void JSONObject::saves(std::vector<std::string> &reversePath, std::ofstream &os)
{
    if (!reversePath.empty())
    {
        for (std::size_t i = 0; i < this->key_value.size(); i++)
        {
            if (reversePath[reversePath.size() - 1] == key_value[i].first)
            {
                reversePath.pop_back();
                os << '{' << " " << key_value[i].first << ':';

                key_value[i].second->saves(reversePath, os);

                os << '}' << " ";
            }
        }
    }
    else
    {
        os << '{' << " ";
        for (std::size_t i = 0; i < this->key_value.size(); i++)
        {
            os << key_value[i].first << ':';

            key_value[i].second->saves(reversePath, os);
        }
        os << '}' << " ";
    }
}

JSONObject::~JSONObject()
{
    destroy();
}
