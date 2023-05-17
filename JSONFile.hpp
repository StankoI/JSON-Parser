#ifndef JSONFILE_HPP
#define JSONFILE_HPP
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include "JSONarray.hpp"
#include "JSONNumber.hpp"
#include "JSONString.hpp"
#include "JSONObject.hpp"
#include "JSONbool.hpp"
#include "JSONNull.hpp"

class JSONFile{
    
    public:

    JSONBase* create(std::istream& is); 

    JSONString* create_string(std::istream& is);

    JSONObject* create_object(std::istream& is);

    JSONNumber* create_number(std::istream& is); 

    JSONbool* create_bool(std::istream& is);

    JSONarray* create_array(std::istream& is);

    JSONNull* create_null(std::istream& is);

    void ignoreSpaces(std::istream& is);

    bool is_digit(const char el);

    bool validate(std::ifstream& is);

};



#endif