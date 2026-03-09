#include <cassert>
#include <filesystem>
#include <iostream>
#include <vector>

#include "../include/FileSystemScanner.h"
#include "../include/TreeBuilder.h"

int main() {
    std::vector<FileSystemScanner::ScanEntry> entries{
        {std::filesystem::path{"project"}, true, 0, 0},
        {std::filesystem::path{"project/file.txt"}, false, 100, 1},
    };

    TreeBuilder builder;
    auto tree = builder.Build(entries);

    assert(tree != nullptr);
    assert(tree->isDirectory());
    assert(tree->directory().path == std::filesystem::path{"project"});
    assert(tree->children().size() == 1);
    assert(tree->children()[0]->isFile());
    assert(tree->children()[0]->file().path.filename() == "file.txt");
    assert(tree->children()[0]->file().size_bytes == 100);

    std::vector<FileSystemScanner::ScanEntry> empty_entries;
    auto empty = builder.Build(empty_entries);
    assert(empty == nullptr);

    std::cout << "test_tree_builder passed\n";
    return 0;
}
