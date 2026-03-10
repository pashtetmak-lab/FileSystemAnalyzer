#pragma once

#include <filesystem>
#include <optional>

class ArgsParser {
public:
    void Parse(
        // argc - кол-во адресов
        // argv[] - массив из указателей на них
        int argc, char* argv[],
        std::filesystem::path& root,
        std::optional<int>& max_depth
    );
};
