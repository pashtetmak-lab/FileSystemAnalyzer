cmake_minimum_required(VERSION 4.2.3)

project(FileSystemAnalyzer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(FileSystemAnalyzer
        main.cpp
        src/Application.cpp
        src/ArgsParser.cpp
        src/FileSystemScanner.cpp
        src/TreeBuilder.cpp
        src/FsNode.cpp
        src/SizeCalculator.cpp
        src/TreePrinter.cpp
)

target_include_directories(FileSystemAnalyzer PRIVATE include)

#тест для tree builder

enable_testing()

add_executable(test_tree_builder
        tests/test_tree_builder.cpp
        src/FsNode.cpp
        src/TreeBuilder.cpp
)
target_include_directories(test_tree_builder PRIVATE include)
add_test(NAME test_tree_builder COMMAND test_tree_builder)


#тест для tree printer
add_executable(test_tree_printer
        tests/test_tree_printer.cpp
        src/FsNode.cpp
        src/TreePrinter.cpp
)
target_include_directories(test_tree_printer PRIVATE include)
add_test(NAME test_tree_printer COMMAND test_tree_printer)
