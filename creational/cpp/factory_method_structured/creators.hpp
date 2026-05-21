#pragma once
#include "interfaces.hpp"
#include "concrete_products.hpp"
#include <stdexcept>

class TextEditor : public Application {
protected:
    std::unique_ptr<Document> createDocument() override { return std::make_unique<TextDocument>(); }
};

class PDFViewer : public Application {
protected:
    std::unique_ptr<Document> createDocument() override { return std::make_unique<PDFDocument>(); }
};

class WebBrowser : public Application {
protected:
    std::unique_ptr<Document> createDocument() override { return std::make_unique<HTMLDocument>(); }
};

class DocumentFactory {
public:
    enum class DocumentType { TEXT, PDF, HTML };
    
    static std::unique_ptr<Document> createDocument(DocumentType type) {
        switch (type) {
            case DocumentType::TEXT: return std::make_unique<TextDocument>();
            case DocumentType::PDF: return std::make_unique<PDFDocument>();
            case DocumentType::HTML: return std::make_unique<HTMLDocument>();
            default: throw std::invalid_argument("Unknown document type");
        }
    }
};
