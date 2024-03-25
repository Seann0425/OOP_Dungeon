#include "../Header_Files/Object.h"

Object::Object() : name("Unknown"), tag("Unknown") {
}
Object::Object(string name, string tag) : name(name), tag(tag) {
}
const string Object::getName() const {
    return this->name;
}
const string Object::getTag() const {
    return this->tag;
}