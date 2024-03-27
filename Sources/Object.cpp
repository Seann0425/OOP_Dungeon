#include "../Headers/Object.h"

Object::Object() : name("Unknown"), tag("Unknown") {
}
Object::Object(const std::string name, std::string tag) : name(name), tag(tag) {
}
const std::string Object::getName() const {
    return this->name;
}
const std::string Object::getTag() const {
    return this->tag;
}