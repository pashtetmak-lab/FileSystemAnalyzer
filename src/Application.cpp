#include "../include/ArgsParser.h"
#include "../include/FileSystemScanner.h"
#include "../include/SizeCalculator.h"
#include "../include/TreeBuilder.h"
#include "../include/TreePrinter.h"
#include "../include/Application.h"
#include "../include/Config.h"

#include <memory>

int Application::Run(int argc, char* argv[])
{
    try {
        auto config = std::make_shared<Config>();

        ArgsParser parser;
        parser.Parse(argc, argv, *config);

        FileSystemScanner scanner;
        auto entries = scanner.Scan(config->root_path, config->max_depth);

        TreeBuilder builder;
        auto root = builder.BuildTree(entries);

        SizeCalculator calculator(config);
        calculator.Calculate(*root);

        TreePrinter printer(config);
        printer.Print(*root);

        return 0;
    }
    catch (const std::exception& err) {
        std::cerr << "Error: " << err.what() << std::endl;
        return 1;
    }
}
