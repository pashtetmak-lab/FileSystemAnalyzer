#include "../include/FsNode.h"

#include <cassert>
#include <memory>

void TestNodeType()
{
    FsNode file_node(FsNode::FileInfo{"file.txt", 10});
    FsNode dir_node(FsNode::DirInfo{"root", 0});

    assert(file_node.isFile());
    assert(!file_node.isDirectory());
    assert(dir_node.isDirectory());
    assert(!dir_node.isFile());
}

void TestAddChild()
{
    FsNode parent(FsNode::DirInfo{"root", 0});
    auto child = std::make_unique<FsNode>(FsNode::FileInfo{"a.txt", 10});

    parent.addChild(std::move(child));

    assert(parent.children().size() == 1);
    assert(parent.children()[0]->isFile());
}
