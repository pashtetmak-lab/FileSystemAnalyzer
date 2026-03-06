#include "include/Application.h"
#include "include/ArgsParser.h"
#include "include/FileSystemScanner.h"
#include "include/FsNode.h"
#include "include/TreeBuilder.h"
#include "include/Application.h"
#include "include/ArgsParser.h"
#include "include/FileSystemScanner.h"
#include "include/FsNode.h"
#include "include/TreeBuilder.h"
#include <iostream>


void PrintTree(const FsNode& node, int indent = 0)
{
    for (int i = 0; i < indent; ++i)
        std::cout << "  ";

    if (node.isFile())
    {
        const auto& file = node.file();
        std::cout << file.path.filename().string()
                  << " (" << file.size_bytes << " B)"
                  << std::endl;
    }
    else
    {
        const auto& dir = node.directory();
        std::cout << dir.path.filename().string()
                  << "/"
                  << std::endl;

        for (const auto& child : node.children())
        {
            PrintTree(*child, indent + 1);
        }
    }
}

int main()
{
    FileSystemScanner scanner;

    FileSystemScanner::ScanConfig config;
    config.root = ".";

    auto entries = scanner.Scan(config);

    std::cout << "Scanned entries: " << entries.size() << std::endl;

    TreeBuilder builder;

    auto root = builder.Build(entries);

    if (!root)
    {
        std::cout << "Tree build failed\n";
        return 1;
    }

    std::cout << "\nFilesystem tree:\n";
    PrintTree(*root);

    return 0;
}
/*
int main() {
    Application app;
    app.Run();
    return 0;
}
*/

//тест для FileSystemScanner:

/*
#include <iostream>

int main(int argc, char** argv) {
    FileSystemScanner scanner;

    FileSystemScanner::ScanConfig cfg;
    cfg.root = (argc >= 2) ? argv[1] : std::filesystem::path{"."};
    cfg.max_depth = 2; // для теста ограничим глубину

    const auto entries = scanner.Scan(cfg);

    std::cout << "Scanned entries: " << entries.size() << "\n\n";

    for (const auto& e : entries) {
        for (int i = 0; i < e.depth; ++i) std::cout << "  ";

        std::cout
            << (e.is_directory ? "[D] " : "[F] ")
            << e.path.string();

        if (!e.is_directory) {
            std::cout << " (" << e.size_bytes << " bytes)";
        }
        std::cout << "\n";
    }

    return 0;
}

*/

/*
//тест для FsNode:
#include <iostream>

int main()
{
    FsNode root(FsNode::DirInfo{".", 0});

    auto file = std::make_unique<FsNode>(
        FsNode::FileInfo{"file.txt", 100}
    );

    root.addChild(std::move(file));

    std::cout << "Children count: "
              << root.children().size()
              << std::endl;

    return 0;
}



// Test for TreeBuilder:
#include <iostream>
#include <string>

// Print a single node and recursively print all children to verify the built tree.
void PrintTree(const FsNode& node, int indent = 0) {
    std::cout << std::string(indent, ' ');

    if (node.isDirectory()) {
        std::cout << "[D] " << node.directory().path.string() << '\n';
    } else {
        std::cout << "[F] " << node.file().path.string()
                  << " (" << node.file().size_bytes << " bytes)\n";
    }

    for (const auto& child : node.children()) {
        PrintTree(*child, indent + 2);
    }
}

/*
int main() {
    const std::vector<FileSystemScanner::ScanEntry> entries{
        {std::filesystem::path{"project"}, true, 0, 0},
        {std::filesystem::path{"project/docs"}, true, 0, 1},
        {std::filesystem::path{"project/src"}, true, 0, 1},
        {std::filesystem::path{"project/README.md"}, false, 120, 1},
        {std::filesystem::path{"project/docs/spec.txt"}, false, 64, 2},
        {std::filesystem::path{"project/src/main.cpp"}, false, 256, 2}
    };

    TreeBuilder builder;
    auto tree = builder.Build(entries);

    if (!tree) {
        std::cerr << "TreeBuilder test failed: root node was not created.\n";
        return 1;
    }

    std::cout << "TreeBuilder test output:\n";
    PrintTree(*tree);

    std::cout << "\n";
    std::cout << "Root children count: " << tree->children().size() << '\n';

    if (tree->children().size() != 3) {
        std::cerr << "TreeBuilder test failed: expected 3 root children.\n";
        return 1;
    }

    std::cout << "TreeBuilder test passed.\n";
    return 0;
}

*/
