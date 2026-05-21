#pragma once
#include "interfaces.hpp"
#include <vector>
#include <memory>

template <typename T>
class TreeNode {
public:
    T data;
    std::shared_ptr<TreeNode<T>> left;
    std::shared_ptr<TreeNode<T>> right;
    
    TreeNode(T data) : data(data) {}
};

template <typename T>
class BinaryTreeIterator : public Iterator<T> {
private:
    std::vector<std::shared_ptr<TreeNode<T>>> stack;
    std::shared_ptr<TreeNode<T>> current;
    
    void pushLeft(std::shared_ptr<TreeNode<T>> node) {
        while (node) {
            stack.push_back(node);
            node = node->left;
        }
    }
    
public:
    BinaryTreeIterator(std::shared_ptr<TreeNode<T>> root) {
        pushLeft(root);
    }
    
    bool hasNext() override {
        return !stack.empty();
    }
    
    T next() override {
        if (!hasNext()) return T();
        
        auto node = stack.back();
        stack.pop_back();
        
        if (node->right) {
            pushLeft(node->right);
        }
        
        return node->data;
    }
};
