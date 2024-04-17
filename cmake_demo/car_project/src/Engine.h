#include <string>

class Engine {
public:
    std::string vendor;
    Engine(std::string vendor);
    std::string info();
};