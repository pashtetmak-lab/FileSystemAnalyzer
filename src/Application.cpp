#include "../include/Application.h"

#include <iostream>
#include <utility>

Application::Application()
    : name_("FileSystemAnalyzer") {}

void Application::Run() {
    std::cout << "Hello from Application::Run()\n";
    std::cout << "App name: " << name_ << "\n";
}

