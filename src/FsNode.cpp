#include "../include/FsNode.h"
#include <stdexcept>

FsNode::FsNode(FileInfo file) : data_(std::move(file)){}
FsNode::FsNode(DirInfo dir) : data_(std::move(dir)){}
bool FsNode::isFile() const
{
    return std::holds_alternative<FileInfo>(data_);
}
bool FsNode::isDirectory() const
{
    return std::holds_alternative<DirInfo>(data_);
}
FsNode::FileInfo& FsNode::file()
{
    if (!isFile())
        throw std::logic_error("Not a file");
    return std::get<FileInfo>(data_);
}
FsNode::DirInfo& FsNode::directory()
{
    if (!isDirectory())
        throw std::logic_error("Not a directory");
    return std::get<DirInfo>(data_);
}
void FsNode::addChild(std::unique_ptr<FsNode> child)
{
    children_.push_back(std::move(child));
}
const std::vector<std::unique_ptr<FsNode>>& FsNode::children() const
{
    return children_;
}
