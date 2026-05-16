/*
 * DECORATOR DESIGN PATTERN
 * 
 * WHAT IS IT?
 * The Decorator pattern lets you attach new behaviors to objects by placing these objects inside special wrapper objects that contain the behaviors.
 * It provides a flexible alternative to inheritance for extending functionality.
 * 
 * WHY DOES IT EXIST?
 * - When you want to add responsibilities to individual objects dynamically without affecting other objects
 * - When extending a class by subclassing is impractical (too many subclasses)
 * - When you want to add and remove responsibilities at runtime
 * 
 * WHEN TO USE IT?
 * - When you need to add responsibilities to individual objects without affecting other objects of the same class
 * - When the class definition may be hidden or otherwise unavailable for subclassing
 * - When you want to add functionality to objects in a transparent way (clients shouldn't know the difference)
 * - Common use cases: UI components (scrollbars, borders), data streams (compression, encryption), logging, caching
 * 
 * PROS:
 * - Single Responsibility Principle (divides functionality into small classes)
 * - Open/Closed Principle (can extend behavior without modifying existing code)
 * - Flexible alternative to subclassing
 * - Can add/remove responsibilities at runtime
 * 
 * CONS:
 * - Can result in many small classes (code complexity)
 * - Can make it hard to remove wrapped decorators
 * - Can make debugging difficult due to many layers
 * - Initial setup can be complex
 * 
 * REAL-WORLD ANALOGY:
 * Think of ordering coffee. You start with a basic coffee (component), then you can add decorators like milk, sugar, whipped cream, or syrup. Each decorator adds its own behavior (flavor, cost) while still being treated as coffee. You can combine multiple decorators in any order.
 */

#include <iostream>
#include <string>
#include <memory>

// Component Interface - defines the interface for objects that can have responsibilities added
class Coffee {
public:
    virtual ~Coffee() = default;
    virtual double getCost() = 0;
    virtual std::string getDescription() = 0;
};

// Concrete Component - the basic object that can have responsibilities added
class SimpleCoffee : public Coffee {
public:
    double getCost() override {
        return 2.0;
    }
    
    std::string getDescription() override {
        return "Simple Coffee";
    }
};

// Decorator - implements the Component interface and wraps a Component
class CoffeeDecorator : public Coffee {
protected:
    std::shared_ptr<Coffee> decoratedCoffee;
    
public:
    CoffeeDecorator(std::shared_ptr<Coffee> coffee) : decoratedCoffee(coffee) {}
    
    virtual double getCost() override {
        return decoratedCoffee->getCost();
    }
    
    virtual std::string getDescription() override {
        return decoratedCoffee->getDescription();
    }
};

// Concrete Decorator 1: Milk
class MilkDecorator : public CoffeeDecorator {
public:
    MilkDecorator(std::shared_ptr<Coffee> coffee) : CoffeeDecorator(coffee) {}
    
    double getCost() override {
        return CoffeeDecorator::getCost() + 0.5;
    }
    
    std::string getDescription() override {
        return CoffeeDecorator::getDescription() + ", Milk";
    }
};

// Concrete Decorator 2: Sugar
class SugarDecorator : public CoffeeDecorator {
public:
    SugarDecorator(std::shared_ptr<Coffee> coffee) : CoffeeDecorator(coffee) {}
    
    double getCost() override {
        return CoffeeDecorator::getCost() + 0.2;
    }
    
    std::string getDescription() override {
        return CoffeeDecorator::getDescription() + ", Sugar";
    }
};

// Concrete Decorator 3: Whipped Cream
class WhippedCreamDecorator : public CoffeeDecorator {
public:
    WhippedCreamDecorator(std::shared_ptr<Coffee> coffee) : CoffeeDecorator(coffee) {}
    
    double getCost() override {
        return CoffeeDecorator::getCost() + 1.0;
    }
    
    std::string getDescription() override {
        return CoffeeDecorator::getDescription() + ", Whipped Cream";
    }
};

// Example 2: Text Formatting Decorator
// Shows how decorators can be used for text processing

class TextComponent {
public:
    virtual ~TextComponent() = default;
    virtual std::string getText() = 0;
};

class SimpleText : public TextComponent {
private:
    std::string text;
    
public:
    SimpleText(const std::string& text) : text(text) {}
    
    std::string getText() override {
        return text;
    }
};

class TextDecorator : public TextComponent {
protected:
    std::shared_ptr<TextComponent> wrappedText;
    
public:
    TextDecorator(std::shared_ptr<TextComponent> text) : wrappedText(text) {}
    
    virtual std::string getText() override {
        return wrappedText->getText();
    }
};

class BoldDecorator : public TextDecorator {
public:
    BoldDecorator(std::shared_ptr<TextComponent> text) : TextDecorator(text) {}
    
    std::string getText() override {
        return "<b>" + TextDecorator::getText() + "</b>";
    }
};

class ItalicDecorator : public TextDecorator {
public:
    ItalicDecorator(std::shared_ptr<TextComponent> text) : TextDecorator(text) {}
    
    std::string getText() override {
        return "<i>" + TextDecorator::getText() + "</i>";
    }
};

