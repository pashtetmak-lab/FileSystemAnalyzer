#include "../include/TreeBuilder.h"

#include <vector>

std::unique_ptr<FsNode>
TreeBuilder::MakeNode(const FileSystemScanner::ScanEntry& entry)
{
    if (entry.is_directory) {
        return std::make_unique<FsNode>(FsNode::DirInfo{entry.path, 0});
    }

    return std::make_unique<FsNode>(
        FsNode::FileInfo{entry.path, entry.size_bytes}
    );
}

std::unique_ptr<FsNode>
TreeBuilder::Build(std::span<const FileSystemScanner::ScanEntry> entries) const
{
    if (entries.empty()) {
        return nullptr;
    }

    auto root = MakeNode(entries.front());

    std::vector<FsNode*> depth_nodes;
    depth_nodes.push_back(root.get());

    for (std::size_t i = 1; i < entries.size(); ++i) {
        const auto& entry = entries[i];
        int depth = entry.depth;

        if (depth <= 0) {
            depth = 1;
        }

        if (depth >= static_cast<int>(depth_nodes.size())) {
            depth_nodes.resize(depth + 1, nullptr);
        }

        FsNode* parent_node = depth_nodes[depth - 1];
        if (parent_node == nullptr) {
            parent_node = root.get();
        }

        auto node = MakeNode(entry);
        FsNode* raw_node = node.get();

        parent_node->addChild(std::move(node));
        depth_nodes[depth] = raw_node;
    }

    return root;
}
