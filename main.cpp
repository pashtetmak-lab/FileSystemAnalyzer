#include "include/Application.h"
#include "include/ArgsParser.h"
#include "include/FileSystemScanner.h"

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