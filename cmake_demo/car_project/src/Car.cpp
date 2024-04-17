#include "Car.h"

Car::Car(std::string name) {
    this->name = name;
}
Car::~Car() {
    delete engine;
}
std::string Car::info() {
    return "I'm a car named: " + name + "\n" +
        "I have an engine maked by: " + engine->vendor;
}