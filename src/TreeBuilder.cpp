#include "../include/TreeBuilder.h"

#include <filesystem>
#include <vector>

// читает пути из вектора, не меняя их
std::unique_ptr<FsNode>
TreeBuilder::BuildTree(const std::vector<std::filesystem::path>& paths)
{
    if (paths.empty()) {
        return nullptr;
    }

    // первый элемент: root
    auto& root_path = paths.front();

    std::unique_ptr<FsNode> root;

    // root type
    if (std::filesystem::is_directory(root_path)) {
        root = std::make_unique<FsNode>(FsNode::DirInfo{root_path, 0});
    } else {
        root = std::make_unique<FsNode>(FsNode::FileInfo{root_path, 0});
    }

    // указатели на узлы
    std::vector<FsNode*> depth_nodes;

    // добавляем в вектор указатель на root
    depth_nodes.push_back(root.get());

    // следующие пути
    for (std::size_t i = 1; i < paths.size(); ++i) {

        auto& path = paths[i];

        auto relative = path.lexically_relative(root_path); // путь от root

        // приводим глубину к int
        int depth = static_cast<int>(std::distance(relative.begin(), relative.end()));

        if (depth <= 0) { depth = 1; }

        if (depth >= static_cast<int>(depth_nodes.size())) {
            depth_nodes.resize(depth + 1, nullptr);
        }

        // ищем родителя, если нет то назначаем
        FsNode* parent_node = depth_nodes[depth - 1];
        if (parent_node == nullptr) {
            parent_node = root.get();
        }

        // new node
        std::unique_ptr<FsNode> node;

        if (std::filesystem::is_directory(path)) {
            node = std::make_unique<FsNode>(FsNode::DirInfo{path, 0});
        } else {
            node = std::make_unique<FsNode>(FsNode::FileInfo{path, 0});
        }

        FsNode* raw_node = node.get();

        parent_node->addChild(std::move(node));

        // сохраняем указатель на новый узел в массив по его глубине
        depth_nodes[depth] = raw_node;
    }

    return root;
}
