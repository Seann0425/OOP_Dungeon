#ifndef OBJECT
#define OBJECT

#include <iostream>

class Object {
public:
    Object();
    Object(std::string&, const std::string);
    const std::string getName() const;
    const std::string getTag() const;
protected:
    std::string name;
    std::string tag;
};

#endif