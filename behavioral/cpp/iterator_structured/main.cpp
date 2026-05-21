#include "interfaces.hpp"
#include "book_collection.hpp"
#include "tree_iterator.hpp"
#include "custom_list.hpp"
#include <iostream>

int main() {
    std::cout << "=== Iterator Pattern Demo ===" << std::endl << std::endl;
    
    // Example 1: Book Collection
    std::cout << "--- Book Collection Example ---" << std::endl;
    
    BookCollection<std::string> books;
    books.add("Design Patterns");
    books.add("Clean Code");
    books.add("Refactoring");
    books.add("The Pragmatic Programmer");
    
    auto bookIterator = books.createIterator();
    
    std::cout << "\nIterating through books:" << std::endl;
    while (bookIterator->hasNext()) {
        std::cout << "  - " << bookIterator->next() << std::endl;
    }
    
    std::cout << std::endl;
    
    // Example 2: Binary Tree Traversal
    std::cout << "--- Binary Tree Traversal Example ---" << std::endl;
    
    auto root = std::make_shared<TreeNode<int>>(5);
    root->left = std::make_shared<TreeNode<int>>(3);
    root->right = std::make_shared<TreeNode<int>>(7);
    root->left->left = std::make_shared<TreeNode<int>>(1);
    root->left->right = std::make_shared<TreeNode<int>>(4);
    root->right->left = std::make_shared<TreeNode<int>>(6);
    root->right->right = std::make_shared<TreeNode<int>>(9);
    
    BinaryTreeIterator<int> treeIterator(root);
    
    std::cout << "\nIn-order traversal:" << std::endl;
    while (treeIterator.hasNext()) {
        std::cout << "  " << treeIterator.next() << std::endl;
    }
    
    std::cout << std::endl;
    
    // Example 3: Custom List Iterator
    std::cout << "--- Custom List Iterator Example ---" << std::endl;
    
    CustomList<int> numbers;
    numbers.add(10);
    numbers.add(20);
    numbers.add(30);
    numbers.add(40);
    numbers.add(50);
    
    auto listIterator = numbers.iterator();
    
    std::cout << "\nIterating through custom list:" << std::endl;
    while (listIterator->hasNext()) {
        std::cout << "  " << listIterator->next() << std::endl;
    }
    
    return 0;
}
