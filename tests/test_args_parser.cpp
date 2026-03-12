#include "../include/ArgsParser.h"

#include <cassert>
#include <filesystem>
#include <optional>
#include <stdexcept>

// проверяем что если вызвать программу вообще
// без аргументов то программа поставит сама
// дефолтные значения
void TestParseDefaultArgs()
{
    ArgsParser parser;
    std::filesystem::path root;
    std::optional<int> max_depth;

    char arg0[] = "prog";
    char* argv[] = {arg0};

    parser.Parse(1, argv, root, max_depth);

    assert(root == std::filesystem::path("."));
    assert(!max_depth.has_value());
}

// тест что получает и подставляет значения
void TestParseDepth()
{
    ArgsParser parser;
    std::filesystem::path root;
    std::optional<int> max_depth;

    char arg0[] = "prog";
    char arg1[] = "root";
    char arg2[] = "--depth";
    char arg3[] = "2";
    char* argv[] = {arg0, arg1, arg2, arg3};

    parser.Parse(4, argv, root, max_depth);

    assert(root == std::filesystem::path("root"));
    assert(max_depth == 2);
}

// тест что кидает ошибку при отрицательной глубине
void TestRejectNegativeDepth()
{
    ArgsParser parser;
    std::filesystem::path root;
    std::optional<int> max_depth;

    char arg0[] = "prog";
    char arg1[] = "root";
    char arg2[] = "--depth";
    char arg3[] = "-1";
    char* argv[] = {arg0, arg1, arg2, arg3};

    bool thrown = false;

    try
    {
        parser.Parse(4, argv, root, max_depth);
    }
    // const - объект не будет меняться
    // & - ссылка, чтобы не создавать люшнюю копию
    // ловим что ошибку кинуло
    catch (const std::invalid_argument&)
    {
        thrown = true;
    }

    assert(thrown);
}
