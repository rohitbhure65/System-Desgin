#pragma once
#include "interfaces.hpp"
#include <memory>

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
