#pragma once

#include <filesystem>
#include <memory>
#include <span>

#include "FileSystemScanner.h"
#include "FsNode.h"

class TreeBuilder {
public:
    std::unique_ptr<FsNode>
    Build(std::span<const FileSystemScanner::ScanEntry> entries) const;

private:
    static std::unique_ptr<FsNode>
    MakeNode(const FileSystemScanner::ScanEntry& entry);
};
