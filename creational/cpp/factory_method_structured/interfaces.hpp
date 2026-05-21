#pragma once
#include <iostream>
#include <memory>
#include <string>

class Document {
public:
    virtual ~Document() = default;
    
    virtual void open() = 0;
    virtual void close() = 0;
    virtual void save() = 0;
    
    virtual std::string getType() const = 0;
};

class Application {
protected:
    virtual std::unique_ptr<Document> createDocument() = 0;
    
public:
    virtual ~Application() = default;
    
    void newDocument() {
        auto doc = createDocument();
        std::cout << "Created: " << doc->getType() << std::endl;
        doc->open();
        doc->save();
        doc->close();
    }
};
