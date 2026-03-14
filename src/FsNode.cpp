#include "../include/FsNode.h"
#include <stdexcept>

// std::move используется, чтобы переместить объект а не копировать его.
FsNode::FsNode(FileInfo file)
    : data_(std::move(file))
{
}
// Аналогично предыдущему но теперь variant хранит DirInfo.
FsNode::FsNode(DirInfo dir)
    : data_(std::move(dir))
{
}
// std::holds_alternative проверяет какой именно тип сейчас хранится внутри std::variant.
bool FsNode::isFile() const
{
    return std::holds_alternative<FileInfo>(data_);
}

// Проверяет является ли узел директорией.
bool FsNode::isDirectory() const
{
    return std::holds_alternative<DirInfo>(data_);
}

// Возвращает ссылку на FileInfo. Если узел не является файлом выбрасывается исключение.
// Это защищает от неправильного использования класса.
FsNode::FileInfo& FsNode::file()
{
    if (!isFile())
        throw std::logic_error("Not a file");

    // std::get извлекает конкретный тип из variant
    return std::get<FileInfo>(data_);
}

// Возвращает ссылку на DirInfo.
FsNode::DirInfo& FsNode::directory()
{
    if (!isDirectory())
        throw std::logic_error("Not a directory");

    return std::get<DirInfo>(data_);
}

// Добавляет дочерний узел в дерево children_ хранит unique_ptr через std::move.
void FsNode::addChild(std::unique_ptr<FsNode> child)
{
    children_.push_back(std::move(child));
}


// Возвращается const-ссылка, чтобы: не копировать vector
const std::vector<std::unique_ptr<FsNode>>& FsNode::children() const
{
    return children_;
}

const FsNode::FileInfo& FsNode::file() const
{
    if (!isFile())
        throw std::logic_error("Not a file");

    return std::get<FileInfo>(data_);
}

const FsNode::DirInfo& FsNode::directory() const
{
    if (!isDirectory())
        throw std::logic_error("Not a directory");

    return std::get<DirInfo>(data_);
}
