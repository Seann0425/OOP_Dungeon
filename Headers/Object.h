#ifndef OBJECT
#define OBJECT

#include <iostream>
using namespace std;

class Object {
public:
    Object();
    Object(string, string);
    const string getName() const;
    const string getTag() const;
private:
    string name;
    string tag;
};

#endif