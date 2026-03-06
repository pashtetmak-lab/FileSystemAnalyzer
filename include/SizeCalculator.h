#pragma once

#include "FsNode.h"

class SizeCalculator
{
public:
    std::uintmax_t Calculate(FsNode& node) const;
};