class UnderlineDecorator : public TextDecorator {
public:
    UnderlineDecorator(std::shared_ptr<TextComponent> text) : TextDecorator(text) {}
    
    std::string getText() override {
        return "<u>" + TextDecorator::getText() + "</u>";
    }
};

// Example 3: Data Stream Decorator
// Shows how decorators can be used for data processing

class DataSource {
public:
    virtual ~DataSource() = default;
    virtual void writeData(std::string data) = 0;
    virtual std::string readData() = 0;
};

class FileDataSource : public DataSource {
private:
    std::string data;
    
public:
    void writeData(std::string data) override {
        this->data = data;
        std::cout << "Writing data to file: " << data << std::endl;
    }
    
    std::string readData() override {
        std::cout << "Reading data from file: " << data << std::endl;
        return data;
    }
};

class DataSourceDecorator : public DataSource {
protected:
    std::shared_ptr<DataSource> wrappedSource;
    
public:
    DataSourceDecorator(std::shared_ptr<DataSource> source) : wrappedSource(source) {}
    
    virtual void writeData(std::string data) override {
        wrappedSource->writeData(data);
    }
    
    virtual std::string readData() override {
        return wrappedSource->readData();
    }
};

class EncryptionDecorator : public DataSourceDecorator {
public:
    EncryptionDecorator(std::shared_ptr<DataSource> source) : DataSourceDecorator(source) {}
    
    void writeData(std::string data) override {
        std::string encrypted = "[ENCRYPTED]" + data + "[ENCRYPTED]";
        std::cout << "Encrypting data..." << std::endl;
        wrappedSource->writeData(encrypted);
    }
    
    std::string readData() override {
        std::string data = wrappedSource->readData();
        std::cout << "Decrypting data..." << std::endl;
        // Remove encryption markers for demo
        if (data.find("[ENCRYPTED]") == 0) {
            data = data.substr(11, data.length() - 22);
        }
        return data;
    }
};

class CompressionDecorator : public DataSourceDecorator {
public:
    CompressionDecorator(std::shared_ptr<DataSource> source) : DataSourceDecorator(source) {}
    
    void writeData(std::string data) override {
        std::string compressed = "[COMPRESSED]" + data + "[COMPRESSED]";
        std::cout << "Compressing data..." << std::endl;
        wrappedSource->writeData(compressed);
    }
    
    std::string readData() override {
        std::string data = wrappedSource->readData();
        std::cout << "Decompressing data..." << std::endl;
        // Remove compression markers for demo
        if (data.find("[COMPRESSED]") == 0) {
            data = data.substr(12, data.length() - 24);
        }
        return data;
    }
};

int main() {
    std::cout << "=== Decorator Pattern Demo ===" << std::endl << std::endl;
    
    // Example 1: Coffee Shop
    std::cout << "--- Coffee Shop Example ---" << std::endl;
    
    std::shared_ptr<Coffee> coffee = std::make_shared<SimpleCoffee>();
    std::cout << coffee->getDescription() << " $" << coffee->getCost() << std::endl;
    
    coffee = std::make_shared<MilkDecorator>(coffee);
    std::cout << coffee->getDescription() << " $" << coffee->getCost() << std::endl;
    
    coffee = std::make_shared<SugarDecorator>(coffee);
    std::cout << coffee->getDescription() << " $" << coffee->getCost() << std::endl;
    
    coffee = std::make_shared<WhippedCreamDecorator>(coffee);
    std::cout << coffee->getDescription() << " $" << coffee->getCost() << std::endl;
    
    std::cout << std::endl;
    
    // Example 2: Text Formatting
    std::cout << "--- Text Formatting Example ---" << std::endl;
    
    std::shared_ptr<TextComponent> text = std::make_shared<SimpleText>("Hello World");
    std::cout << "Original: " << text->getText() << std::endl;
    
    text = std::make_shared<BoldDecorator>(text);
    std::cout << "Bold: " << text->getText() << std::endl;
    
    text = std::make_shared<ItalicDecorator>(text);
    std::cout << "Bold + Italic: " << text->getText() << std::endl;
    
    text = std::make_shared<UnderlineDecorator>(text);
    std::cout << "Bold + Italic + Underline: " << text->getText() << std::endl;
    
    std::cout << std::endl;
    
    // Example 3: Data Stream Processing
    std::cout << "--- Data Stream Processing Example ---" << std::endl;
    
    std::shared_ptr<DataSource> dataSource = std::make_shared<FileDataSource>();
    std::cout << "\nWriting plain data:" << std::endl;
    dataSource->writeData("Important Data");
    std::cout << "Reading: " << dataSource->readData() << std::endl;
    
    std::cout << "\nWriting encrypted data:" << std::endl;
    dataSource = std::make_shared<EncryptionDecorator>(dataSource);
    dataSource->writeData("Secret Data");
    std::cout << "Reading: " << dataSource->readData() << std::endl;
    
    std::cout << "\nWriting encrypted and compressed data:" << std::endl;
    dataSource = std::make_shared<CompressionDecorator>(dataSource);
    dataSource->writeData("Very Secret Data");
    std::cout << "Reading: " << dataSource->readData() << std::endl;
    
    return 0;
}
