#include "../include/TreePrinter.h"
#include "../include/FsNode.h"

#include <cassert>

#include <filesystem>
#include <memory>
#include <sstream>
#include <iostream>

void TestTreePrinterOutputsNodeNames()
{
    namespace fs = std::filesystem;

    auto root = std::make_unique<FsNode>(FsNode::DirInfo{fs::path("root"), 0});
    auto file = std::make_unique<FsNode>(FsNode::FileInfo{fs::path("file.txt"), 100});

    root->addChild(std::move(file));

    TreePrinter printer;

    std::ostringstream buffer;
    auto* old_buf = std::cout.rdbuf(buffer.rdbuf());

    printer.Print(*root);

    std::cout.rdbuf(old_buf);

    std::string output = buffer.str();

    assert(output.find("root") != std::string::npos);
    assert(output.find("file.txt") != std::string::npos);
}
