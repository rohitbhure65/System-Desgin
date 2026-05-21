#pragma once
#include <string>
#include <memory>
#include <vector>

class Visitor;
class Book;
class Fruit;
class Electronic;

class Visitor {
public:
    virtual ~Visitor() = default;
    virtual void visit(Book* book) = 0;
    virtual void visit(Fruit* fruit) = 0;
    virtual void visit(Electronic* electronic) = 0;
};

class Item {
public:
    virtual ~Item() = default;
    virtual void accept(Visitor* visitor) = 0;
    virtual double getPrice() const = 0;
};

class Book : public Item {
private:
    std::string title;
    std::string author;
    double price;
    
public:
    Book(const std::string& title, const std::string& author, double price)
        : title(title), author(author), price(price) {}
    
    void accept(Visitor* visitor) override {
        visitor->visit(this);
    }
    
    double getPrice() const override {
        return price;
    }
    
    std::string getTitle() const { return title; }
    std::string getAuthor() const { return author; }
};

class Fruit : public Item {
private:
    std::string name;
    double price;
    double weight;
    
public:
    Fruit(const std::string& name, double price, double weight)
        : name(name), price(price), weight(weight) {}
    
    void accept(Visitor* visitor) override {
        visitor->visit(this);
    }
    
    double getPrice() const override {
        return price;
    }
    
    std::string getName() const { return name; }
    double getWeight() const { return weight; }
};

class Electronic : public Item {
private:
    std::string model;
    std::string brand;
    double price;
    
public:
    Electronic(const std::string& brand, const std::string& model, double price)
        : model(model), brand(brand), price(price) {}
    
    void accept(Visitor* visitor) override {
        visitor->visit(this);
    }
    
    double getPrice() const override {
        return price;
    }
    
    std::string getModel() const { return model; }
    std::string getBrand() const { return brand; }
};

class PriceCalculator : public Visitor {
private:
    double totalPrice;
    
public:
    PriceCalculator() : totalPrice(0) {}
    
    void visit(Book* book) override {
        totalPrice += book->getPrice();
        std::cout << "Book: " << book->getTitle() << " - $" << book->getPrice() << std::endl;
    }
    
    void visit(Fruit* fruit) override {
        totalPrice += fruit->getPrice();
        std::cout << "Fruit: " << fruit->getName() << " - $" << fruit->getPrice() << std::endl;
    }
    
    void visit(Electronic* electronic) override {
        totalPrice += electronic->getPrice();
        std::cout << "Electronic: " << electronic->getBrand() << " " << electronic->getModel() 
                  << " - $" << electronic->getPrice() << std::endl;
    }
    
    double getTotalPrice() const {
        return totalPrice;
    }
};

class DescriptionGenerator : public Visitor {
public:
    void visit(Book* book) override {
        std::cout << "Book: \"" << book->getTitle() << "\" by " << book->getAuthor() 
                  << " - A great read!" << std::endl;
    }
    
    void visit(Fruit* fruit) override {
        std::cout << "Fruit: " << fruit->getName() << " (" << fruit->getWeight() << "kg) - Fresh and healthy!" << std::endl;
    }
    
    void visit(Electronic* electronic) override {
        std::cout << "Electronic: " << electronic->getBrand() << " " << electronic->getModel() 
                  << " - High-tech gadget!" << std::endl;
    }
};

class TaxCalculator : public Visitor {
private:
    double totalTax;
    
public:
    TaxCalculator() : totalTax(0) {}
    
    void visit(Book* book) override {
        double tax = book->getPrice() * 0.05;
        totalTax += tax;
        std::cout << "Book tax: $" << tax << std::endl;
    }
    
    void visit(Fruit* fruit) override {
        double tax = fruit->getPrice() * 0.02;
        totalTax += tax;
        std::cout << "Fruit tax: $" << tax << std::endl;
    }
    
    void visit(Electronic* electronic) override {
        double tax = electronic->getPrice() * 0.10;
        totalTax += tax;
        std::cout << "Electronic tax: $" << tax << std::endl;
    }
    
    double getTotalTax() const {
        return totalTax;
    }
};

class ShoppingCart {
private:
    std::vector<std::unique_ptr<Item>> items;
    
public:
    void addItem(std::unique_ptr<Item> item) {
        items.push_back(std::move(item));
    }
    
    void acceptVisitor(Visitor* visitor) {
        for (const auto& item : items) {
            item->accept(visitor);
        }
    }
};
