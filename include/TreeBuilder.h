#pragma once

#include <filesystem>
#include <memory>
#include <span>

#include "FileSystemScanner.h"
#include "FsNode.h"

class TreeBuilder {
public:
    [[nodiscard]] std::unique_ptr<FsNode>
    Build(std::span<const FileSystemScanner::ScanEntry> entries) const;

private:
    [[nodiscard]] static std::unique_ptr<FsNode>
    MakeNode(const FileSystemScanner::ScanEntry& entry);

    [[nodiscard]] static std::filesystem::path
    FindParentPath(const FileSystemScanner::ScanEntry& entry);
};
