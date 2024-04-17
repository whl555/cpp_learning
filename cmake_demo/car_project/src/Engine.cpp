#include "Engine.h"

Engine::Engine(std::string vendor) {
    this->vendor = vendor;
}
std::string Engine::info() {
    return "I'm an engine by vendor: " + vendor;
}
