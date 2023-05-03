#include <iostream>
#include <fstream>
#include <string>
#include "JSONFile.hpp"

void JSONFile::ignoreSpaces(std::istream &is)
{
    do
    {
        is.get();

    } while (is.peek() == ' ' || is.peek() == '\n' || is.peek() == '\t');
}

JSONBase *JSONFile::create(std::istream &is)
{
}

JSONString *JSONFile::create_string(std::istream &is)
{
    JSONString str("");
    std::string temp;
    getline(is, temp, '\"');
    str.set_value(temp);

    return &str;
};

JSONObject *JSONFile::create_object(std::istream &is)
{
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
            JSONString* value = new JSONString("");
            is.get();
            value = create_string(is);

            
        }
    }
};

JSONNumber *JSONFile::create_number(std::istream &is)
{
    JSONNumber num(0);
    double temp;
    is >> temp;
    num.set_value(temp);
    return &num;
};

JSONbool *JSONFile::create_bool(std::istream &is)
{
    JSONbool Boolian(false); // ot lujata sledva vsichko : mitankin
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
    Boolian.set_value(temp);

    return &Boolian;
};

JSONarray *JSONFile::create_array(std::istream &is){

};

int main()
{
    // JSONFile a;

    // std::ifstream is("test.json");

    // a.create(is);

    // return 0;
}

// void ignoreSpaces(std::ifstream &is)
// {
//     do
//     {
//         is.get();

//     } while (is.peek() == ' ' || is.peek() == '\n' || is.peek() == '\t');

//     // while(is.peek() == ' ' || is.peek() == '\n' || is.peek() == '\t')
//     // {
//     //     is.get();
//     // }
// }

// std::string createString(std::ifstream &is)
// {
//     std::string temp;
//     getline(is, temp, '\"');
//     return temp;
// }

// bool is_digit(const char a)
// {
//     return a >= '0' && a <= '9';
// }

// int main()
// {
//     std::ifstream is("test.txt");

//     if (is.peek() == '{')
//     {
//         // create object
//         while (is.peek() != '}')
//         {
//             ignoreSpaces(is);

//             std::string str;

//             getline(is, str, ':');

//             // std::cout << (char)is.peek(); // investigate is.peek() // if ( '\"' ) = string ...
//             if (is.peek() == ' ')
//             {
//                 ignoreSpaces(is);
//             }

//             if (is.peek() == '\"')
//             {
//                 std::string str2;
//                 is.get(); // tuk vikam create na opredeleniq tip
//                 str2 = createString(is);
//                 // getline(is, str2, '\"');
//                 std::cout << str << " " << str2 << '\n';
//             }
//             if (is_digit((char)is.peek()))
//             {
//                 double temp; // tuk vikam create na number
//                 is >> temp;
//                 std::cout << str << " " << temp << '\n';
//             }
//             if(is.peek() == 't' || is.peek() == 'f')
//             {
//                 bool temp;
//                 std::string bolian;
//                 getline(is,bolian);
//                 if(bolian[0] == 't')
//                 {
//                     temp = true;
//                 }
//                 else
//                 {
//                     temp = false;
//                 }
//                 // is >> temp;
//                 std::cout << str << " " << std::boolalpha << temp << '\n';

//             }

//             // std::cout << str << " " << str2 << '\n';
//             // std::cout << (char)is.peek(); zapetaq !!!
//             is.get();
//         }
//     }
//     return 0;
// }
