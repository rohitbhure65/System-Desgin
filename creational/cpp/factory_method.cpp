/*
 * FACTORY METHOD DESIGN PATTERN
 * 
 * WHAT IS IT?
 * The Factory Method pattern defines an interface for creating an object but lets subclasses decide which class to instantiate.
 * It delegates the instantiation logic to child classes.
 * 
 * WHY DOES IT EXIST?
 * - Decouples the creation of objects from their usage
 * - Allows a class to defer instantiation to subclasses
 * - Provides a way to extend the creation logic without modifying existing code (Open/Closed Principle)
 * - Eliminates the need to bind application-specific classes into your code
 * 
 * WHEN TO USE IT?
 * - When a class can't anticipate the class of objects it must create
 * - When a class wants its subclasses to specify the objects it creates
 * - When classes delegate responsibility to one of several helper subclasses, and you want to localize the knowledge of which helper subclass is the delegate
 * - Common use cases: document creation, UI components, payment processing, logging frameworks
 * 
 * PROS:
 * - Avoids tight coupling between the creator and the concrete products
 * - Follows Open/Closed Principle (easy to introduce new products without changing existing code)
 * - Single Responsibility Principle (product creation code is in one place)
 * - Can be combined with other patterns (e.g., Singleton, Prototype)
 * 
 * CONS:
 * - Can make the code more complex by introducing many subclasses
 * - May require creating a parallel inheritance hierarchy for creators and products
 * - Can lead to excessive use of inheritance
 * 
 * REAL-WORLD ANALOGY:
 * Think of a car manufacturing plant. The plant (factory) knows how to build cars, but it doesn't know what specific type of car to build until an order comes in. The plant has a method to build cars, but the specific car model (sedan, SUV, truck) is determined by the order or by specialized assembly lines (subclasses).
 */

#include <iostream>
#include <memory>
#include <string>

// Product interface - defines the common interface for all products
class Document {
public:
    virtual ~Document() = default;
    
    // Common operation that all documents must implement
    virtual void open() = 0;
    virtual void close() = 0;
    virtual void save() = 0;
    
    // Type identification
    virtual std::string getType() const = 0;
};

// Concrete Product 1: Text Document
class TextDocument : public Document {
public:
    void open() override {
        std::cout << "Opening Text Document in text editor..." << std::endl;
    }
    
    void close() override {
        std::cout << "Closing Text Document..." << std::endl;
    }
    
    void save() override {
        std::cout << "Saving Text Document as .txt file..." << std::endl;
    }
    
    std::string getType() const override {
        return "Text Document";
    }
};

// Concrete Product 2: PDF Document
class PDFDocument : public Document {
public:
    void open() override {
        std::cout << "Opening PDF Document in PDF viewer..." << std::endl;
    }
    
    void close() override {
        std::cout << "Closing PDF Document..." << std::endl;
    }
    
    void save() override {
        std::cout << "Saving PDF Document as .pdf file..." << std::endl;
    }
    
    std::string getType() const override {
        return "PDF Document";
    }
};

// Concrete Product 3: HTML Document
class HTMLDocument : public Document {
public:
    void open() override {
        std::cout << "Opening HTML Document in web browser..." << std::endl;
    }
    
    void close() override {
        std::cout << "Closing HTML Document..." << std::endl;
    }
    
    void save() override {
        std::cout << "Saving HTML Document as .html file..." << std::endl;
    }
    
    std::string getType() const override {
        return "HTML Document";
    }
};

// Creator abstract class - declares the factory method
class Application {
protected:
    // Factory method - to be implemented by subclasses
    // This is the core of the pattern: subclasses decide what to create
    virtual std::unique_ptr<Document> createDocument() = 0;
    
public:
    virtual ~Application() = default;
    
    // Business logic that uses the product
    // This method doesn't need to know which specific document is created
    void newDocument() {
        // Use the factory method to create a document
        auto doc = createDocument();
        std::cout << "Created: " << doc->getType() << std::endl;
        doc->open();
        doc->save();
        doc->close();
    }
};

// Concrete Creator 1: Text Editor Application
class TextEditor : public Application {
protected:
    std::unique_ptr<Document> createDocument() override {
        return std::make_unique<TextDocument>();
    }
};

// Concrete Creator 2: PDF Viewer Application
class PDFViewer : public Application {
protected:
    std::unique_ptr<Document> createDocument() override {
        return std::make_unique<PDFDocument>();
    }
};

// Concrete Creator 3: Web Browser Application
class WebBrowser : public Application {
protected:
    std::unique_ptr<Document> createDocument() override {
        return std::make_unique<HTMLDocument>();
    }
};

// Alternative implementation: Parameterized Factory Method
// This allows a single creator to create multiple types of products
class DocumentFactory {
public:
    enum class DocumentType {
        TEXT,
        PDF,
        HTML
    };
    
    static std::unique_ptr<Document> createDocument(DocumentType type) {
        switch (type) {
            case DocumentType::TEXT:
                return std::make_unique<TextDocument>();
            case DocumentType::PDF:
                return std::make_unique<PDFDocument>();
            case DocumentType::HTML:
                return std::make_unique<HTMLDocument>();
            default:
                throw std::invalid_argument("Unknown document type");
        }
    }
};

int main() {
    std::cout << "=== Factory Method Pattern Demo ===" << std::endl << std::endl;
    
    // Using inheritance-based Factory Method
    std::cout << "--- Inheritance-based Factory Method ---" << std::endl;
    
    std::unique_ptr<Application> textEditor = std::make_unique<TextEditor>();
    textEditor->newDocument();
    std::cout << std::endl;
    
    std::unique_ptr<Application> pdfViewer = std::make_unique<PDFViewer>();
    pdfViewer->newDocument();
    std::cout << std::endl;
    
    std::unique_ptr<Application> webBrowser = std::make_unique<WebBrowser>();
    webBrowser->newDocument();
    std::cout << std::endl;
    
    // Using parameterized Factory Method
    std::cout << "--- Parameterized Factory Method ---" << std::endl;
    
    auto textDoc = DocumentFactory::createDocument(DocumentFactory::DocumentType::TEXT);
    textDoc->open();
    std::cout << std::endl;
    
    auto pdfDoc = DocumentFactory::createDocument(DocumentFactory::DocumentType::PDF);
    pdfDoc->open();
    std::cout << std::endl;
    
    auto htmlDoc = DocumentFactory::createDocument(DocumentFactory::DocumentType::HTML);
    htmlDoc->open();
    
    return 0;
}
