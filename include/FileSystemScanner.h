#pragma once

//FileSystemScanner - scans through file system and returns directories/files

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

        std::filesystem::path path; // full path to node

        bool is_directory{
            false //default
        };

        std::uintmax_t size_bytes{0};

        int depth{0};
    };

    // Scan filesystem and return a flat list of entries.
    [[nodiscard]] std::vector<ScanEntry> Scan(const ScanConfig& cfg) const;
};