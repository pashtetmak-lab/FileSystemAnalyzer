#include "../include/ArgsParser.h"

#include <string>

FileSystemScanner::ScanConfig
ArgsParser::Parse(int argc, char* argv[]) const
{
    FileSystemScanner::ScanConfig config;

    if (argc >= 2)
    {
        config.root = argv[1];
    }

    for (int i = 2; i < argc; ++i)
    {
        std::string arg = argv[i];

        if (arg == "--depth" && i + 1 < argc)
        {
            config.max_depth = std::stoi(argv[i + 1]);
            ++i;
        }
    }

    return config;
}
