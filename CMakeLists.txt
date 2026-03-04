cmake_minimum_required(VERSION 4.2.3)

project(FileSystemAnalyzer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(FileSystemAnalyzer
        main.cpp
        src/Application.cpp
        src/FileSystemScanner.cpp
        src/TreeBuilder.cpp
        src/FsNode.cpp
)