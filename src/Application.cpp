#include "../include/Application.h"

Application::Application()
    : name_("FileSystemAnalyzer") {}

void Application::Run() {
    std::cout << "Hello from Application::Run()\n";
    std::cout << "App name: " << name_ << "\n";
}

