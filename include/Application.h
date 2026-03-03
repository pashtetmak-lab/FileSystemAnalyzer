#pragma once

#include <string>
#include <iostream>

class Application {
public:
    Application();
    void Run();
    void print();
private:
    std::string name_;
};