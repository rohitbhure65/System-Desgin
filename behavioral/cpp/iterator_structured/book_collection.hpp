#pragma once
#include "interfaces.hpp"
#include <vector>

template <typename T>
class BookCollection : public Aggregate<T> {
private:
    std::vector<T> items;
    
public:
    void add(const T& item) {
        items.push_back(item);
    }
    
    std::unique_ptr<Iterator<T>> createIterator() override {
        return std::make_unique<BookIterator<T>>(this);
    }
    
    size_t size() const {
        return items.size();
    }
    
    const T& get(size_t index) const {
        return items[index];
    }
    
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
