#include <exception>
#include <iostream>

#include "../include/ArgsParser.h"
#include "../include/FileSystemScanner.h"
#include "../include/SizeCalculator.h"
#include "../include/TreeBuilder.h"
#include "../include/TreePrinter.h"
#include "../include/Application.h"

int Application::Run(int argc, char* argv[])
{
    try
    {
        std::filesystem::path root_path;
        std::optional<int> max_depth;
        ArgsParser parser;
        parser.Parse(argc, argv, root_path, max_depth);

        FileSystemScanner scanner;
        auto entries = scanner.Scan(root_path, max_depth);

        TreeBuilder builder;
        auto root = builder.BuildTree(entries);

        if (!root)
        {
            std::cerr << "Error: failed to build file system tree\n";
            return 1;
        }

        SizeCalculator calculator;
        calculator.Calculate(*root);

        TreePrinter printer;
        printer.Print(*root);

        return 0;
    }
    catch (std::exception& ex)
    {
        std::cerr << "Error: " << ex.what() << '\n';
        return 1;
    }
}
