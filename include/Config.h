#pragma once

#include <filesystem>
#include <optional>

struct Config
{
    std::filesystem::path root_path = ".";
    std::optional<int> max_depth = std::nullopt;
};
