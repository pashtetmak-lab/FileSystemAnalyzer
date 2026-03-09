#include <cassert>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>

#include "../include/FsNode.h"
#include "../include/TreePrinter.h"

int main() {
    FsNode root(FsNode::DirInfo{std::filesystem::path{"project"}, 100});

    root.addChild(std::make_unique<FsNode>(
        FsNode::FileInfo{std::filesystem::path{"project/file.txt"}, 100}
    ));

    TreePrinter printer;
    std::ostringstream captured;
    std::streambuf* old_buf = std::cout.rdbuf(captured.rdbuf());
    printer.Print(root);
    std::cout.rdbuf(old_buf);

    const std::string output = captured.str();
    assert(output.find("project/ (100 B)") != std::string::npos);
    assert(output.find("file.txt (100 B)") != std::string::npos);

    std::cout << "test_tree_printer passed\n";
    return 0;
}
