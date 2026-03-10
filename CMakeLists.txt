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

enable_testing()

add_executable(unit_tests
        tests/test_main.cpp
        tests/test_args_parser.cpp
        tests/test_file_system_scanner.cpp
        tests/test_fs_node.cpp
        tests/test_size_calculator.cpp
        tests/test_tree_builder.cpp
        tests/test_tree_printer.cpp
        src/Application.cpp
        src/ArgsParser.cpp
        src/FileSystemScanner.cpp
        src/TreeBuilder.cpp
        src/FsNode.cpp
        src/SizeCalculator.cpp
        src/TreePrinter.cpp
)

target_include_directories(unit_tests PRIVATE include)

add_test(NAME unit_tests COMMAND unit_tests)
