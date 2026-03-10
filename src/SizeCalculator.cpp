#include "../include/SizeCalculator.h"

#include <filesystem>

std::uintmax_t SizeCalculator::Calculate(FsNode& node)
{
    // файл?
    if (node.isFile() == true)
    {
        auto& file = node.file(); //ссылка чтобы не создавать копию
        file.size_bytes = std::filesystem::file_size(file.path);
        return file.size_bytes;
    }
    else //если директория
    {
        auto& dir = node.directory();

        std::uintmax_t sum = 0;

        for (auto& child : node.children())
        {
            sum += Calculate(*child);
        }

        dir.total_size = sum;

        return sum;
    }
}
