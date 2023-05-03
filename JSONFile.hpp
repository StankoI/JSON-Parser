#ifndef JSONFILE_HPP
#define JSONFILE_HPP
#include <string>
#include <vector>
#include <iostream>
#include "JSONarray.hpp"
#include "JSONNumber.hpp"
#include "JSONString.hpp"
#include "JSONObject.hpp"
#include "JSONbool.hpp"
#include "analise.hpp"
#include "factory.hpp"

class JSONFile{
    
    public:

    JSONBase* create(std::istream& is); 

};



#endif