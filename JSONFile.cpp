#include <iostream>
#include <fstream>
#include <string>
#include "JSONFile.hpp"

bool JSONFile::is_digit(const char el)
{
    return el >= '0' && el <= '9' || el == '-';
}

void JSONFile::ignoreSpaces(std::istream &is)
{
    while (is.peek() == ' ' || is.peek() == '\n' || is.peek() == '\t')
    {
        is.get();
    }
}

JSONBase *JSONFile::create(std::istream &is)
{
    if (is.peek() == '{')
    {
        JSONObject *org = new JSONObject;
        org = create_object(is);
        return org;
    }
    if (is.peek() == '[')
    {
        JSONarray *arr = new JSONarray;
        arr = create_array(is);
        return arr;
    }
    
    if (is.peek() == '\"')
    {
        JSONString *str = new JSONString("");
        str = create_string(is);
        return str;
    }

    if (is_digit(is.peek()))
    {
        JSONNumber *num = new JSONNumber(0);
        num = create_number(is);
        return num;
    }

    if (is.peek() == 't' || is.peek() == 'f')
    {
        JSONbool *boolean = new JSONbool(false);
        boolean = create_bool(is);
        return boolean;
    }

    return nullptr;
}

JSONString *JSONFile::create_string(std::istream &is)
{
    JSONString *str = new JSONString("");
    std::string temp;
    is.get();
    getline(is, temp, '\"');
    str->set_value(temp);

    return str;
};

JSONObject *JSONFile::create_object(std::istream &is)
{
    JSONObject *MAINobj = new JSONObject;
    is.get();
    while (is.peek() != '}')
    {
        ignoreSpaces(is);

        std::string str_key; 

        getline(is, str_key, ':');

        if (is.peek() == ' ')
        {
            ignoreSpaces(is);
        }

        if (is.peek() == '\"')
        {
            JSONString *value = new JSONString("");
            
            value = create_string(is);

            std::pair<std::string, JSONBase *> temporary;
            temporary.first = str_key;
            temporary.second = value->clone();
            delete value;

            MAINobj->add_element(temporary);
        }

        if (is_digit((char)is.peek()))
        {
            JSONNumber *num = new JSONNumber(0);
            num = create_number(is);
            std::pair<std::string, JSONBase *> temporary;
            temporary.first = str_key;
            temporary.second = num->clone();
            delete num;

            MAINobj->add_element(temporary);
        }

        if (is.peek() == 't' || is.peek() == 'f')
        {
            JSONbool *bull = new JSONbool(false);
            bull = create_bool(is);
            std::pair<std::string, JSONBase *> temporary;
            temporary.first = str_key;
            temporary.second = bull->clone();
            delete bull;

            MAINobj->add_element(temporary);
        }
        if (is.peek() == '[')
        {
            JSONarray *arr = new JSONarray;
            arr = create_array(is);
            is.get();
            std::pair<std::string, JSONBase *> temporary;
            temporary.first = str_key;
            temporary.second = arr->clone();
            delete arr;

            MAINobj->add_element(temporary);
        }

        if (is.peek() == '{')
        {
            JSONObject *object = new JSONObject;
            object = create_object(is);
            is.get();
            std::pair<std::string, JSONBase *> temporary;
            temporary.first = str_key;
            temporary.second = object->clone();
            delete object;

            MAINobj->add_element(temporary);
        }

        if (is.peek() == 'n')
        {
            JSONNull *null_value = new JSONNull;
            null_value = create_null(is);
            std::pair<std::string, JSONBase *> temporary;
            temporary.first = str_key;
            temporary.second = null_value->clone();
            delete null_value;

            MAINobj->add_element(temporary);
        }

        if (is.peek() != '}')
        {
            is.get();
        }
    }
    return MAINobj;
};

JSONNumber *JSONFile::create_number(std::istream &is)
{
    JSONNumber *num = new JSONNumber(0);
    double temp;
    is >> temp;
    num->set_value(temp);
    return num;
};

JSONNull *JSONFile::create_null(std::istream &is)
{
    JSONNull *null_value = new JSONNull;
    std::string reader;
    getline(is, reader);

    return null_value;
}

JSONbool *JSONFile::create_bool(std::istream &is)
{
    JSONbool *Boolian = new JSONbool(false);
    bool temp;
    std::string bolian;
    getline(is, bolian);
    if (bolian[0] == 't')
    {
        temp = true;
    }
    else
    {
        temp = false;
    }
    Boolian->set_value(temp);

    return Boolian;
};

JSONarray *JSONFile::create_array(std::istream &is)
{
    JSONarray *array = new JSONarray;
    is.get();
    while (is.peek() != ']')
    {
        if (is.peek() == ' ')
        {
            ignoreSpaces(is);
        }

        if (is.peek() == '\"')
        {
            JSONString *value = new JSONString("");
            
            value = create_string(is);

            array->add_element(value->clone());
            delete value;
        }

        if (is_digit(is.peek()))
        {
            JSONNumber *num = new JSONNumber(0);
            num = create_number(is);

            array->add_element(num->clone());
            delete num;
        }

        if (is.peek() == 't' || is.peek() == 'f')
        {
            JSONbool *booleanTemp = new JSONbool(false);
            booleanTemp = create_bool(is);

            array->add_element(booleanTemp->clone());
            delete booleanTemp;
        }

        if (is.peek() == '{')
        {
            JSONObject *objectTemp = new JSONObject;
            objectTemp = create_object(is);
            
            is.get();

            array->add_element(objectTemp->clone());
            delete objectTemp;
        }

        if (is.peek() == 'n')
        {
            JSONNull *null_value = new JSONNull;
            null_value = create_null(is);

            array->add_element(null_value->clone());
            delete null_value;
        }

        if (is.peek() == '[')
        {
            JSONarray *arr = new JSONarray;
            arr = create_array(is);
            is.get();

            array->add_element(arr->clone()); 
            delete arr;
        }

        if (is.peek() != ']')
        {
            is.get();
        }
    }
    return array;
};

bool JSONFile::validate(std::ifstream &is)
{
    std::size_t quotationMarksCounter = 0;
    std::vector<char> counter;
    while (is)
    {
        if (is.peek() == '\"')
        {
            quotationMarksCounter++;
        }
        if (is.peek() == '{')
        {
            counter.push_back('{');
        }
        if (is.peek() == '[')
        {
            counter.push_back('[');
        }
        if (is.peek() == '}')
        {
            if (counter[counter.size() - 1] == '{')
            {
                counter.pop_back();
            }
            else
            {
                counter.push_back('}');
            }
        }
        if (is.peek() == ']')
        {
            if (counter[counter.size() - 1] == '[')
            {
                counter.pop_back();
            }
            else
            {
                counter.push_back(']');
            }
        }
        is.get();
    }
    if (!counter.empty())
    {
        std::cout << "there is a problem with the braces";
        return false;
    }
    if (quotationMarksCounter % 2 != 0)
    {
        std::cout << "there is a problem with quotation marks";
        return false;
    }
    return true;
}
