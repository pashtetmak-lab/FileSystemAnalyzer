#include "include/Application.h"
#include <iostream>
#include "include/ArgsParser.h"
#include "include/FileSystemScanner.h"
#include "include/TreeBuilder.h"
#include "include/SizeCalculator.h"
#include "include/TreePrinter.h"

int main(int argc, char* argv[])
{
    ArgsParser parser;
    auto config = parser.Parse(argc, argv);

    FileSystemScanner scanner;
    auto entries = scanner.Scan(config);

    TreeBuilder builder;
    auto root = builder.Build(entries);

    if (!root)
        return 1;

    SizeCalculator calc;
    calc.Calculate(*root);

    TreePrinter printer;
    printer.Print(*root);

    return 0;
}
