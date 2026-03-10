#include "../include/TreePrinter.h"

void TreePrinter::Print(const FsNode& node, int indent)
{
    for (int i = 0; i < indent; ++i)
    {
        std::cout << "  ";
    }

    if (node.isFile())
    {
        auto& file = node.file();

        std::cout << file.path.filename().string()
                  << " (" << file.size_bytes << " B)"
                  << std::endl;
    }
    else
    {
        auto& dir = node.directory();

        std::cout << dir.path.filename().string()
                  << "/ (" << dir.total_size << " B)"
                  << std::endl;

        for (auto& child : node.children())
        {
            Print(*child, indent + 1);
        }
    }
}
