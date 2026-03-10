#include "../include/Application.h"

#include <exception>
#include <iostream>

#include "../include/ArgsParser.h"
#include "../include/FileSystemScanner.h"
#include "../include/SizeCalculator.h"
#include "../include/TreeBuilder.h"
#include "../include/TreePrinter.h"

int Application::Run(int argc, char* argv[]) const
{
    try
    {
        ArgsParser parser;
        const auto config = parser.Parse(argc, argv);

        FileSystemScanner scanner;
        const auto entries = scanner.Scan(config);

        TreeBuilder builder;
        auto root = builder.Build(entries);

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
    catch (const std::exception& ex)
    {
        std::cerr << "Error: " << ex.what() << '\n';
        return 1;
    }
}
