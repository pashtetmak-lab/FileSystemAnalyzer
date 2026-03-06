#include "../include/SizeCalculator.h"

std::uintmax_t SizeCalculator::Calculate(FsNode& node) const
{
    if (node.isFile())
    {
        return node.file().size_bytes;
    }

    auto& dir = node.directory();

    std::uintmax_t sum = 0;

    for (auto& child : node.children())
    {
        sum += Calculate(*child);
    }

    dir.total_size = sum;

    return sum;
}
