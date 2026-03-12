#include "../include/ArgsParser.h"

#include <string>
#include <stdexcept>

constexpr bool IsValidDepth(int depth)
{
    return depth >= 0;
}

void ArgsParser::Parse (
    int argc,
    char* argv[],
    Config& config
) {
    config.root_path = "."; //default
    config.max_depth = std::nullopt; //default

    if (argc >= 2)
    {
        config.root_path = argv[1];
    }

    for (int i = 2; i < argc; ++i) {

        std::string arg = argv[i];

        if (arg == "--depth" && i + 1 < argc) {
            // stoi преобразование в int
            int depth = std::stoi(argv[i + 1]);

            if (!IsValidDepth(depth)) {
                throw std::invalid_argument("Depth must be non-negative");
            }

            config.max_depth = depth;
            ++i;
        }
    }
}
