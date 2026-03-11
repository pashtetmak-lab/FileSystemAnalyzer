#include "../include/TreeBuilder.h"

#include <cassert>
#include <filesystem>
#include <fstream>
#include <vector>

/*
fsa_tree_builder_test/
|-─ file.txt
└-─ subdir/
*/
// функция создает тестовую файловую систему для использования ее в тестах
std::filesystem::path MakeTreeBuilderRoot()
{
    auto root = std::filesystem::temp_directory_path() / "fsa_tree_builder_test";
    std::filesystem::remove_all(root);
    std::filesystem::create_directories(root / "subdir");
    std::ofstream(root / "file.txt") << "abc";
    return root;
}

// Тесты:

// std::filesystem::remove_all(root_path) - очищает структуру после каждого теста

void TestBuildTreeReturnsRoot()
{
    auto root_path = MakeTreeBuilderRoot();
    TreeBuilder builder;

    // передаем только root_path: он должен стать единственным корневым узлом
    auto root = builder.BuildTree({root_path});

    assert(root != nullptr);
    assert(root->isDirectory());

    std::filesystem::remove_all(root_path);
}

// проверка что 2 файла/папки дают два ребенка
void TestBuildTreeCreatesChildren()
{
    auto root_path = MakeTreeBuilderRoot();
    TreeBuilder builder;

    auto root = builder.BuildTree({root_path, root_path / "file.txt", root_path / "subdir"});

    assert(root->children().size() == 2);

    std::filesystem::remove_all(root_path);
}

// проверка при пустом входе
void TestBuildTreeReturnsNullForEmptyInput()
{
    TreeBuilder builder;

    auto root = builder.BuildTree({});

    assert(root == nullptr);
}