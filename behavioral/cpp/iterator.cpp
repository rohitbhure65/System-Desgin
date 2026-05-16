/*
 * ITERATOR DESIGN PATTERN
 * 
 * WHAT IS IT?
 * The Iterator pattern provides a way to access the elements of an aggregate object sequentially without exposing its underlying representation.
 * It traverses the elements of a collection without knowing its internal structure.
 * 
 * WHY DOES IT EXIST?
 * - When you want to access a collection's contents without exposing its internal representation
 * - When you want to provide multiple ways to traverse a collection
 * - When you want to provide a uniform interface for traversing different data structures
 * 
 * WHEN TO USE IT?
 * - When you have a collection of objects and want to traverse it without exposing its internal structure
 * - When you want to provide multiple traversal algorithms for the same collection
 * - When you want to simplify the interface for accessing a complex data structure
 * - Common use cases: collections, tree structures, database result sets, file systems
 * 
 * PROS:
 * - Single Responsibility Principle (separates traversal logic from the collection)
 * - Open/Closed Principle (can add new iterators without changing the collection)
 * - Provides a uniform interface for traversing different collections
 * - Can support multiple traversals simultaneously
 * 
 * CONS:
 * - Can be overkill for simple collections
 * - May violate encapsulation if the iterator exposes too much about the collection
 * - Can be less efficient than direct access
 * - May complicate the code for simple use cases
 * 
 * REAL-WORLD ANALOGY:
 * Think of a TV remote control with channel up/down buttons. You don't need to know how the TV stores channels - you just use the next/previous buttons to navigate. The remote (iterator) provides a simple interface to traverse the channels (collection) without knowing the internal channel storage mechanism.
 */

#include <iostream>
#include <string>
#include <vector>
#include <memory>

// Iterator interface - declares the operations for traversing
template <typename T>
class Iterator {
public:
    virtual ~Iterator() = default;
    virtual bool hasNext() = 0;
    virtual T next() = 0;
};

// Aggregate interface - declares the method for creating an iterator
template <typename T>
class Aggregate {
public:
    virtual ~Aggregate() = default;
    virtual std::unique_ptr<Iterator<T>> createIterator() = 0;
};

// Concrete Aggregate - implements the aggregate interface
template <typename T>
class BookCollection : public Aggregate<T> {
private:
    std::vector<T> items;
    
public:
    void add(const T& item) {
        items.push_back(item);
    }
    
    std::unique_ptr<Iterator<T>> createIterator() override {
        return std::make_unique<BookIterator<T>(this);
    }
    
    size_t size() const {
        return items.size();
    }
    
    const T& get(size_t index) const {
        return items[index];
    }
    
    // Concrete Iterator (nested class)
    class BookIterator : public Iterator<T> {
    private:
        BookCollection* collection;
        size_t position = 0;
        
    public:
        BookIterator(BookCollection* collection) : collection(collection) {}
        
        bool hasNext() override {
            return position < collection->size();
        }
        
        T next() override {
            if (hasNext()) {
                return collection->get(position++);
            }
            return T();
        }
    };
    
    friend class BookIterator;
};

// Example 2: Tree Traversal Iterator
// Shows how Iterator can be used for tree structures

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

// Example 3: Custom Container with Iterator
// Shows how to implement iterator for a custom data structure

template <typename T>
class CustomList {
private:
    struct Node {
        T data;
        std::shared_ptr<Node> next;
        Node(T data) : data(data), next(nullptr) {}
    };
    
    std::shared_ptr<Node> head;
    size_t count;
    
public:
    CustomList() : head(nullptr), count(0) {}
    
    void add(const T& item) {
        auto newNode = std::make_shared<Node>(item);
        if (!head) {
            head = newNode;
        } else {
            auto current = head;
            while (current->next) {
                current = current->next;
            }
            current->next = newNode;
        }
        count++;
    }
    
    std::unique_ptr<Iterator<T>> iterator() {
        return std::make_unique<ListIterator>(head);
    }
    
    class ListIterator : public Iterator<T> {
    private:
        std::shared_ptr<Node> current;
        
    public:
        ListIterator(std::shared_ptr<Node> head) : current(head) {}
        
        bool hasNext() override {
            return current != nullptr;
        }
        
        T next() override {
            if (!hasNext()) return T();
            auto data = current->data;
            current = current->next;
            return data;
        }
    };
};

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
    
    // Build a simple binary tree
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
