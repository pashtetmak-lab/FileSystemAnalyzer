#include "../include/FileSystemScanner.h"

// FileSystemScanner.cpp

std::vector<FileSystemScanner::ScanEntry>
FileSystemScanner::Scan(const ScanConfig& cfg) const {

    std::vector<ScanEntry> result;

    try {
        if (!std::filesystem::exists(cfg.root)) {
            return result;
        }

        ScanEntry root_entry;
        root_entry.path = cfg.root;
        root_entry.depth = 0;
        root_entry.is_directory = std::filesystem::is_directory(cfg.root);

        if (!root_entry.is_directory) {
            root_entry.size_bytes = std::filesystem::file_size(cfg.root);
        }
        result.push_back(root_entry);

        if (!root_entry.is_directory) {
            return result;
        }

        auto opts = std::filesystem::directory_options::skip_permission_denied;

        for (std::filesystem::recursive_directory_iterator it(cfg.root, opts), end;
             it != end; ++it) {

            const int depth = it.depth() + 1;

            if (cfg.max_depth && depth > *cfg.max_depth) {
                it.disable_recursion_pending();
                continue;
            }

            ScanEntry entry;
            entry.path = it->path();
            entry.depth = depth;

            entry.is_directory = it->is_directory(); // uses iterator cached status

            if (!entry.is_directory) {
                entry.size_bytes = it->file_size();
            }

            result.push_back(entry);
             }
    }

    catch (const std::filesystem::filesystem_error&) {}

    return result;
}