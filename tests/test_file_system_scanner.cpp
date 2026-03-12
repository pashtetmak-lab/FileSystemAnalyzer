#include "../include/FileSystemScanner.h"

#include <cassert>
#include <filesystem>
#include <fstream>
#include <optional>
#include <string>

/*
fsa_scanner_test/
    file.txt
    nested/
        inner.txt
*/
// Тестовая файловая система
std::filesystem::path MakeScannerTestDir()
{
    auto root = std::filesystem::temp_directory_path() / "fsa_scanner_test";
    std::filesystem::remove_all(root);
    std::filesystem::create_directories(root / "nested");
    std::ofstream(root / "file.txt") << "abc";
    std::ofstream(root / "nested" / "inner.txt") << "xyz";
    return root;
}

// Проверка что не пусто, первый элемент root
void TestScanReturnsRoot()
{
    auto root = MakeScannerTestDir();
    FileSystemScanner scanner;

    auto paths = scanner.Scan(root);

    assert(!paths.empty());
    assert(paths.front() == root);

    std::filesystem::remove_all(root);
}

// Проверка что при глубине 1, только 3 объекта попадает
void TestScanRespectsDepth()
{
    auto root = MakeScannerTestDir();
    FileSystemScanner scanner;

    auto paths = scanner.Scan(root, 1);

    assert(paths.size() == 3);

    std::filesystem::remove_all(root);
}
