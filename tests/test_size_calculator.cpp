#include "SizeCalculator.h"
#include "FsNode.h"

#include <cassert>
#include <filesystem>
#include <memory>

void TestCalculateDirectorySize()
{
    namespace fs = std::filesystem;

    auto root = std::make_unique<FsNode>(FsNode::DirInfo{fs::path("root"), 0});

    auto file1 = std::make_unique<FsNode>(FsNode::FileInfo{fs::path("a.txt"), 100});
    auto file2 = std::make_unique<FsNode>(FsNode::FileInfo{fs::path("b.txt"), 200});

    root->addChild(std::move(file1));
    root->addChild(std::move(file2));

    SizeCalculator calc;
    calc.Calculate(*root);

    assert(root->directory().size_bytes == 300);
}
