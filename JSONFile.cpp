#include <iostream>
#include <fstream>
#include <string>
#include "JSONFile.hpp"


JSONBase* JSONFile::create(std::istream& is){
    char t = is.get(); 
    Analise a;
    std::string temp = a.invest(t); 
    //JSONBase* base; 
    if(temp == "object")
    {
        // Factory f;
        JSONObject obj;
        
        // base = f.product(temp);
        // dynamic_cast<JSONObject*>(base); 

        for(int i = 0; is ; i++)    // po skoro dokato != '}' inache shte cikli 
        {
            
        }
        return &obj;

    }
    if(temp == "string")
    {
        JSONString string(""); 
        //dynamic_cast<JSONString*>(base);
        char str[100]; 
        is.getline(str, 100, '\"'); 

        string.set_value(str); 
        return &string; 
    }
    if(temp == "number")
    {
        JSONNumber num(0);
        double a;
        is >> a;
        num.set_value(a);

        return &num; 
    }
    if(temp == "bool")
    {
        JSONbool bull(true); 
        bool b;
        is >> b;
        bull.set_value(b);

        return &bull; 
    }
}

    JSONString* JSONFile::create_string(std::istream& is){

    };

    JSONObject* JSONFile::create_object(std::istream& is){

    };

    JSONNumber* JSONFile::create_number(std::istream& is){

    }; 

    JSONbool* JSONFile::create_bool(std::istream& is){

    };

    JSONarray* JSONFile::create_array(std::istream& is){
        
    };

int main()
{
    JSONFile a;

    std::ifstream is("test.json"); 

    a.create(is);  

    return 0;
}
