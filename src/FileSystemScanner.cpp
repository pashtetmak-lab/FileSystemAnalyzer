#include "../include/FileSystemScanner.h"

std::vector<FileSystemScanner::ScanEntry>
FileSystemScanner::Scan(const ScanConfig& cfg) const
{
    std::vector<ScanEntry> result;
    std::error_code ec;

    if (!std::filesystem::exists(cfg.root, ec) || ec) {
        return result;
    }

    const bool root_is_dir = std::filesystem::is_directory(cfg.root, ec);
    if (ec) {
        return result;
    }

    ScanEntry root_entry;
    root_entry.path = cfg.root;
    root_entry.is_directory = root_is_dir;
    root_entry.depth = 0;
    if (!root_is_dir) {
        root_entry.size_bytes = std::filesystem::file_size(cfg.root, ec);
        if (ec) {
            root_entry.size_bytes = 0;
        }
    }
    result.push_back(root_entry);

    if (!root_is_dir) {
        return result;
    }

    const auto options = std::filesystem::directory_options::skip_permission_denied;
    std::filesystem::recursive_directory_iterator it(cfg.root, options, ec);
    std::filesystem::recursive_directory_iterator end;
    if (ec) {
        return result;
    }

    for (; it != end; it.increment(ec)) {
        if (ec) {
            ec.clear();
            continue;
        }

        const int depth = it.depth() + 1;
        if (cfg.max_depth && depth > *cfg.max_depth) {
            it.disable_recursion_pending();
            continue;
        }

        ScanEntry entry;
        entry.path = it->path();
        entry.depth = depth;
        entry.is_directory = it->is_directory(ec);
        if (ec) {
            ec.clear();
            continue;
        }

        if (!entry.is_directory) {
            entry.size_bytes = it->file_size(ec);
            if (ec) {
                ec.clear();
                entry.size_bytes = 0;
            }
        }

        result.push_back(entry);
    }

    return result;
}