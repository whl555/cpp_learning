#include <string>
#include "Engine.h"

class Car {
public:
    std::string name;
    Engine *engine;

    Car(std::string name);
    ~Car();
    std::string info();
};