#pragma once

#include <filesystem>
#include <optional>
#include <vector>

class FileSystemScanner {
public:
    std::vector<std::filesystem::path> Scan(
        const std::filesystem::path& root = ".",
        std::optional<int> max_depth = std::nullopt
    );
};
