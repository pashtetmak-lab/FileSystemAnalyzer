#include "../include/ArgsParser.h"

#include <string>

void ArgsParser::Parse (
    int argc,
    char* argv[],
    std::filesystem::path& root,
    std::optional<int>& max_depth
)
{
    root = "."; //default
    max_depth = std::nullopt; //default

    if (argc >= 2)
    {
        root = argv[1];
    }

    for (int i = 2; i < argc; ++i)
    {
        std::string arg = argv[i];

        if (arg == "--depth" && i + 1 < argc)
        {
            max_depth = std::stoi(argv[i + 1]);
            ++i;
        }
    }
}
