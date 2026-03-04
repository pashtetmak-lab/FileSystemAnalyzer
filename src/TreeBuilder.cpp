#include "../include/TreeBuilder.h"

#include <algorithm>
#include <optional>
#include <ranges>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

struct PathHash {
    std::size_t operator()(const std::filesystem::path& path) const noexcept {
        return std::hash<std::string>{}(path.generic_string());
    }
};

std::unique_ptr<FsNode>
TreeBuilder::MakeNode(const FileSystemScanner::ScanEntry& entry) {
    if (entry.is_directory) {
        return std::make_unique<FsNode>(FsNode::DirInfo{entry.path, 0});
    }

    return std::make_unique<FsNode>(
        FsNode::FileInfo{entry.path, entry.size_bytes}
    );
}

std::filesystem::path
TreeBuilder::FindParentPath(const FileSystemScanner::ScanEntry& entry) {
    return entry.path.parent_path();
}

std::unique_ptr<FsNode>
TreeBuilder::Build(std::span<const FileSystemScanner::ScanEntry> entries) const {
    if (entries.empty()) {
        return nullptr;
    }

    std::vector<FileSystemScanner::ScanEntry> sorted_entries(
        entries.begin(), entries.end()
    );

    std::ranges::sort(
        sorted_entries,
        [](const FileSystemScanner::ScanEntry& left,
           const FileSystemScanner::ScanEntry& right) {
            if (left.depth != right.depth) {
                return left.depth < right.depth;
            }

            return left.path.generic_string() < right.path.generic_string();
        }
    );

    auto root = MakeNode(sorted_entries.front());

    std::unordered_map<std::filesystem::path, FsNode*, PathHash> index;
    index.emplace(sorted_entries.front().path, root.get());

    for (std::size_t i = 1; i < sorted_entries.size(); ++i) {
        const auto& entry = sorted_entries[i];
        const auto parent_path = FindParentPath(entry);

        std::optional<FsNode*> parent;
        if (const auto parent_it = index.find(parent_path); parent_it != index.end()) {
            parent = parent_it->second;
        }

        FsNode* parent_node = parent.value_or(root.get());

        auto node = MakeNode(entry);
        FsNode* raw_node = node.get();

        parent_node->addChild(std::move(node));
        index.emplace(entry.path, raw_node);
    }

    return root;
}
