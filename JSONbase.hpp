#ifndef JSON_BASE_HPP
#define JSON_BASE_HPP

class JSONBase
{
    public:
    
    virtual void print() const = 0; 

    virtual std::string getType() const = 0; 

    virtual JSONBase* clone() = 0;

    virtual ~JSONBase() = default;

    virtual void search(const std::string& element) = 0; 

};

#endif