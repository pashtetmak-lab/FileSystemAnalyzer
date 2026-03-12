#pragma once

#include "FsNode.h"
#include "Config.h"
#include <memory>

class SizeCalculator
{
private:
    std::shared_ptr<Config> config_;

public:
    SizeCalculator(std::shared_ptr<Config> config = std::make_shared<Config>());
    std::uintmax_t Calculate(FsNode& node);
};
