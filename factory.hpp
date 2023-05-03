#ifndef FACTORY_HPP
#define FACTORY_HPP
#include <string>
#include <iostream>
#include "JSONarray.hpp"
#include "JSONNumber.hpp"
#include "JSONString.hpp"
#include "JSONObject.hpp"
#include "JSONbool.hpp"

class Factory{
    public: 

    JSONBase* product(const std::string word); 

};

#endif