#pragma once

#include <filesystem>
#include <memory>
#include <vector>

#include "FsNode.h"

class TreeBuilder {
public:
    std::unique_ptr<FsNode>
    BuildTree(const std::vector<std::filesystem::path>& paths);
};
