#include <iostream>
#include "src/Car.h"

/**
 * Run: g++ main.cpp ./src/Car.cpp ./src/Engine.cpp -o main
 */
int main()
{
    Car *car = new Car("Model 3");
    car->engine = new Engine("BMW");
    std::cout << car->info() << std::endl;
    delete car;
    return 0;
}