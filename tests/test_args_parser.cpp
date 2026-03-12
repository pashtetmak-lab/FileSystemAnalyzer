#include "../include/ArgsParser.h"

#include <cassert>
#include <stdexcept>

// проверяем что если вызвать программу вообще
// без аргументов то программа поставит сама
// дефолтные значения
void TestParseDefaultArgs()
{
    ArgsParser parser;
    Config config;

    char arg0[] = "prog";
    char* argv[] = {arg0};

    parser.Parse(1, argv, config);

    assert(config.root_path == std::filesystem::path("."));
    assert(!config.max_depth.has_value());
}

// тест что получает и подставляет значения
void TestParseDepth()
{
    ArgsParser parser;
    Config config;

    char arg0[] = "prog";
    char arg1[] = "root";
    char arg2[] = "--depth";
    char arg3[] = "2";
    char* argv[] = {arg0, arg1, arg2, arg3};

    parser.Parse(4, argv, config);

    assert(config.root_path == std::filesystem::path("root"));
    assert(config.max_depth == 2);
}

// тест что кидает ошибку при отрицательной глубине
void TestRejectNegativeDepth()
{
    ArgsParser parser;
    Config config;

    char arg0[] = "prog";
    char arg1[] = "root";
    char arg2[] = "--depth";
    char arg3[] = "-1";
    char* argv[] = {arg0, arg1, arg2, arg3};

    bool thrown = false;

    try
    {
        parser.Parse(4, argv, config);
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
