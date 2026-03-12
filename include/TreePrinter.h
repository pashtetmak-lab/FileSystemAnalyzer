#pragma once

#include "FsNode.h"
#include "Config.h"
#include <iostream>
#include <memory>

class TreePrinter
{
public:
    TreePrinter(std::shared_ptr<Config> config = std::make_shared<Config>());
    void Print(const FsNode& node, int indent = 0);

private:
    std::shared_ptr<Config> config_;
};
