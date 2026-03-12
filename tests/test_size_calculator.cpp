#include "../include/SizeCalculator.h"
#include "../include/FsNode.h"

#include <cassert>
#include <filesystem>
#include <fstream>
#include <memory>

void TestCalculateDirectorySize()
{
    namespace fs = std::filesystem;

    fs::path dir = "test_tmp_dir";
    fs::create_directory(dir);

    fs::path file1 = dir / "a.txt";
    fs::path file2 = dir / "b.txt";

    std::ofstream(file1) << "12345";
    std::ofstream(file2) << "1234567890";


    auto root = std::make_unique<FsNode>(FsNode::DirInfo{dir});

    root->addChild(std::make_unique<FsNode>(
        FsNode::FileInfo{file1}));

    root->addChild(std::make_unique<FsNode>(
        FsNode::FileInfo{file2}));

    SizeCalculator calc;

    auto size = calc.Calculate(*root);

    assert(size == 15);

    fs::remove_all(dir);
}
