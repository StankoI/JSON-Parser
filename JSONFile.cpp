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
    // do
    // {
    //     is.get();

    // } while (is.peek() == ' ' || is.peek() == '\n' || is.peek() == '\t');
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
    // novo dopulnenie v sluchai che s4upi neshto
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
        JSONbool *bull = new JSONbool(false);
        bull = create_bool(is);
        return bull;
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

        std::string str; // key

        getline(is, str, ':');

        if (is.peek() == ' ')
        {
            ignoreSpaces(is);
        }

        if (is.peek() == '\"')
        {
            JSONString *value = new JSONString("");
            // is.get();
            value = create_string(is);

            std::pair<std::string, JSONBase *> temporary;
            temporary.first = str;
            temporary.second = value->clone();
            delete value;

            MAINobj->add_element(temporary);
        }

        if (is_digit((char)is.peek()))
        {
            JSONNumber *num = new JSONNumber(0);
            num = create_number(is);
            std::pair<std::string, JSONBase *> temporary;
            temporary.first = str;
            temporary.second = num->clone();
            delete num;

            MAINobj->add_element(temporary);
        }

        if (is.peek() == 't' || is.peek() == 'f')
        {
            JSONbool *bull = new JSONbool(false);
            bull = create_bool(is);
            std::pair<std::string, JSONBase *> temporary;
            temporary.first = str;
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
            temporary.first = str;
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
            temporary.first = str;
            temporary.second = object->clone();
            delete object;

            MAINobj->add_element(temporary);
        }

        if (is.peek() == 'n')
        {
            JSONNull *null_value = new JSONNull;
            null_value = create_null(is);
            std::pair<std::string, JSONBase *> temporary;
            temporary.first = str;
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
    JSONbool *Boolian = new JSONbool(false); // ot lujata sledva vsichko : mitankin
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
            // is.get();
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
            JSONbool *bull = new JSONbool(false);
            bull = create_bool(is);

            array->add_element(bull->clone());
            delete bull;
        }

        if (is.peek() == '{')
        {
            JSONObject *obj = new JSONObject;
            obj = create_object(is);
            // std::cout << (char)is.peek();
            is.get();

            array->add_element(obj->clone());
            delete obj;
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

            array->add_element(arr->clone()); // tuka e vajno
            delete arr;
        }

        if (is.peek() != ']')
        {
            is.get();
        }
    }
    return array;
};

bool validate(std::ifstream &is)
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

int main()
{
    JSONFile a;

    std::ifstream is("test.txt");

    JSONBase *tr = a.create(is);

    // tr->print();

    // tr->set({"name"} , "\"Petur\"");
    std::vector<std::string> v;
    std::vector<std::string> l;
    std::vector<std::string> empty;
    v.push_back("brand");
    v.push_back("car");

    // tr->delete_element(v);

    // tr->print();

    l.push_back("pets");
    l.push_back("human");

    tr->move(v,l);

    // tr->print();

    // tr->get(v);

    // tr->get(v)->print();
    // JSONNumber aaaa(5);

    // tr->addbByPath(v,"gosho", &aaaa); 
    
    std::ofstream osss("saver.txt");

    tr->saves(empty, osss);
    // JSONarray str;
    // str.add(tr->get(l)->clone());
    // str.print(); 
    // tr->get(l)->print();

    

    // std::cout << tr->set(v , "\"mercedes\"") << '\n';
    // tr->set({"model" , "car"}, "\"benz220\"");

    // tr->set(v, "\"passat\"");

    // tr->print();

    // std::cout << tr->set({"peis","arr"}, "\"gotin\"") << '\n';

    // tr->print();

    // tr->create(v , "\"toyota\""); // the path is reversed if you want to do something like this car:brand:mercedes you write("brand", "car")

    // tr->delete_element(v);

    // tr->set(v , "\"passat 1.9tdi chiposan\"");

    is.close();

    // std::ofstream os("saver.txt");

    // tr->move(v,l);
    // tr->saves(v, os);

    // os.close();

    // std::ifstream in("saver.txt");

    // JSONBase* lerem = a.create(in);

    // lerem->print();

    // tr->print();

    return 0;
}
