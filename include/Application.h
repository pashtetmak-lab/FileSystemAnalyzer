#pragma once

#include <string>

class Application {
public:
    Application();
    void Run();
    void print();
private:
    std::string name_;
};