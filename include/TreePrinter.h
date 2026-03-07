#pragma once

#include "FsNode.h"
#include <iostream>

class TreePrinter
{
public:
    void Print(const FsNode& node, int indent = 0) const;
};
