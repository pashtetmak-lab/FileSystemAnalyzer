#pragma once

#include <filesystem>
#include <variant>
#include <vector>
#include <memory>

class FsNode
{
public:
    struct FileInfo
    {
        std::filesystem::path path;
        std::uintmax_t size_bytes{};
    };
    struct DirInfo
    {
        std::filesystem::path path;
        std::uintmax_t total_size{0};
    };
    using NodeData = std::variant<FileInfo, DirInfo>;
public:
    explicit FsNode(FileInfo file);
    explicit FsNode(DirInfo dir);
    bool isFile() const;
    bool isDirectory() const;
    FileInfo& file();
    const FileInfo& file() const;
    DirInfo& directory();
    const DirInfo& directory() const;
    void addChild(std::unique_ptr<FsNode> child);
    const std::vector<std::unique_ptr<FsNode>>& children() const;
private:
    NodeData data_;
    std::vector<std::unique_ptr<FsNode>> children_;
};
