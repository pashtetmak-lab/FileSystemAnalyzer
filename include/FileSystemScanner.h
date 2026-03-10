#pragma once

#include <filesystem>
#include <optional>
#include <vector>

class FileSystemScanner {
public:
    struct ScanConfig {
        std::filesystem::path root{"."};
        std::optional<int> max_depth{};
    };

    struct ScanEntry {

        std::filesystem::path path;

        bool is_directory{
            false
        };

        std::uintmax_t size_bytes{0};

        int depth{0};
    };

    [[nodiscard]] std::vector<ScanEntry> Scan(const ScanConfig& cfg) const;
};