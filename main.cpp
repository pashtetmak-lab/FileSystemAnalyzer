#include "include/Application.h"
#include "include/ArgsParser.h"
#include "include/FileSystemScanner.h"
#include "include/FsNode.h"
/*
int main() {
    Application app;
    app.Run();
    return 0;
}
*/

#include "include/FileSystemScanner.h"


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
*/
